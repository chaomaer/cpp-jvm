//
// Created by chaomaer on 2023/1/31.
//

#include "load.h"

void _iload(Frame* frame, int index) {
    int val = frame->local_vars->get_int(index);
    frame->operation_stack->push_int(val);
}

void _aload(Frame* frame, int index) {
    auto val = frame->local_vars->get_ref(index);
    frame->operation_stack->push_ref(val);
}

void I_LOAD::execute(Frame *frame) {
    _iload(frame, this->index);
}

void I_LOAD_1::execute(Frame *frame) {
    _iload(frame, 1);
}

void I_LOAD_2::execute(Frame *frame) {
    _iload(frame, 2);
}

void I_LOAD_3::execute(Frame *frame) {
    _iload(frame, 3);
}

void A_LOAD::execute(Frame *frame) {
    _aload(frame, index);
}

void A_LOAD_0::execute(Frame *frame) {
    _aload(frame, 0);
}

void A_LOAD_1::execute(Frame *frame) {
    _aload(frame, 1);
}

void A_LOAD_2::execute(Frame *frame) {
    _aload(frame, 2);
}

void A_LOAD_3::execute(Frame *frame) {
    _aload(frame, 3);
}

void I_LOAD_0::execute(Frame *frame) {
    _iload(frame, 0);
}
