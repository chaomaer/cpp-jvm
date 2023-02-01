//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_SWAP_H
#define CPP_JVM2_SWAP_H
#include "instructions/base/instruction.h"

class SWAP : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_SWAP_H
