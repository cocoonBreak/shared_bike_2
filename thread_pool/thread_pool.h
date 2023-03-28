#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "thread_common.h"
#include "thread_mutex.h"
#include "thread_cond.h"

	typedef struct thread_task_s {
		struct thread_task_s* next;
		uint_t   id;
		void* ctx;
		void           (*handler)(void* data);
	}thread_task_t;

	typedef struct {
		thread_task_t* first;
		thread_task_t** last;
	}thread_pool_queue_t;

#define thread_pool_queue_init(q)          \
	(q)->first = NULL;                     \
	(q)->last = &(q)->first;

	typedef struct thread_pool_s {
		thread_mutex_t       mtx;
		thread_cond_t        cond;
		thread_pool_queue_t  queue;
		int_t                waiting;

		char* name;
		uint_t               threads;
		int_t                max_queue;
	}thread_pool_t;

	thread_task_t* thread_task_alloc(size_t size);
	void thread_task_free(thread_task_t *task);

	thread_pool_t* thread_pool_init();
	void thread_pool_destroy(thread_pool_t* tp);
	int_t thread_task_post(thread_pool_t* tp, thread_task_t* task);

#ifdef __cplusplus
}
#endif

#endif
