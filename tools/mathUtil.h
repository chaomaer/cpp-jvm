//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_MATHUTIL_H
#define CPP_JVM2_MATHUTIL_H
#include "common/type.h"
#include "string"
class MathUtil{
public:
    static float bytes_to_float(uint8 byte[4]);
    static double bytes_to_double(uint8 byte[4]);
    static std::string byte_to_string(uint8* bytes);
};

#endif //CPP_JVM2_MATHUTIL_H
