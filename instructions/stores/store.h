//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_STORE_H
#define CPP_JVM2_STORE_H
#include "instructions/base/instruction.h"

void l_store(Frame* frame, int index);
void i_store(Frame* frame, int index);

class L_STORE : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class L_STORE_1 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class L_STORE_2 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_STORE : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class I_STORE_0 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_STORE_1 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_STORE_2 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_STORE_3 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_STORE : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class A_STORE_0 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};


class A_STORE_1 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_STORE_2 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_STORE_3 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_STORE_4 : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};
#endif //CPP_JVM2_STORE_H
