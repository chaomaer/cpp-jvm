//
// Created by chaomaer on 2023/2/9.
//

#include "return.h"
#include "iostream"

void RETURN::execute(Frame *frame) {
    auto cur_frame = frame->manager->pop_frame();
    delete cur_frame;
}

void I_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->manager->pop_frame();
    auto invoke_frame = frame->manager->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_int();
    //std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_int(ret_val);
    delete cur_frame;
}

void L_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->manager->pop_frame();
    auto invoke_frame = frame->manager->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_long();
    //std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_long(ret_val);
    delete cur_frame;
}

void A_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->manager->pop_frame();
    auto invoke_frame = frame->manager->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_ref();
    //std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_ref(ret_val);
    delete cur_frame;
}
