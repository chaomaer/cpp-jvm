//
// Created by chaomaer on 2023/2/16.
//

#ifndef CPP_JVM2_NATIVE_H
#define CPP_JVM2_NATIVE_H
#include "frame.h"
#include "unordered_map"

typedef void (*nativeFunc)(Frame*);

class NativeRegistry {
private:
    static NativeRegistry* registry;
    std::unordered_map<std::string, nativeFunc>* native_methods;
    NativeRegistry();
public:
    ~NativeRegistry();
    static int size();
    static NativeRegistry* get_registry();
    void _register(std::string class_name, std::string name, std::string des, nativeFunc func);
    nativeFunc find_native_method(std::string class_name, std::string name, std::string des);
};

#endif //CPP_JVM2_NATIVE_H
