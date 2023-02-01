//
// Created by chaomaer on 2023/1/31.
//

#include "swap.h"

void SWAP::execute(Frame *frame) {
    auto slot1 = frame->operation_stack->pop_slot();
    auto slot2 = frame->operation_stack->pop_slot();
    frame->operation_stack->push_slot(slot1);
    frame->operation_stack->push_slot(slot2);
}
