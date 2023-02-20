//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_TYPE_H
#define CPP_JVM2_TYPE_H
#include "unordered_map"
#include "string"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

enum ARRAY_TYPE {
    AT_OBJECT = -1,
    AT_BOOLEAN = 4,
    AT_CHAR = 5,
    AT_FLOAT = 6,
    AT_DOUBLE = 7,
    AT_BYTE = 8,
    AT_SHORT = 9,
    AT_INT = 10,
    AT_LONG = 11
};

static std::unordered_map<std::string, std::string> primitive_types = {
        {"void", "V"},
        {"int", "I"},
        {"long", "J"},
        {"char", "C"},
        {"float", "F"},
        {"double", "D"},
        {"byte", "B"},
        {"short", "S"},
        {"boolean", "Z"}
};


#endif //CPP_JVM2_TYPE_H
