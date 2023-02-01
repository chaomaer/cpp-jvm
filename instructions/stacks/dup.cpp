//
// Created by chaomaer on 2023/1/31.
//

#include "dup.h"

void DUP::execute(Frame *frame) {
    auto slot = frame->operation_stack->top();
    frame->operation_stack->push_slot(slot);
}
