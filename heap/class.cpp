//
// Created by chaomaer on 2023/2/7.
//
#include "common/debug.h"
#include "class.h"
#include "accessFlags.h"
#include "common/debug.h"
#include "core/interpreter.h"
#include "common/heapVector.h"
#include <cassert>
#include <cstring>

HeapVector<Field *> *Class::new_fields(ClassFile *class_file) {
    auto vect = new HeapVector<Field*>;
    for (int i = 0; i<class_file->fields_count; i++) {
        auto info = class_file->fields->at(i);
        auto new_f = new Field;
        new_f->copy_member_info(info);
        new_f->copy_attributes(info);
        new_f->_class = this;
        vect->push_back(new_f);
    }
    return vect;
}

HeapVector<Method *> *Class::new_methods(ClassFile *class_file) {
    auto vect = new HeapVector<Method*>;
    for (int i = 0; i<class_file->methods_count; i++) {
        auto info = class_file->methods->at(i);
        auto new_m = new Method;
        new_m->copy_member_info(info);
        new_m->copy_attributes(info);
        new_m->cal_arg_slot_number();
        new_m->_class = this;
        if (new_m->is_native()) {
            auto m_type = new_m->parse_descriptor();
            new_m->inject_code_attribute(m_type->retType);
            delete m_type;
        }
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
        if (_const == nullptr) {
            continue;
        }
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
            rt_val->val = str_to_heapStr(val);
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
        }else if (type == CONSTANT_InterfaceMethodref) {
            auto info = (ConstantInterfaceMethodRefInfo*)(_const);
            auto rt_val = new InterfaceMethodRef(info, rt_cp);
            rt_val->rt_cp = rt_cp;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Class) {
            auto info = (ConstantClassInfo *) (_const);
            auto rt_val = new ClassRef(info, rt_cp);
            rt_val->rt_cp = rt_cp;
            rt_cp->at(i) = rt_val;
        }else if (type == CONSTANT_Utf8 || type == CONSTANT_NameAndType) {

        }else {
            DEBUG_MSG(type);
            DEBUG_MSG("[errr:] convert constant_info to runtime-constant");
        }
    }
    return rt_cp;
}

Class::Class(ClassFile *class_file) {
    // move to heap memory
    this->access_flags = class_file->access_flags;
    this->superClass_name = str_to_heapStr(class_file->get_superClass_name());
    this->name = str_to_heapStr(class_file->get_class_name());
    DEBUG_MSG(superClass_name << "<-" << name);
    this->interface_names = new HeapVector<HeapString>;
    auto inter_names = class_file->get_interface_names();
    for (auto& s: *inter_names) {
        this->interface_names->push_back(str_to_heapStr(s));
    }
    delete inter_names;
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
        if (f->is_final() && f->const_idx) {
            auto val = (RTInt_Const*)cp->at(f->const_idx);
            static_vars->set_int(slot_id, val->val);
        }
    } else if (des == "J") {
        static_vars->set_long(slot_id, 0);
        if (f->is_final() && f->const_idx) {
            auto val = (RTLong_Const*)cp->at(f->const_idx);
            static_vars->set_long(slot_id, val->val);
        }
    } else if (des == "F") {
        static_vars->set_float(slot_id, 0);
        if (f->is_final() && f->const_idx) {
            auto val = (RTFloat_Const*)cp->at(f->const_idx);
            static_vars->set_float(slot_id, val->val);
        }
    } else if (des == "D") {
        static_vars->set_double(slot_id, 0);
        if (f->is_final() && f->const_idx) {
            auto val = (RTDouble_Const*)cp->at(f->const_idx);
            static_vars->set_double(slot_id, val->val);
        }
    } else {
        static_vars->set_ref(slot_id, nullptr);
        DEBUG_MSG("[INIT STATIC]: not supported " <<des);
    }
}

void Class::init_static_fields() {
    static_vars = new ObjectLocalVars(static_slot_count);
    for (int i = 0; i<fields->size(); i++) {
        auto f = fields->at(i);
        if (f->is_static()) {
            init_one_static(f);
        }
    }
}

