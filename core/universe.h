//
// Created by chaomaer on 2023/2/19.
//

#ifndef CPP_JVM2_UNIVERSE_H
#define CPP_JVM2_UNIVERSE_H
#include "native.h"

class Universe {
public:
    static NativeRegistry* registry;
public:
    static void init();
    static void clean_up();
};

#endif //CPP_JVM2_UNIVERSE_H
