//
// Created by USER on 2019-08-15.
//

#include "SpinLock.h"

void SpinLock::lock() {
    while(spinLock.test_and_set((std::memory_order_acquire))) {}
}

void SpinLock::unlock() {
    spinLock.clear(std::memory_order_release);
}

bool SpinLock::tryLock() {
    return !spinLock.test_and_set(std::memory_order_acquire);
}
