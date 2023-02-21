//
// Created by chaomaer on 2023/2/21.
//

#include "monitor.h"

void MONITOR_ENTER::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    stack->pop_ref();
}

void MONITOR_EXIT::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    stack->pop_ref();
}
