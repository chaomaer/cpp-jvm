//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_FRAME_H
#define CPP_JVM_FRAME_H

#include "vector"
#include "stack"
#include "thread.h"
#include "heap/class.h"
#include "common/localArray.h"

class Method;
class FrameManager;
class Frame {
public:
    int pc;
    int max_stack;
    int max_locals;
    FrameManager* manager;
    Method* method;
public:
    OperationLocalVars *local_vars;
    OperationStack *operation_stack;
public:
    ~Frame();
    Frame(int maxStack, int maxLocals, FrameManager* manager, Method* method);
    Frame(FrameManager* manager, Method* method);
    void branch(short offset);
};

#endif //CPP_JVM_FRAME_H
