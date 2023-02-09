//
// Created by chaomaer on 2023/2/1.
//
#include "common/type.h"
#include "interpreter.h"
#include "frame.h"
#include "instructions/factory.h"

void Interpreter::run(Method* method) {
    auto byte_code = method->code;
    auto max_stack = method->max_stack;
    auto max_locals = method->max_locals;
    auto thread = new Thread();
    auto frame = new Frame(max_stack, max_locals, thread, method);
    loop(frame, byte_code);
}

void Interpreter::loop(Frame *frame, uint8 *byte_code) {
    auto reader = new BytecodeReader(byte_code);
    while (1) {
        // record cur_pc in thread.pc
        reader->reset_cp(frame->thread->pc);
        uint8 op_code = reader->read_uint8();
        printf("op_code is %x\n", op_code);
        auto inst = InstructionFactory::new_instruction(op_code);
        inst->fetch_operands(reader);
        frame->pc = reader->pc;
        inst->execute(frame);
        frame->thread->pc = frame->pc;

        // print local_var and stack
        frame->local_vars->print();
        frame->operation_stack->print();
    }
}
