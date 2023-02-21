//
// Created by chaomaer on 2023/2/1.
//
#include "common/type.h"
#include "interpreter.h"
#include "frame.h"
#include "instructions/factory.h"
#include "iostream"

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
        auto class_name = frame->method->_class->name;
        auto method_name = frame->method->name;
        // record cur_pc in thread.pc
        reader->reset(frame->method->code, frame->pc);
        uint8 op_code = reader->read_uint8();
        printf("op_code is %x\n", op_code);
        std::cout << "class_name: " << class_name << " name: "<< method_name << std::endl;
        auto inst = InstructionFactory::new_instruction(op_code);
        if (inst == nullptr) {
            std::cout << "class_name: " << class_name << " name: "<< method_name << std::endl;
            exit(-1);
        }
        inst->fetch_operands(reader);
        frame->pc = reader->pc;
        inst->execute(frame);
        frame->thread->pc = frame->pc;

        // print local_var and stack
//        frame->local_vars->print();
//        frame->operation_stack->print();
    }
}
