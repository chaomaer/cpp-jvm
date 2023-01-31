//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_CLASSFILE_H
#define CPP_JVM2_CLASSFILE_H
#include "common/type.h"
#include "constantInfo.h"
#include "attributeInfo.h"

class MemberInfo {
public:
    ConstantPool* cp;
    uint16 access_flags;
    uint16 name_index;
    uint16 descriptor_index;
    std::vector<AttributeInfo*>* attributes;
};

class FieldInfo : public MemberInfo {

};

class MethodInfo : public MemberInfo {

};

class ClassFile {
public:
    uint32 magic;
    uint16 minor_version;
    uint16 major_version;
    uint16 constant_pool_count;
    ConstantPool* constant_pool;
    uint16 access_flags;
    uint16 this_class;
    uint16 super_class;
    uint16 interfaces_count;
    uint16* interfaces;
    uint16 fields_count;
    std::vector<FieldInfo*>* fields;
    uint16 methods_count;
    std::vector<MethodInfo*>* methods;
    uint16 attributes_count;
    std::vector<AttributeInfo*>* attributes;
};

#endif //CPP_JVM2_CLASSFILE_H