Field *Class::lookup_field(HeapString name, HeapString descriptor) {
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

HeapObject *Class::new_object() {
    auto object = new HeapObject;
    object->_class = this;
    // todo: 需要初始化field
    object->fields = new ObjectLocalVars(instance_slot_count);
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
    return tClass->is_sub_of(this) && tClass != this;
}

Method *Class::find_main_method() {
    for (auto m: *methods) {
        if (m->name == "main" && m->descriptor == "([Ljava/lang/String;)V") {
            return m;
        }
    }
    return nullptr;
}

Method* lookup_method_in_interfaces(HeapVector<Class*>* _interfaces, HeapString name, HeapString descriptor) {
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

Method *Class::lookup_method(HeapString name, HeapString descriptor) {
    Method *ret_m = nullptr;
    if (methods != nullptr) {
        for (auto m: *methods) {
            if (m->name == name && m->descriptor == descriptor) {
                return m;
            }
        }
    }
    if (super_class != nullptr && !is_interface()) {
        ret_m = super_class->lookup_method(name, descriptor);
    }
    return ret_m != nullptr? ret_m : lookup_method_in_interfaces(interface_classes, name, descriptor);
}

bool Class::is_interface() {
    return access_flags & ACC_INTERFACE;
}

bool Class::is_super() {
    return access_flags & ACC_SUPER;
}

Class::Class() {

}

HeapObject *Class::new_array(int size) {
    if (name == "[Z" || name == "[B" || name == "[I" || name == "[S" || name == "[C") {
        return new ArrayObject<int>(this, size);
    }else if (name == "[J") {
        return new ArrayObject<long>(this, size);
    }else if (name == "[F") {
        return new ArrayObject<float>(this, size);
    }else if (name == "[D") {
        return new ArrayObject<double>(this, size);
    }else if (name[0] == '[') {
        return new ArrayObject<HeapObject*>(this, size);
    }
    return nullptr;
}

void Class::execute_class_init() {
//    auto m = lookup_method("<clinit>", "()V");
//    if (m == nullptr) {
//        return;
//    }
//    auto manager = new FrameManager();
//    auto frame = manager->new_frame(m);
//    manager->push_frame(frame);
//    auto vm = new Interpreter();
//    vm->loop(manager);
}

Class *Class::array_class() {
    auto array_name = get_array_name();
    return class_loader->load_class(heapStr_to_str(array_name));
}

HeapString Class::get_array_name() {
    auto str_name = heapStr_to_str(name);
    //array
    if (name[0] == '[') {
        return str_to_heapStr("[" + str_name);
    }
    //primitive
    if (primitive_types.count(str_name)) {
        return str_to_heapStr("[" + primitive_types[str_name]);
    }
    //object
    return str_to_heapStr("[L" + str_name + ";");
}

void *Class::operator new(std::size_t n) {
    return MemBuffer::allocate(n);
}

void ClassMember::copy_member_info(MemberInfo *member_info) {
    access_flag = member_info->access_flags;
    name = str_to_heapStr(member_info->cp->get_utf8(member_info->name_index));
    descriptor = str_to_heapStr(member_info->cp->get_utf8(member_info->descriptor_index));
}

void Method::copy_attributes(MethodInfo *method_info) {
    auto attributes = (CodeAttribute*)(method_info->get_first_code_attributes());
    if (attributes == nullptr) {
        return;
    }
    max_stack = attributes->max_stack;
    max_locals = attributes->max_locals;
    // copy to heap;
    len = attributes->len;
    code = static_cast<uint8 *>(MemBuffer::allocate(len));
    memcpy(code, attributes->byte_code, len);
}

MethodType* Method::parse_descriptor() {
    assert(descriptor != "");
    auto* methodType = new MethodType;
    auto right_brace = descriptor.find_last_of(')');
    auto ret_type = descriptor.substr(right_brace+1, descriptor.size()-right_brace-1);
    methodType->retType = *(HeapString*)&ret_type;
    auto temp_descriptor = descriptor.substr(1, right_brace-1);
    int idx = 0;
    char x;
    std::string cur = "";
    while (idx < temp_descriptor.size()) {
        x = temp_descriptor[idx];
        //array
        if (x == '[') {
            cur += x;
        }else if (x == 'L') {
            while(x != ';') {
                cur += x;
                idx++;
                x = temp_descriptor[idx];
            }
            methodType->argsType->push_back(str_to_heapStr(cur));
            cur = "";
        }else if (x == 'J' || x == 'D') {
            cur += x;
            methodType->argsType->push_back(str_to_heapStr(cur));
            cur = "";
        }else if (x == 'Z' || x == 'B' || x == 'C' || x == 'S' || x == 'I' || x == 'F' ){
            cur += x;
            methodType->argsType->push_back(str_to_heapStr(cur));
            cur = "";
        }else {
            assert(false && "error in this place");
        }
        idx++;
    }
    return methodType;
}

int Method::cal_arg_slot_number() {
    auto method_type = parse_descriptor();
    int slot_number = 0;
    for (HeapString& s: *method_type->argsType) {
        auto x = s[0];
        if (x == 'J' || x == 'D') {
            slot_number+=2;
        }else {
            slot_number++;
        }
    }
    if (!is_static()) {
        slot_number++;
    }
    arg_slot_number = slot_number;
    delete method_type;
    return slot_number;
}

void Method::inject_code_attribute(HeapString a_type) {
    max_locals = arg_slot_number;
    max_stack = 4;
    char type = a_type[0];
    code = static_cast<uint8 *>(MemBuffer::allocate(2));
    code[0] = 0xfe;
    if (type == 'V') {
        code[1] = 0xb1; // return
    }else if (type == 'D') {
        code[1] = 0xaf; // dreturn
    }else if (type == 'L' || type == '[') {
        code[1] = 0xb0; // areturn
    }else if (type == 'F') {
        code[1] = 0xae; // freturn
    }else if (type == 'J') {
        code[1] = 0xad; // lreturn
    }else {
        //DEBUG_MSG("native return type: " << type);
        code[1] = 0xac; //ireturn
    }
}

bool ClassMember::is_static() {
    return access_flag & ACC_STATIC;
}

bool Field::is_long_or_double() {
    return descriptor == "J" || descriptor == "D";
}

void Field::copy_attributes(FieldInfo *field_info) {
    if (is_final()) {
        auto att = (ConstantValueAttribute*)(field_info->get_first_constant_attribute());
        if (att != nullptr) {
            const_idx = att->constant_value_index;
        }
    }
}

bool ClassMember::is_final() {
    return access_flag & ACC_FINAL;
}

bool ClassMember::is_native() {
    return access_flag & ACC_NATIVE;
}

void *ClassMember::operator new(std::size_t n) {
    return MemBuffer::allocate(n);
}

RTConstantPool::RTConstantPool(int size) : HeapVector<RTConst*>(size){
}

void *RTConstantPool::operator new(std::size_t n) {
    return MemBuffer::allocate(n);
}

HeapString to_string(HeapObject* object) {
    auto idx = object->_class->lookup_field("value", "[C")->slot_id;
    auto str_array = (ArrayObject<int>*)object->fields->get_ref(idx);
    std::string s;
    for (int i = 0; i<str_array->size(); i++) {
        s.push_back((char )str_array->arr->at(i));
    }
    return str_to_heapStr(s);
}

HeapObject* new_string_object(ClassLoader* class_loader, HeapString str) {
    auto _class = class_loader->load_class("java/lang/String");
    auto object = _class->new_object();
    auto idx = object->_class->lookup_field("value", "[C")->slot_id;
    auto str_arr = new ArrayObject<int>(_class, str.size());
    for (int i = 0; i<str.size(); i++) {
        str_arr->arr->at(i) = (int )str[i];
    }
    object->fields->set_ref(idx, str_arr);
    return object;
}

MethodType::MethodType() {
    argsType = new HeapVector<HeapString>;
}
