//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_CONSTANTINFO_H
#define CPP_JVM2_CONSTANTINFO_H

#include "common/type.h"
#include "string"

#define CONSTANT_Class 7
#define CONSTANT_Fieldref  9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String  8
#define CONSTANT_Integer  3
#define CONSTANT_Float  4
#define CONSTANT_Long  5
#define CONSTANT_Double  6
#define CONSTANT_NameAndType  12
#define CONSTANT_Utf8  1
#define CONSTANT_MethodHandle  15
#define CONSTANT_MethodType  16
#define CONSTANT_InvokeDynamic  18
#include "vector"

class ConstantInfo {
};

//typedef std::vector<ConstantInfo*> ConstantPool;

class ConstantUTF8Info;

class ConstantPool : public std::vector<ConstantInfo*> {
public:
    ConstantPool(uint16 cnt);
    std::string get_utf8(uint16 index);
};

class ConstantIntegerInfo : public ConstantInfo {
public:
    int val;
};

class ConstantLongInfo : public ConstantInfo {
public:
    long long val;
};

class ConstantFloatInfo : public ConstantInfo {
public:
    float val;
};

class ConstantDoubleInfo : public ConstantInfo {
public:
    double val;
};

class ConstantUTF8Info : public ConstantInfo {
public:
    std::string val;
};

class ConstantStringInfo : public ConstantInfo {
public:
    ConstantPool* cp;
    uint16 string_index;
};

class ConstantClassInfo : public ConstantInfo {
public:
    ConstantPool* cp;
    uint16 class_index;
};

class ConstantNameAndTypeInfo : public ConstantInfo {
public:
    ConstantPool* cp;
    uint16 name_index;
    uint16 descriptor_index;
};

class ConstantMemberRefInfo : public ConstantInfo {
public:
    ConstantPool* cp;
    uint16 class_index;
    uint16 name_and_type_index;
};

class ConstantFieldRefInfo : public ConstantMemberRefInfo {

};

class ConstantMethodRefInfo : public ConstantMemberRefInfo {

};

class ConstantInterfaceMethodRefInfo : public ConstantMemberRefInfo {

};
#endif //CPP_JVM2_CONSTANTINFO_H
