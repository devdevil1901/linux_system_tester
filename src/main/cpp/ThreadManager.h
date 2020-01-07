#pragma once

#include <map>
#include <vector>
#include <pthread.h>
//#include <functional>
#include "SpinLock.h"

typedef void* (*ThreadRoutine)(void *);

typedef struct ThreadInfo {
	ThreadRoutine routine;
	std::string name;
	void *param;
    SpinLock *logLock;
};


class ThreadManager {
public:
	ThreadManager();
	~ThreadManager();
	bool startPrimitiveThread(ThreadInfo *threadInfo);
	void waiting(std::string name);
    
    inline ThreadInfo *createThreadInfo(ThreadRoutine routine, std::string name);
    inline pthread_t getDesc(std::string name);
private:
    // key is ThreadInfo::name
	std::map<std::string, pthread_t *> threadList;
    std::vector<ThreadInfo *> infoList;
    SpinLock lock;
};

ThreadInfo *ThreadManager::createThreadInfo(ThreadRoutine routine, std::string name) {
    ThreadInfo *info = new ThreadInfo;
    info->routine = routine;
    info->name = name;
    info->logLock = &lock;
    infoList.push_back(info);
    return info;
}

pthread_t ThreadManager::getDesc(std::string name) {
    return *(pthread_t *)threadList[name];
}
