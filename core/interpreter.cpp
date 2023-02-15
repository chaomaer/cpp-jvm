//
// Created by chaomaer on 2023/2/1.
//
#include "common/type.h"
#include "interpreter.h"
#include "frame.h"
#include "instructions/factory.h"

void Interpreter::run(Method* method) {
    auto thread = new Thread();
    auto* frame = thread->new_frame(method);
    thread->push_frame(frame);
    loop(thread);
}

void Interpreter::loop(Thread* thread) {
    auto reader = new BytecodeReader();
    while (true) {
        if (thread->empty_frame()) {
            break;
        }
        auto frame = thread->top_frame();
        // record cur_pc in thread.pc
        reader->reset(frame->method->code, frame->pc);
        uint8 op_code = reader->read_uint8();
        //printf("op_code is %x\n", op_code);
        auto inst = InstructionFactory::new_instruction(op_code);
        inst->fetch_operands(reader);
        frame->pc = reader->pc;
        inst->execute(frame);
        frame->thread->pc = frame->pc;

        // print local_var and stack
//        frame->local_vars->print();
//        frame->operation_stack->print();
    }
}
