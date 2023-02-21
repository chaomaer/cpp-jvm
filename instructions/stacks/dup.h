//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_DUP_H
#define CPP_JVM2_DUP_H
#include "instructions/base/instruction.h"

class DUP : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class DUP2 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class DUP_X1 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_DUP_H
