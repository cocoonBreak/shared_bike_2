#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

typedef pthread_mutex_t thread_mutex_t;

int thread_mutex_create(thread_mutex_t *mtx);
int thread_mutex_destroy(thread_mutex_t *mtx);
int thread_mutex_lock(thread_mutex_t *mtx);
int thread_mutex_unlock(thread_mutex_t *mtx);

#ifdef __cplusplus
}
#endif

#endif
