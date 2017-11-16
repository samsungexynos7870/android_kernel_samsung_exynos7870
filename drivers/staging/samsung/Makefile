# drivers/staging/samsung/Makefile
#
# Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
#		http://www.samsung.com/
#
# Licensed under GPLv2

obj-y				:=
obj-m				:=
obj-n				:=
obj-				:=

# Samsung Battery
obj-$(CONFIG_BATTERY_SAMSUNG)	+= sec_batt.o

# Samsung TN Features 
obj-$(CONFIG_SEC_EXT)		+= sec_log.o
# Samsung TN Sysfs Feature
obj-$(CONFIG_SEC_SYSFS)		+= sec_sysfs.o
# Samsung TN Reset Feature
obj-$(CONFIG_SEC_REBOOT)	+= sec_reboot.o
# Samsung TN Debugging Features
obj-$(CONFIG_SEC_DEBUG)		+= sec_debug.o sec_getlog.o sec_gaf.o sec_data_param.o
# Samsung TN BSP Options
obj-$(CONFIG_SEC_PARAM)		+= sec_param.o
obj-$(CONFIG_SEC_BOOTSTAT)	+= sec_bootstat.o
obj-$(CONFIG_SEC_INITCALL_DEBUG)+= sec_initcall_debug.o
obj-$(CONFIG_ARGOS)		+= sec_argos.o

# Samsung sec NAD Feature
obj-$(CONFIG_SEC_NAD)		+= sec_nad.o

