#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

#include <iostream>
#include <unistd.h>
#include "SchedManager.h"
#include <sched.h>

void SchedManager::changePriority(int prio, bool useNice) {
	if (useNice) {
		nice(prio);
        return;
	}
	setpriority(PRIO_PROCESS, getpid(), prio);
	int prior = getpriority(PRIO_PROCESS, getpid());
	std::cout << "<priority: " << prior  << ">" << std::endl;	
}

int SchedManager::getPriority() {
	return getpriority(PRIO_PROCESS, getpid());
}

int SchedManager::getPriorityFromParam() {
	struct sched_param param;
	sched_getparam(getpid(), &param);
    return param.sched_priority;
}

int SchedManager::getThreadPriority(pthread_t td) {
	struct sched_param param;
    int policy;
    if (pthread_getschedparam(td, &policy , &param) != 0) {
        return -100;
    }   
    return param.sched_priority;
}

std::string SchedManager::getThreadPolicy(pthread_t td) {
	struct sched_param param;
    int policy;
    if (pthread_getschedparam(td, &policy , &param) != 0) {
        return "FAILED";
    }   
    if (policy == 0) {
        return "Normal";
    } else if (policy == 1) {
        return "FIFO";
    } else if (policy == 2) {
        return "RR";
    } else if (policy == 3) {
        return "BATCH";
    } else {
        return "WIERD..MAYBE FAILED";
    }
}

void SchedManager::changeThreadPriority(pthread_t td, int prio, int policy) {
	struct sched_param param;
    param.sched_priority = prio;
    pthread_setschedparam(td, policy, &param);
}

pthread_attr_t SchedManager::getThreadAttrWithSched(int prio, int policy) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    return attr;
}
