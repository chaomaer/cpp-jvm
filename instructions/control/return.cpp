//
// Created by chaomaer on 2023/2/9.
//

#include "return.h"
#include "iostream"

void RETURN::execute(Frame *frame) {
    frame->thread->pop_frame();
}

void I_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->thread->pop_frame();
    auto invoke_frame = frame->thread->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_int();
    std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_int(ret_val);
}

void L_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->thread->pop_frame();
    auto invoke_frame = frame->thread->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_long();
    std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_long(ret_val);
}

void A_RETURN::execute(Frame *frame) {
    auto cur_frame = frame->thread->pop_frame();
    auto invoke_frame = frame->thread->top_frame();
    auto ret_val = cur_frame->operation_stack->pop_ref();
    std::cout << "ret_val: " << ret_val << std::endl;
    invoke_frame->operation_stack->push_ref(ret_val);
}
