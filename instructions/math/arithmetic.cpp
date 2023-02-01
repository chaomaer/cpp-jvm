//
// Created by chaomaer on 2023/2/1.
//

#include "arithmetic.h"
#include "iostream"

void I_REM::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto v2 = stack->pop_int();
    auto v1 = stack->pop_int();
    if (v2 == 0) {
        std::cout << "a/b and b = 0" << std::endl;
        exit(-1);
    }
    stack->push_int(v1 % v2);
}

void I_ADD::execute(Frame *frame) {
    auto* stack = frame->operation_stack;
    auto v2 = stack->pop_int();
    auto v1 = stack->pop_int();
    stack->push_int(v1 + v2);
}

void I_INC::fetch_operands(BytecodeReader *reader) {
    index = reader->read_uint8();
    _const = reader->read_uint8();
}

void I_INC::execute(Frame *frame) {
    auto local_vars = frame->local_vars;
    auto val = local_vars->get_int(index);
    local_vars->set_int(index, _const + val);
}
