//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_CONSTANT_H
#define CPP_JVM2_CONSTANT_H
#include "instructions/base/instruction.h"
#include "parser/constantInfo.h"

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

class I_CONST_2 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_3 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_4 : public NoOperandsInstruction {
    void execute(Frame* frame);
};

class I_CONST_5 : public NoOperandsInstruction {
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

class LDC : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class LDC_W : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class LDC2_W : public Index16Instruction {
public:
    void execute(Frame* frame);
};


#endif //CPP_JVM2_CONSTANT_H
