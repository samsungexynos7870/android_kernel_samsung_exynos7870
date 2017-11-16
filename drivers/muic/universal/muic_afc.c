/*
 * muic_afc.c
 *
 * Copyright (C) 2014 Samsung Electronics
 * Jeongrae Kim <jryu.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/module.h>

#include <linux/muic/muic.h>
#include <linux/muic/muic_afc.h>
#include "muic-internal.h"
#include "muic_regmap.h"
#include "muic_i2c.h"
#if defined(CONFIG_MUIC_NOTIFIER)
#include <linux/muic/muic_notifier.h>
#endif /* CONFIG_MUIC_NOTIFIER */

/* Bit 0 : VBUS_VAILD, Bit 1~7 : Reserved */
#define	REG_RSVDID1	0x15

#define	REG_AFCTXD	0x19
#define	REG_VBUSSTAT	0x1b

#if defined(CONFIG_MUIC_UNIVERSAL_SM5705_AFC_QC20)
#define	REG_AFCSTAT	0x1A
#endif

muic_data_t *gpmuic;
static int afc_work_state;

static int muic_is_afc_voltage(void);
static int muic_dpreset_afc(void);
static int muic_restart_afc(void);

/* To make AFC work properly on boot */
static int is_charger_ready;
static struct work_struct muic_afc_init_work;

int muic_check_afc_state(int state)
{
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;
	int ret, retry;

	pr_info("%s state = %d\n", __func__, state);

	if (state) {
		/* Flash on state */
		if (muic_is_afc_voltage() && gpmuic->is_afc_device) {
			ret = muic_dpreset_afc();
			if (ret < 0) {
				pr_err("%s:failed to AFC reset(%d)\n",
						__func__, ret);
			}
			msleep(60); // 60ms delay

			afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_VBUS_READ, 1);
			afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_VBUS_READ, 0);
			for (retry = 0; retry <20; retry++) {
				mdelay(20);
				ret = muic_is_afc_voltage();
				if (!ret) {
					pr_info("%s:AFC Reset Success(%d)\n",
							__func__, ret);
					gpmuic->is_flash_on = 1;
					return 1;
				} else {
					pr_info("%s:AFC Reset Failed(%d)\n",
							__func__, ret);
					gpmuic->is_flash_on = -1;
				}
			}
		} else {
			pr_info("%s:Not connected AFC\n",__func__);
			gpmuic->is_flash_on = 1;
			return 1;
		}
	} else {
		/* Flash off state */
		if ((gpmuic->attached_dev == ATTACHED_DEV_AFC_CHARGER_5V_MUIC) ||
				((gpmuic->is_afc_device) && (gpmuic->attached_dev != ATTACHED_DEV_AFC_CHARGER_9V_MUIC)))
			muic_restart_afc();
		gpmuic->is_flash_on = 0;
		return 1;
	}
	return 0;
}
EXPORT_SYMBOL(muic_check_afc_state);

int muic_torch_prepare(int state)
{
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;
	int ret, retry;

	pr_info("%s state = %d\n", __func__, state);

	if (afc_work_state == 1) {
		pr_info("%s:%s cancel_delayed_work  afc_work_state=%d\n",MUIC_DEV_NAME, __func__, afc_work_state);
		cancel_delayed_work(&gpmuic->afc_restart_work);
		afc_work_state = 0;
	}

	if (state) {
		/* Torch on state */
		if (muic_is_afc_voltage() && gpmuic->is_afc_device) {
			ret = muic_dpreset_afc();
			msleep(60); // 60ms delay
			if (ret < 0) {
				pr_err("%s:failed to AFC reset(%d)\n",
						__func__, ret);
			}
			afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_VBUS_READ, 1);
			afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_VBUS_READ, 0);
			for (retry = 0; retry <20; retry++) {
				mdelay(20);
				ret = muic_is_afc_voltage();
				if (!ret) {
					pr_info("%s:AFC Reset Success(%d)\n",
							__func__, ret);
					gpmuic->is_flash_on = 1;
					return 1;
				} else {
					pr_info("%s:AFC Reset Failed(%d)\n",
							__func__, ret);
					gpmuic->is_flash_on = -1;
				}
			}
		} else {
			pr_info("%s:Not connected AFC\n",__func__);
			gpmuic->is_flash_on = 1;
			return 1;
		}
	} else {
		/* Torch off state */
		gpmuic->is_flash_on = 0;
		if ((gpmuic->attached_dev == ATTACHED_DEV_AFC_CHARGER_5V_MUIC) ||
				((gpmuic->is_afc_device) && (gpmuic->attached_dev != ATTACHED_DEV_AFC_CHARGER_9V_MUIC))) {
			schedule_delayed_work(&gpmuic->afc_restart_work, msecs_to_jiffies(5000)); // 20sec
			pr_info("%s:%s AFC_torch_work start \n",MUIC_DEV_NAME, __func__ );
			afc_work_state = 1;
		}
		return 1;
	}
	return 0;
}
EXPORT_SYMBOL(muic_torch_prepare);

