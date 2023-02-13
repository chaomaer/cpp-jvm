//
// Created by chaomaer on 2023/2/7.
//
#include <iostream>
#include "class.h"
#include "accessFlags.h"

std::vector<Field *> *Class::new_fields(ClassFile *class_file) {
    auto vect = new std::vector<Field*>;
    for (int i = 0; i<class_file->fields_count; i++) {
        auto info = class_file->fields->at(i);
        auto new_f = new Field;
        new_f->copy_member_info(info);
        new_f->_class = this;
        vect->push_back(new_f);
    }
    return vect;
}

std::vector<Method *> *Class::new_methods(ClassFile *class_file) {
    auto vect = new std::vector<Method*>;
    for (int i = 0; i<class_file->methods_count; i++) {
        auto info = class_file->methods->at(i);
        auto new_m = new Method;
        new_m->copy_member_info(info);
        new_m->copy_attributes(info);
        new_m->cal_arg_slot_number(new_m->descriptor);
        new_m->_class = this;
        vect->push_back(new_m);
    }
    return vect;
}

RTConstantPool *Class::new_rt_constant_pool(ClassFile *class_file) {
    auto cp = class_file->constant_pool;
    auto rt_cp = new RTConstantPool(cp->size());
    rt_cp->_class = this;
    // 从1开始
    for (int i = 1; i<cp->size(); i++) {
        auto _const = cp->at(i);
        auto type = _const->type;
        if (type == CONSTANT_Integer) {
            auto val = ((ConstantIntegerInfo*)(_const))->val;
            auto rt_val = new RTInt_Const;
            rt_val->val = val;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Long) {
            auto val = ((ConstantLongInfo*)(_const))->val;
            auto rt_val = new RTLong_Const;
            rt_val->val = val;
            rt_cp->at(i) = rt_val;
            i++;
        }else if (type == CONSTANT_Float) {
            auto val = ((ConstantFloatInfo*)(_const))->val;
            auto rt_val = new RTFloat_Const;
            rt_val->val = val;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Double) {
            auto val = ((ConstantDoubleInfo*)(_const))->val;
            auto rt_val = new RTDouble_Const;
            rt_val->val = val;
            rt_cp->at(i) = rt_val;
            i++;
        }else if (type == CONSTANT_String) {
            auto idx = ((ConstantStringInfo*)(_const))->string_index;
            auto val = cp->get_utf8(idx);
            auto rt_val = new RTString_Const;
            rt_val->val = val;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Fieldref) {
            auto info = (ConstantFieldRefInfo*)(_const);
            auto rt_val = new FieldRef(info, rt_cp);
            rt_val->rt_cp = rt_cp;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Methodref) {
            auto info = (ConstantMethodRefInfo*)(_const);
            auto rt_val = new MethodRef(info, rt_cp);
            rt_val->rt_cp = rt_cp;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Class) {
            auto info = (ConstantClassInfo*)(_const);
            auto rt_val = new ClassRef(info, rt_cp);
            rt_val->rt_cp = rt_cp;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Utf8 || type == CONSTANT_NameAndType) {

        }else {
            std::cout << type << std::endl;
            std::cout << "[errr:] convert constant_info to runtime-constant" << std::endl;
        }
    }
    return rt_cp;
}

Class::Class(ClassFile *class_file) {
    std::cout << "hello class" << std::endl;
    this->access_flags = class_file->access_flags;
    this->superClass_name = class_file->get_superClass_name();
    this->name = class_file->get_class_name();
    std::cout << superClass_name << "<-" << name << std::endl;
    this->interface_names = class_file->get_interface_names();

    this->rt_constant_pool = this->new_rt_constant_pool(class_file);
    this->fields = this->new_fields(class_file);
    this->methods = this->new_methods(class_file);
}

bool Class::is_public() {
    return this->access_flags & ACC_PUBLIC;
}

void Class::calc_instance_field_ids() {
    int idx = 0;
    if (super_class != nullptr) {
        idx = super_class->instance_slot_count;
    }
    for (int i = 0; i<fields->size(); i++) {
        auto f = fields->at(i);
        if (!f->is_static()){
            f->slot_id = idx++;
            if (f->is_long_or_double()) {
                idx++;
            }
        }
    }
    this->instance_slot_count = idx;
}

void Class::calc_static_field_ids() {
    int idx = 0;
    for (int i = 0; i<fields->size(); i++) {
        auto f = fields->at(i);
        if (f->is_static()){
            f->slot_id = idx++;
            if (f->is_long_or_double()) {
                idx++;
            }
        }
    }
    this->static_slot_count = idx;
}

