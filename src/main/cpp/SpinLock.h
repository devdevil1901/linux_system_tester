#pragma once

#include <atomic>
#include <string>

class SpinLock {
public:
    void lock();
    void unlock();
	bool tryLock();
private:
    std::atomic_flag spinLock;
};