static int muic_is_afc_voltage(void)
{
	struct i2c_client *i2c = gpmuic->i2c;
	int vbus_status;
	
	if (gpmuic->attached_dev == ATTACHED_DEV_NONE_MUIC) {
		pr_info("%s attached_dev None \n", __func__);
		return 0;
	}

	vbus_status = muic_i2c_read_byte(i2c, REG_VBUSSTAT);
	vbus_status = (vbus_status & 0x0F);
	pr_info("%s vbus_status (%d)\n", __func__, vbus_status);
	if (vbus_status == 0x00)
		return 0;
	else
		return 1;
}

int muic_dpreset_afc(void)
{
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;

	pr_info("%s: gpmuic->attached_dev = %d\n", __func__, gpmuic->attached_dev);
	if ( (gpmuic->attached_dev == ATTACHED_DEV_AFC_CHARGER_9V_MUIC) ||
		(gpmuic->attached_dev == ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC) ||
		(muic_is_afc_voltage()) ) {
		// ENAFC set '0'
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_ENAFC, 0);
		msleep(50); // 50ms delay

		// DP_RESET
		pr_info("%s:AFC Disable \n", __func__);
#if defined(CONFIG_MUIC_UNIVERSAL_SM5705_AFC_QC20)
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_ENQC20, 0);
#endif
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_DIS_AFC, 1);
		msleep(20);
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_DIS_AFC, 0);

		gpmuic->attached_dev = ATTACHED_DEV_AFC_CHARGER_5V_MUIC;
		muic_notifier_attach_attached_dev(ATTACHED_DEV_AFC_CHARGER_5V_MUIC);
	}

	return 0;
}

static int muic_restart_afc(void)
{
	struct i2c_client *i2c = gpmuic->i2c;
	int ret, value;
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;

	pr_info("%s:AFC Restart attached_dev = 0x%x\n", __func__, gpmuic->attached_dev);
	msleep(120); // 120ms delay
	if (gpmuic->attached_dev == ATTACHED_DEV_NONE_MUIC) {
		pr_info("%s:%s Device type is None\n",MUIC_DEV_NAME, __func__);
		return 0;
	}
	gpmuic->attached_dev = ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC;
	muic_notifier_attach_attached_dev(ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC);
	cancel_delayed_work(&gpmuic->afc_retry_work);
	schedule_delayed_work(&gpmuic->afc_retry_work, msecs_to_jiffies(5000)); // 5sec

	// voltage(9.0V) + current(1.65A) setting : 0x
	value = 0x46;
	ret = muic_i2c_write_byte(i2c, REG_AFCTXD, value);
	if (ret < 0)
		printk(KERN_ERR "[muic] %s: err write AFC_TXD(%d)\n", __func__, ret);
	pr_info("%s:AFC_TXD [0x%02x]\n", __func__, value);

#if defined(CONFIG_MUIC_UNIVERSAL_SM5705_AFC_QC20)
	ret = muic_i2c_read_byte(i2c, REG_AFCSTAT);
	if (ret < 0)
		printk(KERN_ERR "%s: err read AFC_STATUS %d\n", __func__, ret);
	pr_info("%s:%s AFC_STATUS [0x%02x]\n",MUIC_DEV_NAME, __func__, ret);
#endif

	// ENAFC set '1'
	afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_ENAFC, 1);

	return 0;
}

