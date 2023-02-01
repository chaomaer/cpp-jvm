//
// Created by chaomaer on 2023/1/31.
//

#include "pop.h"

void POP::execute(Frame *frame) {
    frame->operation_stack->pop_slot();
}
