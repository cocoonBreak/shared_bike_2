#include "thread_common.h"
#include "thread_cond.h"

int thread_cond_create(thread_cond_t *cond)
{
	if(pthread_cond_init(cond, NULL) != 0){
		fprintf(stderr, "pthread_cond_init() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_cond_destroy(thread_cond_t *cond)
{
	if(pthread_cond_destroy(cond) != 0){
		fprintf(stderr, "pthread_cond_destroy() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_cond_signal(thread_cond_t *cond)
{
	if(pthread_cond_signal(cond) != 0){
		fprintf(stderr, "pthread_cond_signal() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_cond_wait(thread_cond_t *cond, thread_mutex_t *mtx)
{
	if(pthread_cond_wait(cond, mtx) != 0){
		fprintf(stderr, "pthread_cond_wait() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

