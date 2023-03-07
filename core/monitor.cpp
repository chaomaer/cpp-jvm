//
// Created by chaomaer on 2023/3/6.
//

#include "monitor.h"
#include "iostream"
#include "sstream"

std::thread::id thread_to_int() {
    return std::this_thread::get_id();
}

void MonitorLock::lock() {
    // re-enter
    if (tid == std::this_thread::get_id()) {

    }else {
        bool expect = false;
        while (!mutex.compare_exchange_strong(expect, true)) {
            expect = false;
        }
        tid = thread_to_int();
    }
    cnt++;
//    _lock.lock();
}

void MonitorLock::unlock() {
    assert(tid == thread_to_int());
    cnt--;
    if(cnt == 0) {
        tid = {};
        mutex = false;
    }
//    _lock.unlock();
}
