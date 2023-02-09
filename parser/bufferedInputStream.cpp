//
// Created by chaomaer on 2023/1/29.
//

#include "bufferedInputStream.h"
#include "iostream"

uint8 BufferedInputStream::read_uint8() {
    if (_index >= BUFFER_SIZE) {
        fread(buffer, BUFFER_SIZE, 1, _fp);
        _index = 0;
    }
    return buffer[_index++];
}

uint16 BufferedInputStream::read_uint16() {
    uint16 b1 = read_uint8() & 0xff;
    uint16 b2 = read_uint8() & 0xff;
    return b1 << 8 | b2;
}

uint32 BufferedInputStream::read_uint32() {
    uint32 b1 = read_uint8() & 0xff;
    uint32 b2 = read_uint8() & 0xff;
    uint32 b3 = read_uint8() & 0xff;
    uint32 b4 = read_uint8() & 0xff;
    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

uint64 BufferedInputStream::read_uint64() {
    uint64 int1 = read_uint32() & 0xffffffff;
    uint64 int2 = read_uint32() & 0xffffffff;
    return int1 << 32 | int2;
}

float BufferedInputStream::read_float() {
    float f;
    uint8 b[4];
    for (int i = 3; i>=0; i--) {
        b[i] = read_uint8();
    }
    memcpy(&f, &b, sizeof(f));
    return f;
}

double BufferedInputStream::read_double() {
    double f;
    uint8 b[8];
    for (int i = 7; i>=0; i--) {
        b[i] = read_uint8();
    }
    memcpy(&f, &b, sizeof(f));
    return f;
}

std::string gen_class_name(const char* fileName) {
    auto old = std::string(fileName);
    auto last_slash = old.find_last_of('/');
    auto prefix = old.substr(0, last_slash+1);
    auto suffix = old.substr(last_slash+1) + ".class";
    auto new_str = "/Users/chaomaer/Desktop/lib/" + prefix + suffix;
    std::cout << prefix << " " << suffix << std::endl;
    std::cout << new_str << std::endl;
    return new_str;
}

BufferedInputStream::BufferedInputStream(const char *fileName) {
    std::cout << "load class " << fileName << std::endl;
    _fp = fopen(fileName, "rb");
    if (_fp == nullptr) {
        std::string new_str = gen_class_name(fileName);
        _fp = fopen(new_str.c_str(), "rb");
    }
    fread(buffer, BUFFER_SIZE, 1, _fp);
    _index = 0;
}

BufferedInputStream::BufferedInputStream(std::string fileName) : BufferedInputStream(fileName.c_str()) {
}
