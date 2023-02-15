//
// Created by chaomaer on 2023/1/31.
//

#include "store.h"

void l_store(Frame* frame, int index) {
    long val = frame->operation_stack->pop_long();
    frame->local_vars->set_long(index, val);
}

void i_store(Frame* frame, int index) {
    int val = frame->operation_stack->pop_int();
    frame->local_vars->set_int(index, val);
}

void a_store(Frame* frame, int index) {
    auto val = frame->operation_stack->pop_ref();
    frame->local_vars->set_ref(index, val);
}

void L_STORE::execute(Frame *frame) {
    l_store(frame, index);
}

void L_STORE_1::execute(Frame *frame) {
    l_store(frame, 1);
}

void L_STORE_2::execute(Frame *frame) {
    l_store(frame, 2);
}

void I_STORE::execute(Frame *frame) {
    i_store(frame, index);
}

void I_STORE_1::execute(Frame *frame) {
    i_store(frame, 1);
}

void I_STORE_2::execute(Frame *frame) {
    i_store(frame, 2);
}

void I_STORE_3::execute(Frame *frame) {
    i_store(frame, 3);
}

void A_STORE::execute(Frame *frame) {
    a_store(frame, index);
}

void A_STORE_1::execute(Frame *frame) {
    a_store(frame, 1);
}

void A_STORE_2::execute(Frame *frame) {
    a_store(frame, 2);
}

void A_STORE_3::execute(Frame *frame) {
    a_store(frame, 3);
}

void A_STORE_4::execute(Frame *frame) {
    a_store(frame, 4);
}
