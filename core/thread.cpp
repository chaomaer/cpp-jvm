//
// Created by chaomaer on 2023/1/31.
//

#include "thread.h"
#include "universe.h"
#include "iostream"

Frame *FrameManager::new_frame(Method* method) {
    return new Frame(this, method);
}

void FrameManager::push_frame(Frame *frame) {
    stack.push(frame);
}

Frame *FrameManager::pop_frame() {
    auto frame = stack.top();
    stack.pop();
    return frame;
}

Frame *FrameManager::top_frame() {
    return stack.top();
}

bool FrameManager::empty_frame() {
    return stack.size() == 0;
}

VMThread::VMThread(Method *method) {
    invoked_threads = new std::vector<VMThread*>;
    manager = new FrameManager;
    auto frame = manager->new_frame(method);
    manager->push_frame(frame);
    interpreter = new Interpreter(this);
    start();
}

VMThread::VMThread(FrameManager *manager): manager(manager) {
    invoked_threads = new std::vector<VMThread*>;
    interpreter = new Interpreter(this);
    start();
}

void VMThread::start() {
    t = new std::thread(&Interpreter::loop, interpreter, manager);
}

VMThread::~VMThread() {
    delete t;
    delete invoked_threads;
    if (manager != nullptr) {
        delete manager;
    }
    if (interpreter != nullptr) {
        delete interpreter;
    }
}
