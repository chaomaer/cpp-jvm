//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_THREAD_H
#define CPP_JVM_THREAD_H
#include "stack"
#include "frame.h"
#include "heap/class.h"

class Frame;
class Method;
class Thread {
public:
    int pc;
    std::stack<Frame*> stack;
    Frame* new_frame(Method* method);
    Frame* pop_frame();
    Frame* top_frame();
    bool empty_frame();
    void push_frame(Frame* frame);
};

#endif //CPP_JVM_THREAD_H
