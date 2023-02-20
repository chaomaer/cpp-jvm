//
// Created by chaomaer on 2023/2/16.
//

#ifndef CPP_JVM2_OBJECT_H
#define CPP_JVM2_OBJECT_H
#include "core/native.h"
#include "core/frame.h"

class NativeObject {
private:
    static void getClass(Frame* frame);
    static void getPrimitiveClass(Frame* frame);
    static void getName0(Frame* frame);
    static void desiredAssertionStatus0(Frame* frame);
public:
    static void init(NativeRegistry* registry);
};



#endif //CPP_JVM2_OBJECT_H
