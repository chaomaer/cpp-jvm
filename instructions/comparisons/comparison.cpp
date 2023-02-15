//
// Created by chaomaer on 2023/2/1.
//

#include "comparison.h"

void IF_I_CMP_GT::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto v2 = stack->pop_int();
    auto v1 = stack->pop_int();
    if (v1 > v2) {
        frame->branch(offset);
    }
}

void IF_I_CMP_GE::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto v2 = stack->pop_int();
    auto v1 = stack->pop_int();
    if (v1 >= v2) {
        frame->branch(offset);
    }
}

void IF_I_CMP_LE::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto v2 = stack->pop_int();
    auto v1 = stack->pop_int();
    if (v1 <= v2) {
        frame->branch(offset);
    }
}

void IF_EQ::execute(Frame *frame) {
    auto val = frame->operation_stack->pop_int();
    if (val == 0) {
        frame->branch(offset);
    }
}

void IF_A_CMP_NE::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto ref2 = stack->pop_ref();
    auto ref1 = stack->pop_ref();
    if (ref1 != ref2) {
        frame->branch(offset);
    }
}
