//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_CONSTANT_H
#define CPP_JVM2_CONSTANT_H
#include "instructions/base/instruction.h"

class Nop : public NoOperandsInstruction {

};

class A_CONST_NULL : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class D_CONST_0 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_0 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_1 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_M1 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class B_I_PUSH : public Instruction {
public:
    int val;
public:
    void fetch_operands(BytecodeReader* reader);
    void execute(Frame* frame);
};

class S_I_PUSH : public Instruction {
public:
    int val;
public:
    void fetch_operands(BytecodeReader* reader);
    void execute(Frame* frame);
};


#endif //CPP_JVM2_CONSTANT_H
