//
// Created by chaomaer on 2023/2/7.
//

#ifndef CPP_JVM2_CLASS_H
#define CPP_JVM2_CLASS_H
#include "common/type.h"
#include "string"
#include "common/heapVector.h"
#include "common/heapString.h"
#include "core/frame.h"
#include "parser/classFile.h"
#include "common/localArray.h"
#include "classLoader.h"
#include "rtConsts.h"

class Class;
class RTConst;
class RTConstantPool : public HeapVector<RTConst*>{
public:
    RTConstantPool(int size);
    Class* _class;
};

class ClassMember {
public:
    uint16 access_flag;
    HeapString name;
    HeapString descriptor;
    Class* _class{nullptr};
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
    HeapVector<HeapString>* argsType;
    HeapString retType;
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
    void inject_code_attribute(HeapString type);
};

class ClassLoader;

HeapObject* new_string_object(ClassLoader* class_loader, HeapString str);
HeapString to_string(HeapObject* object);

class Class {
public:
    HeapVector<Field*>* new_fields(ClassFile* class_file);
    HeapVector<Method*>* new_methods(ClassFile* class_file);
    RTConstantPool* new_rt_constant_pool(ClassFile* class_file);
    Field* lookup_field(HeapString name, HeapString descriptor);
    Method* lookup_method(HeapString name, HeapString descriptor);
    HeapObject* new_object();
    Method* find_main_method();
    Class* array_class();
    HeapString get_array_name();
    HeapObject* new_array(int size);
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
    HeapString name;
    HeapString superClass_name;
    HeapVector<HeapString>* interface_names;
    RTConstantPool* rt_constant_pool;
    HeapVector<Field*>* fields;
    HeapVector<Method*>* methods;
    ClassLoader* class_loader;
    Class* super_class;
    HeapVector<Class*>* interface_classes;
    uint32 instance_slot_count;
    uint32 static_slot_count;
    ObjectLocalVars* static_vars;
    HeapObject* jClass; // the instance of the java/lang/Class
};

#endif //CPP_JVM2_CLASS_H