static void muic_afc_restart_work(struct work_struct *work)
{
	struct i2c_client *i2c = gpmuic->i2c;
	int ret, value;
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;

	pr_info("%s:AFC Restart\n", __func__);
	msleep(120); // 120ms delay
	if (gpmuic->attached_dev == ATTACHED_DEV_NONE_MUIC) {
		pr_info("%s:%s Device type is None\n",MUIC_DEV_NAME, __func__);
		return;
	}
	gpmuic->attached_dev = ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC;
	muic_notifier_attach_attached_dev(ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC);
	cancel_delayed_work(&gpmuic->afc_retry_work);
	schedule_delayed_work(&gpmuic->afc_retry_work, msecs_to_jiffies(5000)); // 5sec

	// voltage(9.0V) + current(1.65A) setting : 0x
	value = 0x46;
	ret = muic_i2c_write_byte(i2c, REG_AFCTXD, value);
	if (ret < 0)
		printk(KERN_ERR "[muic] %s: err write AFC_TXD(%d)\n", __func__, ret);
	pr_info("%s:AFC_TXD [0x%02x]\n", __func__, value);

#if defined(CONFIG_MUIC_UNIVERSAL_SM5705_AFC_QC20)
	ret = muic_i2c_read_byte(i2c, REG_AFCSTAT);
	if (ret < 0)
		printk(KERN_ERR "%s: err read AFC_STATUS %d\n", __func__, ret);
	pr_info("%s:%s AFC_STATUS [0x%02x]\n",MUIC_DEV_NAME, __func__, ret);
#endif

	// ENAFC set '1'
	afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_ENAFC, 1);
	afc_work_state = 0;
}

static void muic_afc_retry_work(struct work_struct *work)
{
	struct i2c_client *i2c = gpmuic->i2c;
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;
	int vbus;

	pr_info("%s:AFC retry work\n", __func__);
	if (gpmuic->attached_dev == ATTACHED_DEV_AFC_CHARGER_PREPARE_MUIC) {
		vbus = muic_i2c_read_byte(i2c, REG_RSVDID1);
		if (!(vbus & 0x01)) {
			pr_info("%s:%s VBUS is nothing\n",MUIC_DEV_NAME, __func__);
			gpmuic->attached_dev = ATTACHED_DEV_NONE_MUIC;
			muic_notifier_attach_attached_dev(ATTACHED_DEV_NONE_MUIC);
			return;
		}		

#if defined(CONFIG_MUIC_UNIVERSAL_SM5705_AFC_QC20)
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_ENQC20, 0);
#endif
		pr_info("%s: [MUIC] devtype is afc prepare - Disable AFC\n", __func__);
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_DIS_AFC, 1);
		msleep(20);
		afcops->afc_ctrl_reg(gpmuic->regmapdesc, AFCCTRL_DIS_AFC, 0);
	}
}

static void muic_focrced_detection_by_charger(struct work_struct *work)
{
	struct afc_ops *afcops = gpmuic->regmapdesc->afcops;

	pr_info("%s\n", __func__);

	mutex_lock(&gpmuic->muic_mutex);

	afcops->afc_init_check(gpmuic->regmapdesc);

	mutex_unlock(&gpmuic->muic_mutex);
}

void muic_charger_init(void)
{
	pr_info("%s\n", __func__);

	if (!gpmuic) {
		pr_info("%s: MUIC AFC is not ready.\n", __func__);
		return;
	}

	if (is_charger_ready) {
		pr_info("%s: charger is already ready.\n", __func__);
		return;
	}

	is_charger_ready = true;

	if (gpmuic->attached_dev == ATTACHED_DEV_TA_MUIC)
		schedule_work(&muic_afc_init_work);
}

static ssize_t afc_off_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	muic_data_t *pmuic = dev_get_drvdata(dev);
	return snprintf(buf, 4, "%d\n", pmuic->is_flash_on);
}

static ssize_t afc_off_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t size)
{
	if (!strncmp(buf, "1", 1)) {
		pr_info("%s, Disable AFC\n", __func__);
		muic_check_afc_state(1);
	} else {
		pr_info("%s, Enable AFC\n", __func__);
		muic_check_afc_state(0);
	}

	return size;
}
static DEVICE_ATTR(afc_off, S_IRUGO | S_IWUSR,
		afc_off_show, afc_off_store);
void muic_init_afc_state(muic_data_t *pmuic)
{
	int ret;
	gpmuic = pmuic;
	gpmuic->is_flash_on = 0;
	gpmuic->is_afc_device = 0;
	INIT_DELAYED_WORK(&gpmuic->afc_restart_work, muic_afc_restart_work);

	/* To make AFC work properly on boot */
	INIT_WORK(&muic_afc_init_work, muic_focrced_detection_by_charger);
	INIT_DELAYED_WORK(&gpmuic->afc_retry_work, muic_afc_retry_work);

	ret = device_create_file(switch_device, &dev_attr_afc_off);
	if (ret < 0) {
		pr_err("[MUIC] Failed to create file (disable AFC)!\n");
	}

	pr_info("%s:attached_dev = %d\n", __func__, gpmuic->attached_dev);
}

MODULE_DESCRIPTION("MUIC driver");
MODULE_AUTHOR("<jryu.kim@samsung.com>");
MODULE_LICENSE("GPL");
