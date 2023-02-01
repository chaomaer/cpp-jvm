//
// Created by chaomaer on 2023/1/31.
//

#include "conversion.h"

void D_2_I::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto d = stack->pop_double();
    stack->push_int(int(d));
}
