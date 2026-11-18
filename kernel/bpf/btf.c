// SPDX-License-Identifier: GPL-2.0
/* Minimal BTF support.
 *
 * The verifier of this kernel does not consume BTF, but recent BPF loaders
 * load the BTF blob before the programs and treat a failure as fatal.  The
 * blob is validated for basic sanity and kept alive by the returned fd.
 */
#include <linux/bpf.h>
#include <linux/btf.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/anon_inodes.h>

#define BTF_MAGIC	0xeB9F
#define BTF_VERSION	1
#define BTF_MAX_SIZE	(16 * 1024 * 1024)

struct btf_header {
	__u16	magic;
	__u8	version;
	__u8	flags;
	__u32	hdr_len;

	/* All offsets are in bytes relative to the end of this header */
	__u32	type_off;
	__u32	type_len;
	__u32	str_off;
	__u32	str_len;
};

struct btf {
	void *data;
	u32 data_size;
};

static void btf_free(struct btf *btf)
{
	kfree(btf->data);
	kfree(btf);
}

static int btf_release(struct inode *inode, struct file *filp)
{
	btf_free(filp->private_data);
	return 0;
}

static const struct file_operations btf_fops = {
	.release	= btf_release,
};

static int btf_parse_hdr(const void *data, u32 data_size)
{
	const struct btf_header *hdr = data;
	u32 hdr_len, meta_left;

	if (data_size < sizeof(*hdr))
		return -EINVAL;

	hdr_len = hdr->hdr_len;
	if (hdr_len < sizeof(*hdr) || hdr_len > data_size)
		return -EINVAL;

	/* Unsupported header extensions must be zero. */
	if (hdr_len > sizeof(*hdr)) {
		const u8 *p = data + sizeof(*hdr);
		const u8 *end = data + hdr_len;

		for (; p < end; p++)
			if (*p)
				return -EINVAL;
	}

	if (hdr->magic != BTF_MAGIC)
		return -EINVAL;
	if (hdr->version != BTF_VERSION)
		return -EINVAL;
	if (hdr->flags)
		return -EINVAL;

	if (data_size == hdr_len)
		return -EINVAL;

	/* The type and string sections must exactly cover the data. */
	meta_left = data_size - hdr_len;
	if (hdr->type_off != 0)
		return -EINVAL;
	if (hdr->type_len > meta_left)
		return -EINVAL;
	if (hdr->str_off != hdr->type_len)
		return -EINVAL;
	if (hdr->str_len != meta_left - hdr->type_len)
		return -EINVAL;

	/* The string section starts with an empty string. */
	if (!hdr->str_len ||
	    *(const char *)((const u8 *)data + hdr_len + hdr->str_off) != '\0')
		return -EINVAL;

	return 0;
}

int btf_new_fd(const union bpf_attr *attr)
{
	struct btf *btf;
	void *data;
	int fd, err;

	if (attr->btf_size < sizeof(struct btf_header) ||
	    attr->btf_size > BTF_MAX_SIZE)
		return -E2BIG;

	data = memdup_user(u64_to_user_ptr(attr->btf), attr->btf_size);
	if (IS_ERR(data))
		return PTR_ERR(data);

	err = btf_parse_hdr(data, attr->btf_size);
	if (err) {
		kfree(data);
		return err;
	}

	btf = kzalloc(sizeof(*btf), GFP_USER);
	if (!btf) {
		kfree(data);
		return -ENOMEM;
	}

	btf->data = data;
	btf->data_size = attr->btf_size;

	fd = anon_inode_getfd("btf", &btf_fops, btf, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		btf_free(btf);

	return fd;
}
