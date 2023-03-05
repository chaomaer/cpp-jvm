//
// Created by chaomaer on 2023/2/7.
//

#include "classFile.h"

std::string ClassFile::get_class_name() {
    return constant_pool->get_class_name(this_class);
}

std::string ClassFile::get_superClass_name() {
    return constant_pool->get_class_name(super_class);
}

std::vector<std::string> *ClassFile::get_interface_names() {
    auto vect = new std::vector<std::string>;
    for (int i = 0; i<interfaces_count; i++) {
        vect->push_back(constant_pool->get_class_name(interfaces[i]));
    }
    return vect;
}

ClassFile::~ClassFile() {
    //delete info in constant pool and constant pool
    for (auto& info : *constant_pool) {
        delete info;
    }
    delete constant_pool;
    //delete field
    for (auto& f: *fields) {
        delete f;
    }
    delete fields;
    //delete field
    for (auto& m: *methods) {
        delete m;
    }
    delete methods;
    for (auto& att: *attributes) {
        delete att;
    }
    delete attributes;
    delete[] interfaces;
}

MemberInfo::~MemberInfo() {
    for (auto& info : *attributes) {
        delete info;
    }
    delete attributes;
}
