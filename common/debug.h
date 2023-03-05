//
// Created by chaomaer on 2023/3/5.
//

#ifndef CPP_JVM2_DEBUG_H
#define CPP_JVM2_DEBUG_H
#ifdef DEBUG
#include "iostream"
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#endif //CPP_JVM2_DEBUG_H
