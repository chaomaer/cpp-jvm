//
// Created by chaomaer on 2023/2/7.
//

#ifndef CPP_JVM2_RTCONSTS_H
#define CPP_JVM2_RTCONSTS_H
#include "parser/constantInfo.h"
#include "class.h"

class RTConst {
public:
    RTConst(uint16 type);
    uint16 type;
};

class RTConstantPool;
class Field;
class Method;
class SymRef : public RTConst {
public:
    RTConstantPool* rt_cp;
    std::string class_name;
    Class* _class;
    SymRef(int type);
};

class ClassRef : public SymRef {
public:
    ClassRef(ConstantClassInfo* info, RTConstantPool* cp);
    ClassRef(ConstantClassInfo* info, RTConstantPool* cp, int type);
    Class* resolve_class_ref();
};

class MemberRef : public ClassRef {
public:
    MemberRef(ConstantMemberRefInfo* info, RTConstantPool* cp, int type);
    std::string name;
    std::string descriptor;
    void copy_member_info(ConstantMemberRefInfo* info);
};

class FieldRef : public MemberRef {
public:
    FieldRef(ConstantFieldRefInfo* info, RTConstantPool* cp);
    Field* field;
public:
    Field* resolve_field_ref();
};

class MethodRef : public MemberRef {
public:
    MethodRef(ConstantMethodRefInfo* info, RTConstantPool* cp);
    MethodRef(ConstantMethodRefInfo* info, RTConstantPool* cp, int type);
    Method* method;
};

class InterfaceMethodRef : public MethodRef {
public:
    InterfaceMethodRef(ConstantInterfaceMethodRefInfo* info, RTConstantPool* cp);
};

class RTInt_Const : public RTConst {
public:
    int val;
    RTInt_Const();
};

class RTLong_Const : public RTConst {
public:
    long long val;
    RTLong_Const();
};

class RTFloat_Const : public RTConst {
public:
    float val;
    RTFloat_Const();
};

class RTDouble_Const : public RTConst {
public:
    double val;
    RTDouble_Const();
};

class RTString_Const : public RTConst {
public:
    std::string val;
    RTString_Const();
};

#endif //CPP_JVM2_RTCONSTS_H
