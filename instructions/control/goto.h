//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_GOTO_H
#define CPP_JVM2_GOTO_H
#include "instructions/base/instruction.h"

class GOTO : public BranchInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_GOTO_H
