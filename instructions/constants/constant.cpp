//
// Created by chaomaer on 2023/1/31.
//

#include "constant.h"
#include "heap/rtConsts.h"
#include <iostream>
#include "core/frame.h"
#include "common/debug.h"

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

void L_CONST_0::execute(Frame *frame) {
    frame->operation_stack->push_long(0);
}

void L_CONST_1::execute(Frame *frame) {
    frame->operation_stack->push_long(1);
}

void I_CONST_0::execute(Frame *frame) {
    frame->operation_stack->push_int(0);
}

void I_CONST_1::execute(Frame *frame) {
    frame->operation_stack->push_int(1);
}

void I_CONST_2::execute(Frame *frame) {
    frame->operation_stack->push_int(2);
}

void I_CONST_3::execute(Frame *frame) {
    frame->operation_stack->push_int(3);
}

void I_CONST_4::execute(Frame *frame) {
    frame->operation_stack->push_int(4);
}

void I_CONST_5::execute(Frame *frame) {
    frame->operation_stack->push_int(5);
}

void LDC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto stack = frame->operation_stack;
    auto val = cp->at(index);
    if (val->type == CONSTANT_Integer) {
        stack->push_int(((RTInt_Const *) (val))->val);
    }else if (val -> type == CONSTANT_Float) {
        stack->push_float(((RTFloat_Const*)val)->val);
    }else if (val -> type == CONSTANT_Class) {
        auto class_ref = (ClassRef*)val;
        auto _class = class_ref->resolve_class_ref();
        stack->push_ref(_class->jClass);
    }else if (val -> type == CONSTANT_String){
        auto str = ((RTString_Const*)(val))->val;
        auto class_loader = frame->method->_class->class_loader;
        auto object = new_string_object(class_loader, str);
        //std::cout << "[LDC:] put string => " << str << std::endl;
        stack->push_ref(object);
    }else {
        assert(false && "ldc error => unreachable");
    }
}

void LDC_W::execute(Frame *frame) {
    ((LDC*)this)->execute(frame);
}

void LDC2_W::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto stack = frame->operation_stack;
    auto val = cp->at(index);
    if (val -> type == CONSTANT_Long) {
        stack->push_long(((RTLong_Const*)val)->val);
    }else if (val -> type == CONSTANT_Double) {
        stack->push_double(((RTDouble_Const *) val)->val);
    }else {
        DEBUG_MSG("load unsupported const");
    }
}
