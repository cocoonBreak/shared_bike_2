#ifndef __THREAD_COND_H__
#define __THREAD_COND_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include "thread_mutex.h"

typedef pthread_cond_t thread_cond_t;

int thread_cond_create(thread_cond_t *cond);
int thread_cond_destroy(thread_cond_t *cond);
int thread_cond_signal(thread_cond_t *cond);
int thread_cond_wait(thread_cond_t *cond, thread_mutex_t *mtx);

#ifdef __cplusplus
}
#endif

#endif
