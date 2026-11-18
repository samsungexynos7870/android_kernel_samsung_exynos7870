/* Copyright (c) 2016 Facebook
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#ifndef _LINUX_BPF_PERF_EVENT_H
#define _LINUX_BPF_PERF_EVENT_H

#include <uapi/linux/bpf_perf_event.h>
/*
 * struct bpf_perf_event_data_kern already lives in linux/perf_event.h on
 * this tree; pull it in here so bpf_trace.c gets it via the header it
 * expects.
 */
#include <linux/perf_event.h>

#endif /* _LINUX_BPF_PERF_EVENT_H */
