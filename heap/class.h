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
    bool is_static();
    bool is_final();
    bool is_native();
    void copy_member_info(MemberInfo* member_info);
};

class Field : public ClassMember {
public:
    int slot_id;
    int const_idx;
    bool is_long_or_double();
    void copy_attributes(FieldInfo* field_info);
};

class MethodType {
public:
    MethodType();
    std::vector<std::string>* argsType;
    std::string retType;
};

class Method : public ClassMember {
public:
    int arg_slot_number;
    uint16 max_stack;
    uint16 max_locals;
    uint16 len;
    uint8* code;
public:
    void copy_attributes(MethodInfo* method_info);
    int cal_arg_slot_number();
    MethodType* parse_descriptor();
    void inject_code_attribute(std::string type);
};

class ClassLoader;
class LocalVars;
class Object;

Object* new_string_object(ClassLoader* class_loader, std::string str);
std::string to_string(Object* object);

class Class {
public:
    std::vector<Field*>* new_fields(ClassFile* class_file);
    std::vector<Method*>* new_methods(ClassFile* class_file);
    RTConstantPool* new_rt_constant_pool(ClassFile* class_file);
    Field* lookup_field(std::string name, std::string descriptor);
    Method* lookup_method(std::string name, std::string descriptor);
    Object* new_object();
    Method* find_main_method();
    Class* array_class();
    std::string get_array_name();
    Object* new_array(int size);
    void execute_class_init();
    bool is_sub_of(Class* tClass);
    bool is_super_of(Class* tClass);
    bool is_public();
    bool is_super();
    bool is_interface();
    void calc_instance_field_ids();
    void calc_static_field_ids();
    void init_static_fields();
    void init_one_static(Field* f);
    Class(ClassFile* class_file);
    Class();
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
    Object* jClass; // the instance of the java/lang/Class
};

#endif //CPP_JVM2_CLASS_H
