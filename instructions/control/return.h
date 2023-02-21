//
// Created by chaomaer on 2023/2/9.
//

#ifndef CPP_JVM2_RETURN_H
#define CPP_JVM2_RETURN_H
#include "instructions/base/instruction.h"

class RETURN : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_RETURN : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class L_RETURN : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_RETURN : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_RETURN_H
