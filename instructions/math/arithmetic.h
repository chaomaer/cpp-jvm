//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_ARITHMETIC_H
#define CPP_JVM2_ARITHMETIC_H
#include "instructions/base/instruction.h"

class I_REM : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_ADD : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class L_ADD : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_SUB : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_MUL : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_INC : public Instruction {
public:
    int index;
    int _const;
    void fetch_operands(BytecodeReader* reader);
    void execute(Frame* frame);
};

#endif //CPP_JVM2_ARITHMETIC_H
