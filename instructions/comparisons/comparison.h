//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_COMPARISON_H
#define CPP_JVM2_COMPARISON_H
#include "instructions/base/instruction.h"

class IF_I_CMP_GT : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_I_CMP_GE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_I_CMP_LE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_I_CMP_NE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_I_CMP_LT : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_EQ : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_NE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_LE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_GE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_LT : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_A_CMP_NE : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_NON_NULL : public BranchInstruction {
public:
    void execute(Frame* frame);
};

class IF_NULL : public BranchInstruction {
public:
    void execute(Frame* frame);
};
#endif //CPP_JVM2_COMPARISON_H
