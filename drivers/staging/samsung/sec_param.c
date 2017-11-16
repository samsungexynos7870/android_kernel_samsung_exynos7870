/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *      http://www.samsung.com
 *
 * Samsung TN debugging code
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sec_ext.h>

#ifdef CONFIG_SEC_PARAM

#define SEC_PARAM_NAME "/dev/block/param"
struct sec_param_data_s {
	struct work_struct sec_param_work;
	unsigned long offset;
	char val;
};
static struct sec_param_data_s sec_param_data;
static DEFINE_MUTEX(sec_param_mutex);

static void sec_param_update(struct work_struct *work)
{
	int ret = -1;
	struct file *fp;
	struct sec_param_data_s *param_data =
		container_of(work, struct sec_param_data_s, sec_param_work);

	fp = filp_open(SEC_PARAM_NAME, O_WRONLY | O_SYNC, 0);
	if (IS_ERR(fp)) {
		pr_err("%s: filp_open error %ld\n", __func__, PTR_ERR(fp));
		return;
	}
	pr_info("%s: set param %c at %lu\n", __func__,
				param_data->val, param_data->offset);
	ret = fp->f_op->llseek(fp, param_data->offset, SEEK_SET);
	if (ret < 0) {
		pr_err("%s: llseek error %d!\n", __func__, ret);
		goto close_fp_out;
	}

	ret = fp->f_op->write(fp, &param_data->val, 1, &(fp->f_pos));
	if (ret < 0)
		pr_err("%s: write error! %d\n", __func__, ret);

close_fp_out:
	if (fp)
		filp_close(fp, NULL);

	pr_info("%s: exit %d\n", __func__, ret);
	return;
}

/*
  success : ret >= 0
  fail : ret < 0
 */
int sec_set_param(unsigned long offset, char val)
{
	int ret = -1;

	mutex_lock(&sec_param_mutex);

	if ((offset != CM_OFFSET) && (offset != CM_OFFSET + CM_OFFSET_LIMIT)
		&& (offset != GSP_OFFSET))
		goto unlock_out;

	if ((val != '0') && (val != '1'))
		goto unlock_out;

	sec_param_data.offset = offset;
	sec_param_data.val = val;

	schedule_work(&sec_param_data.sec_param_work);

	/* how to determine to return success or fail ? */

	ret = 0;
unlock_out:
	mutex_unlock(&sec_param_mutex);
	return ret;
}

static int __init sec_param_work_init(void)
{
	pr_info("%s: start\n", __func__);

	sec_param_data.offset = 0;
	sec_param_data.val = '0';

	INIT_WORK(&sec_param_data.sec_param_work, sec_param_update);

	return 0;
}

static void __exit sec_param_work_exit(void)
{
	cancel_work_sync(&sec_param_data.sec_param_work);
	pr_info("%s: exit\n", __func__);
}
module_init(sec_param_work_init);
module_exit(sec_param_work_exit);

#endif /* CONFIG_SEC_PARAM */
