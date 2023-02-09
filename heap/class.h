//
// Created by chaomaer on 2023/2/7.
//

#ifndef CPP_JVM2_CLASS_H
#define CPP_JVM2_CLASS_H
#include "common/type.h"
#include "string"
#include "vector"
#include "core/frame.h"
#include "parser/classFile.h"
#include "classLoader.h"
#include "rtConsts.h"

class Class;
class RTConst;
class RTConstantPool : public std::vector<RTConst*>{
public:
    RTConstantPool(int size);
    Class* _class;
};

class ClassMember {
public:
    uint16 access_flag;
    std::string name;
    std::string descriptor;
    Class* _class;
    void copy_member_info(MemberInfo* member_info);
};

class Field : public ClassMember {
public:
    int slot_id;
    int const_idx;
    bool is_static();
    bool is_final();
    bool is_long_or_double();
};

class Method : public ClassMember {
public:
    uint16 max_stack;
    uint16 max_locals;
    uint8* code;
public:
    void copy_attributes(MethodInfo* method_info);
};
class ClassLoader;
class LocalVars;
class Object;
class Class {
public:
    std::vector<Field*>* new_fields(ClassFile* class_file);
    std::vector<Method*>* new_methods(ClassFile* class_file);
    RTConstantPool* new_rt_constant_pool(ClassFile* class_file);
    Field* lookup_field(std::string name, std::string descriptor);
    Object* new_object();
    Method* find_main_method();
    bool is_sub_of(Class* tClass);
    bool is_public();
    void calc_instance_field_ids();
    void calc_static_field_ids();
    void init_static_fields();
    void init_one_static(Field* f);
    Class(ClassFile* class_file);
    uint16 access_flags;
    std::string name;
    std::string superClass_name;
    std::vector<std::string>* interface_names;
    RTConstantPool* rt_constant_pool;
    std::vector<Field*>* fields;
    std::vector<Method*>* methods;
    ClassLoader* class_loader;
    Class* super_class;
    std::vector<Class*>* interface_classes;
    uint32 instance_slot_count;
    uint32 static_slot_count;
    LocalVars* static_vars;
};

#endif //CPP_JVM2_CLASS_H
