//
// Created by chaomaer on 2023/1/31.
//

#include "constant.h"
#include "heap/rtConsts.h"
#include <iostream>

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

void IDC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto stack = frame->operation_stack;
    auto val = cp->at(index);
    if (val->type == CONSTANT_Integer) {
        stack->push_int(((RTInt_Const*)(val))->val);
    }else if (val -> type == CONSTANT_Long) {
        stack->push_long(((RTLong_Const*)val)->val);
    }else if (val -> type == CONSTANT_Float) {
        stack->push_float(((RTFloat_Const*)val)->val);
    }else if (val -> type == CONSTANT_Double) {
        stack->push_double(((RTDouble_Const*)val)->val);
    }else if (val -> type == CONSTANT_Class) {
        std::cout << "load class unsupported" << std::endl;
    }else {
        std::cout << "load unsupported const" << std::endl;
    }
}
