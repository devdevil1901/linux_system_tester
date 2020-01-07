#pragma once

#include <string>
#include "SchedManager.h"
#include "ThreadManager.h"

class Rater {
public:
	virtual ~Rater() {}

	virtual std::string evaluate() = 0;
};

class SchedRater : public Rater {
public:
	SchedRater();
	virtual ~SchedRater();

	virtual std::string evaluate();
    static void scheduleMe(ThreadInfo *param);

private:
	std::string evalProcessPriority();
	std::string evalThreadPriority();
    SchedManager scheduler;
    ThreadManager threadManager;
};

