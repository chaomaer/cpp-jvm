//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_POP_H
#define CPP_JVM2_POP_H
#include "instructions/base/instruction.h"

class POP : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_POP_H
