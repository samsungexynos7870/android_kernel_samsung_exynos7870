/*
* Samsung debugging features for Samsung's SoC's.
*
* Copyright (c) 2014 Samsung Electronics Co., Ltd.
*      http://www.samsung.com
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*/

#ifndef SEC_DEBUG_H
#define SEC_DEBUG_H

#include <linux/sizes.h>
#include <linux/memblock.h>
#include <linux/module.h>
#include <linux/reboot.h>

#define SEC_DEBUG_MAGIC_PA memblock_start_of_DRAM()
#define SEC_DEBUG_MAGIC_VA phys_to_virt(SEC_DEBUG_MAGIC_PA)
#define SEC_DEBUG_DUMPER_LOG_VA (SEC_DEBUG_MAGIC_VA + 0x800)

#ifdef CONFIG_SEC_DEBUG
extern int  sec_debug_setup(void);
extern void sec_debug_reboot_handler(void);
extern void sec_debug_panic_handler(void *buf, bool dump);
extern void sec_debug_post_panic_handler(void);

extern int  sec_debug_get_debug_level(void);
extern void sec_debug_disable_printk_process(void);

/* getlog support */
extern void sec_getlog_supply_kernel(void *klog_buf);
extern void sec_getlog_supply_platform(unsigned char *buffer, const char *name);
extern void sec_gaf_supply_rqinfo(unsigned short curr_offset, unsigned short rq_offset);
#else
#define sec_debug_setup()			(-1)
#define sec_debug_reboot_handler()		do { } while(0)
#define sec_debug_panic_handler(a,b)		do { } while(0)
#define sec_debug_post_panic_handler()		do { } while(0)	

#define sec_debug_get_debug_level()		(0)
#define sec_debug_disable_printk_process()	do { } while(0)

#define sec_getlog_supply_kernel(a)		do { } while(0)
#define sec_getlog_supply_platform(a,b)		do { } while(0)

#define sec_gaf_supply_rqinfo(a,b)		do { } while(0)
#endif /* CONFIG_SEC_DEBUG */

#ifdef CONFIG_SEC_DEBUG_MDM_SEPERATE_CRASH
extern int  sec_debug_is_enabled_for_ssr(void);
#else
#define sec_debug_is_enabled_for_ssr()		(0)
#endif /* CONFIG_SEC_DEBUG_MDM_SEPERATE_CRASH */

#ifdef CONFIG_SEC_DEBUG_RESET_REASON

enum sec_debug_reset_reason_t {
	RR_S = 1,
	RR_W = 2,
	RR_D = 3,
	RR_K = 4,
	RR_M = 5,
	RR_P = 6,
	RR_R = 7,
	RR_B = 8,
	RR_N = 9,
	RR_T = 10,
};

extern unsigned reset_reason;
#endif

#if 1	/* TODO : MOVE IT LATER */

#define SEC_DEBUG_SHARED_MAGIC0 0xFFFFFFFF
#define SEC_DEBUG_SHARED_MAGIC1 0x95308180
#define SEC_DEBUG_SHARED_MAGIC2 0x14F014F0
#define SEC_DEBUG_SHARED_MAGIC3 0x00010001

struct sec_debug_ksyms {
	uint32_t magic;
	uint32_t kallsyms_all;
	uint64_t addresses_pa;
	uint64_t names_pa;
	uint64_t num_syms;
	uint64_t token_table_pa;
	uint64_t token_index_pa;
	uint64_t markers_pa;
	uint64_t sinittext;
	uint64_t einittext;
	uint64_t stext;
	uint64_t etext;
	uint64_t end;
};

struct sec_debug_shared_info {
	/* initial magic code */
	unsigned int magic[4];
};

#endif	/* TODO : MOVE IT LATER */

#ifdef CONFIG_SEC_DEBUG_LAST_KMSG
#define SEC_LKMSG_MAGICKEY 0x0000000a6c6c7546
extern void sec_debug_save_last_kmsg(unsigned char *head_ptr, unsigned char *curr_ptr, size_t buf_size);
#else
#define sec_debug_save_last_kmsg(a, b, c)		do { } while (0)
#endif /* CONFIG_SEC_DEBUG_LAST_KMSG */

/**
 * sec_debug_tsp_log : Leave tsp log in tsp_msg file.
 * ( Timestamp + Tsp logs )
 * sec_debug_tsp_log_msg : Leave tsp log in tsp_msg file and
 * add additional message between timestamp and tsp log.
 * ( Timestamp + additional Message + Tsp logs )
 */
#ifdef CONFIG_SEC_DEBUG_TSP_LOG
extern void sec_debug_tsp_log(char *fmt, ...);
extern void sec_debug_tsp_log_msg(char *msg, char *fmt, ...);
extern void sec_debug_tsp_raw_data(char *fmt, ...);
extern void sec_debug_tsp_raw_data_msg(char *msg, char *fmt, ...);
extern void sec_tsp_raw_data_clear(void);
#if defined(CONFIG_TOUCHSCREEN_FTS)
extern void tsp_dump(void);
#elif defined(CONFIG_TOUCHSCREEN_SEC_TS)
extern void tsp_dump_sec(void);
#endif
#else
#define sec_debug_tsp_log(a, ...)			do { } while (0)
#define sec_debug_tsp_log_msg(a, b, ...)		do { } while (0)
#define sec_debug_tsp_raw_data(a, ...)			do { } while (0)
#define sec_debug_tsp_raw_data_msg(a, b, ...)		do { } while (0)
#define sec_tsp_raw_data_clear()			do { } while (0)
#endif /* CONFIG_SEC_DEBUG_TSP_LOG */

#ifdef CONFIG_TOUCHSCREEN_DUMP_MODE
struct tsp_dump_callbacks {
	void (*inform_dump)(void);
};
#endif

extern int sec_debug_force_error(const char *val, struct kernel_param *kp);

#endif /* SEC_DEBUG_H */
