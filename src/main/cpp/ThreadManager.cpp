#include "ThreadManager.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <algorithm>
#include <iostream>

ThreadManager::ThreadManager() {
}

ThreadManager::~ThreadManager() {
	for (auto &kv : threadList) {
		delete kv.second;
	}
	threadList.clear();
    std::for_each(infoList.begin(), infoList.end(), [](auto &element) {
        delete element;
        element = NULL;
    });
}

void ThreadManager::waiting(std::string name) {
	if (name.empty()) {
        lock.lock();
        std::cout << "trying to wait" << std::endl;
        lock.unlock();
        for(std::map<std::string, pthread_t *>::iterator ir = threadList.begin(); ir != threadList.end(); ir++) {
			int status;
			pthread_join(*ir->second, (void **)&status);
		}
		return;
	}
	auto ir = threadList.find(name);
	if (ir == threadList.end()) {
        perror("Can't find  thread");
		return;
	}
	int status;
	pthread_join(*(ir->second), (void **)&status);
}

bool ThreadManager::startPrimitiveThread(ThreadInfo *threadInfo) {
	pthread_t *td = new pthread_t;
	int tid = pthread_create(td, NULL, threadInfo->routine, (void *)threadInfo);

	if (tid < 0) {
        perror("failed to create thread: ");
		delete td;
		return false;
    }
    threadList[threadInfo->name] = td;
	return true;
}