void Class::init_one_static(Field* f) {
    auto slot_id = f->slot_id;
    auto des = f->descriptor;
    auto cp = f->_class->rt_constant_pool;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        static_vars->set_int(slot_id, 0);
        if (f->is_final()) {
            auto val = (RTInt_Const*)cp->at(f->const_idx);
            static_vars->set_int(slot_id, val->val);
        }
    } else if (des == "J") {
        static_vars->set_long(slot_id, 0);
        if (f->is_final()) {
            auto val = (RTLong_Const*)cp->at(f->const_idx);
            static_vars->set_long(slot_id, val->val);
        }
    } else if (des == "F") {
        static_vars->set_float(slot_id, 0);
        if (f->is_final()) {
            auto val = (RTFloat_Const*)cp->at(f->const_idx);
            static_vars->set_float(slot_id, val->val);
        }
    } else if (des == "D") {
        static_vars->set_double(slot_id, 0);
        if (f->is_final()) {
            auto val = (RTDouble_Const*)cp->at(f->const_idx);
            static_vars->set_double(slot_id, val->val);
        }
    } else {
        static_vars->set_ref(slot_id, nullptr);
        std::cout << "not supported " <<des << std::endl;
    }
}

void Class::init_static_fields() {
    static_vars = new LocalVars(static_slot_count);
    for (int i = 0; i<fields->size(); i++) {
        auto f = fields->at(i);
        if (f->is_static()) {
            init_one_static(f);
        }
    }
}

Field *Class::lookup_field(std::string name, std::string descriptor) {
    for (auto f : *fields) {
        if (f->name == name && f->descriptor == descriptor) {
            return f;
        }
    }
    if (super_class != nullptr) {
        return super_class->lookup_field(name, descriptor);
    }
    return nullptr;
}

Object *Class::new_object() {
    auto object = new Object;
    object->_class = this;
    // todo: 需要初始化field
    object->fields = new LocalVars(instance_slot_count);
    return object;
}

bool Class::is_sub_of(Class *tClass) {
    if (tClass == this) return true;
    auto pClass = super_class;
    for (; pClass != nullptr; pClass = pClass->super_class) {
        if (pClass == tClass) return true;
    }
    return false;
}

bool Class::is_super_of(Class* tClass) {
    return tClass->is_sub_of(this);
}

Method *Class::find_main_method() {
    for (auto m: *methods) {
        if (m->name == "main" && m->descriptor == "([Ljava/lang/String;)V") {
            return m;
        }
    }
    return nullptr;
}

Method* lookup_method_in_interfaces(std::vector<Class*>* _interfaces, std::string name, std::string descriptor) {
    for (auto inter : *_interfaces) {
        for (auto m: *inter->methods) {
            if (m->name == name && m->descriptor == descriptor) {
                return m;
            }
        }
        auto ret = lookup_method_in_interfaces(inter->interface_classes, name, descriptor);
        if (ret != nullptr) return ret;
    }
    return nullptr;
}

Method *Class::lookup_method(std::string name, std::string descriptor) {
    Method *ret_m = nullptr;
    for (auto m: *methods) {
        if (m->name == name && m->descriptor == descriptor) {
            return m;
        }
    }
    if (super_class != nullptr && !is_interface()) {
        ret_m = super_class->lookup_method(name, descriptor);
    }
    return lookup_method_in_interfaces(interface_classes, name, descriptor);
}

bool Class::is_interface() {
    return access_flags & ACC_INTERFACE;
}

bool Class::is_super() {
    return access_flags & ACC_SUPER;
}

void ClassMember::copy_member_info(MemberInfo *member_info) {
    access_flag = member_info->access_flags;
    name = member_info->cp->get_utf8(member_info->name_index);
    descriptor = member_info->cp->get_utf8(member_info->descriptor_index);
}

void Method::copy_attributes(MethodInfo *method_info) {
    auto attributes = (CodeAttribute*)(method_info->get_first_code_attributes());
    if (attributes == nullptr) {
        return;
    }
    max_stack = attributes->max_stack;
    max_locals = attributes->max_locals;
    code = attributes->byte_code;
}

static char primitive_type[]{'S', 'I', 'L', };

int Method::cal_arg_slot_number(std::string descriptor) {
    auto right_brace = descriptor.find_last_of(')');
    descriptor = descriptor.substr(1, right_brace-1);
    int idx = 0;
    int slot_number = 0;
    char x;
    while (idx < descriptor.size()) {
        x = descriptor[idx];
        //array
        if (x == '[') {

        }else if (x == 'L') {
            while(x != ';') {
                idx++;
                x = descriptor[idx];
            }
            slot_number++;
        }else if (x == 'J' || x == 'D') {
            slot_number+=2;
        }else if (x == 'Z' || x == 'B' || x == 'C' || x == 'S' || x == 'I' || x == 'F' ){
            slot_number++;
        }else {
            assert(false && "error in this place");
        }
        idx++;
    }
    if (!is_static()) {
        slot_number++;
    }
    arg_slot_number = slot_number;
    return slot_number;
}

bool ClassMember::is_static() {
    return access_flag & ACC_STATIC;
}

bool Field::is_long_or_double() {
    return descriptor == "J" || descriptor == "D";
}

bool ClassMember::is_final() {
    return access_flag & ACC_FINAL;
}

RTConstantPool::RTConstantPool(int size) : std::vector<RTConst*>(size){
}
