//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_BUFFEREDINPUTSTREAM_H
#define CPP_JVM2_BUFFEREDINPUTSTREAM_H
#include "common/type.h"
#include "classFile.h"
#include "stdio.h"
#define BUFFER_SIZE 256
class BufferedInputStream{
public:
    int _index;
    FILE* _fp;
    char buffer[BUFFER_SIZE];
public:
    ~BufferedInputStream();
    BufferedInputStream(const char* fileName);
    BufferedInputStream(std::string fileName);
    uint8 read_uint8();
    uint16 read_uint16();
    uint32 read_uint32();
    void discard_uint8s(int size);
    float read_float();
    double read_double();
    uint64 read_uint64();
};


#endif //CPP_JVM2_BUFFEREDINPUTSTREAM_H
