//
// Created by chaomaer on 2023/2/9.
//

#ifndef CPP_JVM2_REFERENCE_H
#define CPP_JVM2_REFERENCE_H
#include "instructions/base/instruction.h"

class NEW : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class PUT_STATIC : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class GET_STATIC : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class PUT_FIELD : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class GET_FIELD : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class IS_INSTANCE_OF : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class CHECK_CAST : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class INVOKE_SPECIAL : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class INVOKE_VIRTUAL : public Index16Instruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_REFERENCE_H
