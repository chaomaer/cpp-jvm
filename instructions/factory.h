//
// Created by chaomaer on 2023/2/1.
//

#ifndef CPP_JVM2_FACTORY_H
#define CPP_JVM2_FACTORY_H
#include "instructions/base/instruction.h"

class InstructionFactory {
public:
    static Instruction* new_instruction(int op_code);
};

#endif //CPP_JVM2_FACTORY_H
