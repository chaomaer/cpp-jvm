//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_INTERPRETER_H
#define CPP_JVM2_INTERPRETER_H
#include "parser/classFile.h"
#include "frame.h"

class Interpreter {
public:
    void run(Method* classFile);
    void loop(Thread* thread);
};

#endif //CPP_JVM2_INTERPRETER_H
