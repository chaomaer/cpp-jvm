//
// Created by chaomaer on 2023/2/1.
//
#include "common/type.h"
#include "interpreter.h"
#include "frame.h"
#include "instructions/factory.h"
#include "iostream"

void Interpreter::run(Method* method) {
    auto manager = new FrameManager();
    auto* frame = manager->new_frame(method);
    manager->push_frame(frame);
    loop(manager);
}

void Interpreter::loop(FrameManager* manager) {
    auto reader = new BytecodeReader();
    while (true) {
        if (manager->empty_frame()) {
            break;
        }
        auto frame = manager->top_frame();
        auto class_name = frame->method->_class->name;
        auto method_name = frame->method->name;
        // start a new std::thread
        auto desc = frame->method->descriptor;
        {
            //record cur_pc in thread.pc
            reader->reset(frame->method->code, frame->pc);
            uint8 op_code = reader->read_uint8();
            //printf("op_code is %x with id: %p \n", op_code, std::this_thread::get_id());
            //std::cout << "class_name: " << class_name << " name: "<< method_name << std::endl;
            auto inst = InstructionFactory::new_instruction(op_code);
            if (inst == nullptr) {
                std::cout << "class_name: " << class_name << " name: "<< method_name << std::endl;
                exit(-1);
            }
            inst->fetch_operands(reader);
            frame->pc = reader->pc;
            if (method_name == "start0" && desc == "()V" && op_code == 0xfe) {
                // start a new std::thread
                auto x = start_new_loop(frame);
                vm->invoked_threads->push_back(x);
            }else{
                inst->execute(frame);
            }
            delete inst;
            if(!InstructionFactory::is_return(op_code)) {
                frame->manager->pc = frame->pc;
            }
        }
    }
    for (auto& t1 :  *vm->invoked_threads) {
            t1->t->join();
    }
    for (auto& _vm: *vm->invoked_threads) {
        delete _vm;
    }
    delete reader;
}

Interpreter::Interpreter(VMThread *vm):vm(vm) {

}

VMThread *Interpreter::start_new_loop(Frame *frame) {
    auto _this = frame->local_vars->get_ref(0);
    auto class_loader = frame->method->_class->class_loader;
    auto thread_class = class_loader->load_class("java/lang/Thread");
    auto target_m = thread_class->lookup_method("run", "()V");
    // 将 _this 推入operation_stack
    auto manager = new FrameManager;
    auto new_frame = manager->new_frame(target_m);
    new_frame->local_vars->set_ref(0, _this);
    manager->push_frame(new_frame);
    return new VMThread(manager);
}
