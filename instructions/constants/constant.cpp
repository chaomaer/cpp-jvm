//
// Created by chaomaer on 2023/1/31.
//

#include "constant.h"

void A_CONST_NULL::execute(Frame *frame) {
    frame->operation_stack->push_ref(nullptr);
}

void D_CONST_0::execute(Frame *frame) {
    frame->operation_stack->push_double(0);
}

void I_CONST_M1::execute(Frame *frame) {
    frame->operation_stack->push_int(-1);
}

void B_I_PUSH::fetch_operands(BytecodeReader *reader) {
    val = reader->read_uint8();
}

void B_I_PUSH::execute(Frame *frame) {
    frame->operation_stack->push_int(val);
}

void S_I_PUSH::fetch_operands(BytecodeReader *reader) {
    val = reader->read_uint16();
}

void S_I_PUSH::execute(Frame *frame) {
    frame->operation_stack->push_int(val);
}

void I_CONST_0::execute(Frame *frame) {
    frame->operation_stack->push_int(0);
}

void I_CONST_1::execute(Frame *frame) {
    frame->operation_stack->push_int(1);
}
