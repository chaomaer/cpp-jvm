//
// Created by chaomaer on 2023/1/31.
//

#include "dup.h"

void DUP::execute(Frame *frame) {
    auto slot = frame->operation_stack->top();
    frame->operation_stack->push_slot(slot);
}

void DUP2::execute(Frame *frame) {
    auto val1 = frame->operation_stack->pop_slot();
    auto val2 = frame->operation_stack->pop_slot();
    frame->operation_stack->push_slot(val2);
    frame->operation_stack->push_slot(val1);
    frame->operation_stack->push_slot(val2);
    frame->operation_stack->push_slot(val1);
}

void DUP_X1::execute(Frame *frame) {
    auto val1 = frame->operation_stack->pop_slot();
    auto val2 = frame->operation_stack->pop_slot();
    frame->operation_stack->push_slot(val1);
    frame->operation_stack->push_slot(val2);
    frame->operation_stack->push_slot(val1);
}
