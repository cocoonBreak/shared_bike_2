#include "thread_common.h"
#include "thread_mutex.h"

int thread_mutex_create(thread_mutex_t *mtx)
{
	pthread_mutexattr_t  attr;

	//初始化锁的属性
	if(pthread_mutexattr_init(&attr) != 0){
		fprintf(stderr, "pthread_mutexattr_init() failed.");
		return REV_ERROR;
	}

	//设置锁的属性为检错锁，如果同一个线程请求同一个锁，则返回EDEADLK，否则与PTHREAD_MUTEX_TIMED_NP类型动作相同。这样就保证当不允许多次加锁时不会出现最简单情况下的死锁。
	if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0){
		fprintf(stderr, "pthread_mutexattr_settype(PTHREAD_MUTEX_ERRORCHECK) failed.");
		return REV_ERROR;
	}

	//创建锁
	if(pthread_mutex_init(mtx, &attr) != 0){
		fprintf(stderr, "pthread_mutex_init() failed.");
		return REV_ERROR;
	}

	//销毁锁的属性attr
	if(pthread_mutexattr_destroy(&attr) != 0){
		fprintf(stderr, "pthread_mutexattr_destroy() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_mutex_destroy(thread_mutex_t *mtx)
{
	if(pthread_mutex_destroy(mtx) != 0){
		fprintf(stderr, "pthread_mutex_destroy() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_mutex_lock(thread_mutex_t *mtx)
{
	if(pthread_mutex_lock(mtx) != 0){
		fprintf(stderr, "pthread_mutex_lock() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}

int thread_mutex_unlock(thread_mutex_t *mtx)
{
	if(pthread_mutex_unlock(mtx) != 0){
		fprintf(stderr, "pthread_mutex_unlock() failed.");
		return REV_ERROR;
	}

	return REV_OK;
}
