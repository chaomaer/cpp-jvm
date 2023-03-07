//
// Created by chaomaer on 2023/2/21.
//

#include "monitor.h"
#include "common/debug.h"

void MONITOR_ENTER::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto object = stack->pop_ref();
    object->lock.lock();
    DEBUG_MSG("lock lock " << &object->lock << " " << std::this_thread::get_id());
}

void MONITOR_EXIT::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto object = stack->pop_ref();
    object->lock.unlock();
    DEBUG_MSG("unlock lock " << &object->lock << " " << std::this_thread::get_id());
}
