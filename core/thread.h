//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_THREAD_H
#define CPP_JVM_THREAD_H
#include "stack"
#include "frame.h"
#include "heap/class.h"
#include "thread"
#include "interpreter.h"

class Frame;
class Method;
class VMThread;
class FrameManager{
public:
    VMThread* vm_thread;
public:
    int pc;
    std::stack<Frame*> stack;
    Frame* new_frame(Method* method);
    Frame* pop_frame();
    Frame* top_frame();
    bool empty_frame();
    void push_frame(Frame* frame);
};
class Interpreter;
class VMThread {
public:
    VMThread(Method* method);
    VMThread(FrameManager* manager);
    FrameManager* manager;
    Interpreter* interpreter;
public:
    std::thread* start();
};

#endif //CPP_JVM_THREAD_H
