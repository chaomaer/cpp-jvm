//
// Created by chaomaer on 2023/2/21.
//

#ifndef CPP_JVM2_MONITOR_H
#define CPP_JVM2_MONITOR_H
#include "instructions/base/instruction.h"

class MONITOR_ENTER : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class MONITOR_EXIT : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_MONITOR_H

