#ifndef __THREAD_COMMON_H__
#define __THREAD_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define  REV_OK          0
#define  REV_ERROR      -1
#define  REV_AGAIN      -2
#define  REV_BUSY       -3
#define  REV_DONE       -4
#define  REV_DECLINED   -5
#define  REV_ABORT      -6

#define DEFAULT_THREAD_NUM 4
#define DEFAULT_QUEUE_NUM 65535

typedef intptr_t int_t;
typedef uintptr_t uint_t;

#ifdef __cplusplus
}
#endif

#endif
