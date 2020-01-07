#pragma once

#include <pthread.h>
#include <inttypes.h>

class SchedManager {
public:
	SchedManager() {}
	~SchedManager() {}

	void changePriority(int prio, bool useNice);
    // It is not working
	void changeThreadPriority(pthread_t td, int prio, int policy);

	int getPriority();
	// It would be return which is initail value.
	int getPriorityFromParam();
    int getThreadPriority(pthread_t td);
    
    pthread_attr_t getThreadAttrWithSched(int prio, int policy);
    std::string getThreadPolicy(pthread_t td);
private:
    
};

/*
	int setpriority(int which, id_t who, int prio);
	int getpriority(int which, id_t who);
	int nice(int inc);
	int sched_setparam(pid_t pid, const struct sched_param *param);
	int sched_getparam(pid_t pid, struct sched_param *param);
	struct sched_param {
    ...
    int sched_priority;
    ...
    };
    int pthread_setschedparam(pthread_t thread, int policy,
                                 const struct sched_param *param);
    int pthread_getschedparam(pthread_t thread, int *policy,
                                 struct sched_param *param);
    int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
    int pthread_attr_getschedpolicy(const pthread_attr_t *attr, int *policy);
    policy are SCHED_NORMAL, SCHED_FIFO, SCHED_RR, and SCHED_OTHER, SCHED_IDLE, SCHED_BATCH
*/
