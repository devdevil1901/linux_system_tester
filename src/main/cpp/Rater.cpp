#include "Rater.h"
#include "SchedManager.h"
#include <iostream>
#include <unistd.h>

SchedRater::SchedRater() {
}

SchedRater::~SchedRater() {
}

std::string SchedRater::evaluate() {
    std::string report = "-> evaluating process priority\n";
    report += evalProcessPriority();
    report += "-> evaluating thread priority\n";
    report += evalThreadPriority();
    return report;
}

std::string SchedRater::evalProcessPriority() {
    int prev = scheduler.getPriority();
    scheduler.changePriority(7, true);
    int now = scheduler.getPriority();
    if (prev == now) {
        return "[Failed][evalProcessPriority] They are not same\n";
    }
    return "[Success][evalProcessPriority]\n";
}

std::string SchedRater::evalThreadPriority() {
    threadManager.startPrimitiveThread(
        threadManager.createThreadInfo(
            (ThreadRoutine)scheduleMe,
            "thread1"
        )
    );
    threadManager.startPrimitiveThread(
        threadManager.createThreadInfo(
            (ThreadRoutine)scheduleMe,
            "thread2"
        )
    );
    threadManager.startPrimitiveThread(
        threadManager.createThreadInfo(
            (ThreadRoutine)scheduleMe,
            "thread3"
        )
    );
    pthread_t td = threadManager.getDesc("thread1");
    scheduler.changeThreadPriority(td, 2, 1);// 0 -> SCHED_NORMAL
    sleep(1);
    int prio = scheduler.getThreadPriority(td);
    int prio2 = scheduler.getThreadPriority(threadManager.getDesc("thread2"));
    int prio3 = scheduler.getThreadPriority(threadManager.getDesc("thread3"));
  
    std::string policy = scheduler.getThreadPolicy(td);
    std::string policy2 = scheduler.getThreadPolicy(threadManager.getDesc("thread2"));
    std::string policy3 = scheduler.getThreadPolicy(threadManager.getDesc("thread3"));
    std::string report = "priority: " + std::to_string(prio) + ", " + std::to_string(prio2) + ", " + std::to_string(prio3) + "\n";
    report += "policy: " + policy + "\n";  
    report += "policy2: " + policy2 + "\n";  
    report += "policy3: " + policy3 + "\n";  
    threadManager.waiting("");
    return report;
}

void SchedRater::scheduleMe(ThreadInfo *param) {
    sleep(2);
    for(int i = 0; i<1000; i++) {
        param->logLock->lock();
        std::cout << param->name << std::endl;
        param->logLock->unlock();
    }
}
