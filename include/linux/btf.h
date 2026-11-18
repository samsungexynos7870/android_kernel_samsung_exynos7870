/* SPDX-License-Identifier: GPL-2.0 */
/* Minimal BTF support for the BPF syscall. */
#ifndef _LINUX_BTF_H
#define _LINUX_BTF_H

#include <uapi/linux/bpf.h>

int btf_new_fd(const union bpf_attr *attr);

#endif /* _LINUX_BTF_H */
