//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_LOAD_H
#define CPP_JVM2_LOAD_H
#include "instructions/base/instruction.h"

void _iload(Frame* frame, int index);

class I_LOAD : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class I_LOAD_1 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_LOAD_2 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_LOAD_H
