//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_INTERPRETER_H
#define CPP_JVM2_INTERPRETER_H
#include "parser/classFile.h"
#include "frame.h"

class FrameManager;
class Method;
class Frame;
class Interpreter {
public:
    std::vector<std::thread*>* invoked_threads;
public:
    Interpreter();
    void run(Method* classFile);
    void loop(FrameManager* manager);
    std::thread* start_new_loop(Frame* frame);
};

#endif //CPP_JVM2_INTERPRETER_H
