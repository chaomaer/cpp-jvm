//
// Created by chaomaer on 2023/3/6.
//

#ifndef CPP_JVM2_MONITOR_LOCK_H
#define CPP_JVM2_MONITOR_LOCK_H
#include "thread"
#include "atomic"
#include "optional"
#include "mutex"
class MonitorLock {
private:
    std::atomic<bool> mutex{false};
    int cnt{0};
    std::thread::id tid{};
    std::recursive_mutex _lock;
public:
    void lock();
    void unlock();
};

#endif //CPP_JVM2_MONITOR_LOCK_H
