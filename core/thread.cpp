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
    invoked_threads = std::vector<std::thread>();
    manager = new FrameManager;
    auto frame = manager->new_frame(method);
    manager->push_frame(frame);
    interpreter = new Interpreter;
    manager->vm_thread = this;
}

VMThread::VMThread(FrameManager *manager): manager(manager) {
    invoked_threads = std::vector<std::thread>();
    interpreter = new Interpreter;
    manager->vm_thread = this;
    //std::cout << "======== invoke thread" << invoked_threads->size() << " "<< invoked_threads << std::endl;
    std::cout << "error " << this << std::endl;
    //std::cout << "-----" << manager->vm_thread->invoked_threads << std::endl;
    std::cout << "======== manager " << manager << std::endl;
}

std::thread * VMThread::start() {
    std::cout << "======== invoke thread " << &invoked_threads << std::endl;
    std::cout << "error " << this << std::endl;
    auto t = new std::thread(&Interpreter::loop, interpreter, manager);
    return t;
}

void VMThread::join() {
    if (manager->vm_thread == nullptr) {
        return;
    }
    // join the threads
    //auto t = manager->vm_thread->invoked_threads->at(0);
    //printf("[IN JOIN] thread: %p wait for son threads %p \n", std::this_thread::get_id(), t->get_id());
//    std::cout << std::this_thread::get_id <<" wait for son threads" << std::endl;
    //std::cout << "thread size: " << manager->vm_thread->invoked_threads->size() << std::endl;
    for (auto &t1 :  manager->vm_thread->invoked_threads) {
        t1.join();
    }
}

//VMManager* VMManager::instance = nullptr;
//
//VMManager *VMManager::get_manager() {
//    if (instance == nullptr) {
//        instance = new VMManager();
//    }
//    return instance;
//}
//
//VMManager::VMManager() {
//    threads = new std::vector<std::thread*>;
//}
