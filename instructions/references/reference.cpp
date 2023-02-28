//
// Created by chaomaer on 2023/2/9.
//

#include "reference.h"
#include "core/universe.h"
#include <iostream>

void static_put(OperationStack *stack, LocalVars *vars, Field *f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        vars->set_int(id, stack->pop_int());
    } else if (des == "J") {
        vars->set_long(id, stack->pop_long());
    } else if (des == "F") {
        vars->set_float(id, stack->pop_float());
    } else if (des == "D") {
        vars->set_double(id, stack->pop_double());
    } else if (des[0] == 'L' || des[0] == '[') {
        vars->set_ref(id, stack->pop_ref());
    } else {
        std::cout << "[STATIC_PUT:] unsupported descriptor " << des << std::endl;
    }
}

void static_get(OperationStack *stack, LocalVars *vars, Field *f) {
    auto id = f->slot_id;
    auto des = f->descriptor;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        stack->push_int(vars->get_int(id));
    } else if (des == "J") {
        stack->push_long(vars->get_long(id));
    } else if (des == "F") {
        stack->push_float(vars->get_float(id));
    } else if (des == "D") {
        stack->push_double(vars->get_double(id));
    } else if (des[0] == 'L' || des[0] == '[') {
        stack->push_ref(vars->get_ref(id));
    } else {
        stack->push_ref(vars->get_ref(id));
        std::cout << "[STATIC_PUT:] unsupported descriptor " << des << std::endl;
    }
}

void field_put(OperationStack *stack, Field *f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        auto val = stack->pop_int();
        auto ref = stack->pop_ref();
        ref->fields->set_int(id, val);
    } else if (des == "J") {
        auto val = stack->pop_long();
        auto ref = stack->pop_ref();
        ref->fields->set_long(id, val);
    } else if (des == "F") {
        auto val = stack->pop_float();
        auto ref = stack->pop_ref();
        ref->fields->set_float(id, val);
    } else if (des == "D") {
        auto val = stack->pop_double();
        auto ref = stack->pop_ref();
        ref->fields->set_double(id, val);
    } else if (des[0] == 'L') {
        auto val = stack->pop_ref();
        auto ref = stack->pop_ref();
        ref->fields->set_ref(id, val);
    } else if (des[0] == '['){
        auto val = stack->pop_ref();
        auto ref = stack->pop_ref();
        ref->fields->set_ref(id, val);
    } else {
        std::cout << "[PUT_FIELD:] unsupported descriptor" << std::endl;
    }
}

void field_get(OperationStack *stack, Field *f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    auto vars = stack->pop_ref()->fields;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        stack->push_int(vars->get_int(id));
    } else if (des == "J") {
        stack->push_long(vars->get_long(id));
    } else if (des == "F") {
        stack->push_float(vars->get_float(id));
    } else if (des == "D") {
        stack->push_double(vars->get_double(id));
    } else if (des[0] == 'L' || des[0] == '[') {
        stack->push_ref(vars->get_ref(id));
    } else {
        std::cout << "[GET_FIELD:] unsupported descriptor " << des << std::endl;
    }
}

void NEW::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef *) cp->at(index);
    auto _class = class_ref->resolve_class_ref();
    auto object = _class->new_object();
    frame->operation_stack->push_ref(object);
}

void PUT_STATIC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef *) cp->at(index);
    auto field = field_ref->resolve_field_ref();
    static_put(frame->operation_stack, field->_class->static_vars, field);
}

void GET_STATIC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef *) cp->at(index);
    auto field = field_ref->resolve_field_ref();
    static_get(frame->operation_stack, field->_class->static_vars, field);
}

void PUT_FIELD::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef *) cp->at(index);
    auto field = field_ref->resolve_field_ref();
    field_put(frame->operation_stack, field);
}

void GET_FIELD::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef *) cp->at(index);
    auto field = field_ref->resolve_field_ref();
    field_get(frame->operation_stack, field);
}

void IS_INSTANCE_OF::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef *) cp->at(index);
    auto ref_class = class_ref->resolve_class_ref();
    auto stack = frame->operation_stack;
    auto ref = stack->pop_ref();
    // todo 处理接口
    if (ref->_class->is_sub_of(ref_class)) {
        stack->push_int(1);
    } else {
        stack->push_int(0);
    }
}

void CHECK_CAST::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef *) cp->at(index);
    auto ref_class = class_ref->resolve_class_ref();
    auto stack = frame->operation_stack;
    auto ref = stack->pop_ref();
    stack->push_ref(ref);
    // todo 处理接口
    if (ref->_class->is_sub_of(ref_class)) {

    } else {
        std::cout << "can't cast " << std::endl;
    }
}

void INVOKE_SPECIAL::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto cur_class = frame->method->_class;
    auto m_ref = (MethodRef *) cp->at(index);
    auto to_be_invoke = m_ref->resolve_method_ref();
    //todo 权限控制
    if (to_be_invoke->_class->is_super_of(cur_class) &&
        cur_class->is_super() && to_be_invoke->name != "<init>") {
        to_be_invoke = cur_class->super_class->lookup_method(m_ref->name, m_ref->descriptor);
    }
    invoke_method(frame, to_be_invoke);
}

void _println(OperationStack* stack, std::string des) {
    std::lock_guard<std::mutex> guard(m);
    if (des == "(Z)V") {
        std::cout << (stack->pop_int() == 1) << std::endl;
    } else if (des == "(C)V") {
        printf("%c\n", stack->pop_int());
    }else if (des == "(B)V" || des == "(S)V" || des == "(I)V") {
        std::cout << stack->pop_int() << std::endl;
    } else if (des == "(F)V") {
        std::cout << stack->pop_float() << std::endl;
    } else if (des == "(D)V") {
        std::cout << stack->pop_double() << std::endl;
    } else if (des == "(J)V") {
        std::cout << stack->pop_long() << std::endl;
    } else if (des == "(Ljava/lang/String;)V"){
        auto object = stack->pop_ref();
        auto s = to_string(object);
        std::cout << s << std::endl;
    } else {
        std::cout << "unsupported type " << des << std::endl;
    }
    stack->pop_ref();
}

void INVOKE_VIRTUAL::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto method_ref = (MethodRef *) cp->at(index);
    auto stack = frame->operation_stack;
    if (method_ref->name == "println") {
        //std::cout << "************" << std::endl;
        _println(stack, method_ref->descriptor);
        //std::cout << "************" << std::endl;
        return;
    }
    auto m = method_ref->resolve_method_ref();
    auto object_ref = stack->top_ref(m->arg_slot_number);
    auto to_be_invoke = object_ref->_class->lookup_method(
            method_ref->name, method_ref->descriptor);
    invoke_method(frame, to_be_invoke);
}

void INVOKE_INTERFACE::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto method_ref = (InterfaceMethodRef *) cp->at(index);
    auto stack = frame->operation_stack;
    if (method_ref->name == "println") {
        std::cout << "************" << std::endl;
        _println(stack, method_ref->descriptor);
        std::cout << "************" << std::endl;
        return;
    }
    auto m = method_ref->resolve_method_ref();
    auto object_ref = stack->top_ref(m->arg_slot_number);
    auto to_be_invoke = object_ref->_class->lookup_method(
            method_ref->name, method_ref->descriptor);
    invoke_method(frame, to_be_invoke);
}

void INVOKE_INTERFACE::fetch_operands(BytecodeReader *reader) {
    index = reader->read_uint16();
    reader->read_uint8();
    reader->read_uint8();
}

void INVOKE_STATIC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto m_ref = (MethodRef *) cp->at(index);
    auto to_be_invoke = m_ref->resolve_method_ref();
    //todo 权限控制
    invoke_method(frame, to_be_invoke);
}

void INVOKE_NATIVE::execute(Frame *frame) {
    auto method = frame->method;
    assert(method->is_native());
    auto native_m = Universe::registry->find_native_method(
                method->_class->name, method->name, method->descriptor);
    native_m(frame);
    std::cout << method->_class->name << " " << method->name << " " << method->descriptor << std::endl;
}

void NEW_ARRAY::execute(Frame *frame) {
    auto a_type = this->index;
    auto stack = frame->operation_stack;
    int cnt = stack->pop_int();
    auto class_loader = frame->method->_class->class_loader;
    auto arr_class = get_primitive_array_class(class_loader, a_type);
    auto object = arr_class->new_array(cnt);
    std::cout << ((ArrayObject0*)(object))->type << std::endl;
    stack->push_ref(object);
}

void A_NEW_ARRAY::execute(Frame *frame) {
    auto rt_cp = frame->method->_class->rt_constant_pool;
    auto stack = frame->operation_stack;
    auto cnt = stack->pop_int();
    auto class_ref = (ClassRef*)rt_cp->at(index);
    auto _class = class_ref->resolve_class_ref();
    auto arr_class = _class->array_class();
    auto array_object = arr_class->new_array(cnt);
    stack->push_ref(array_object);
}

Class* get_primitive_array_class(ClassLoader *pLoader, unsigned int type) {
    switch (type) {
        case AT_BOOLEAN:
            return pLoader->load_class("[Z");
        case AT_CHAR:
            return pLoader->load_class("[C");
        case AT_BYTE:
            return pLoader->load_class("[B");
        case AT_INT:
            return pLoader->load_class("[I");
        case AT_SHORT:
            return pLoader->load_class("[S");
        case AT_LONG:
            return pLoader->load_class("[J");
        case AT_FLOAT:
            return pLoader->load_class("[F");
        case AT_DOUBLE:
            return pLoader->load_class("[D");
        default:
            std::cout << "error array type" << std::endl;
            return nullptr;
    }
}

void ARRAY_LENGTH::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto object = stack->pop_ref();
    auto a_type = ((ArrayObject0*)object)->type;
    auto len = 0;
    if (a_type == AT_LONG) {
        len = ((ArrayObject<long>*)object)->size();
    }else if (a_type == AT_INT) {
        len = ((ArrayObject<int>*)object)->size();
    }else if (a_type == AT_FLOAT) {
        len = ((ArrayObject<float>*)object)->size();
    }else if (a_type == AT_DOUBLE) {
        len = ((ArrayObject<double>*)object)->size();
    }else if (a_type == AT_OBJECT) {
        len = ((ArrayObject<Object*>*)object)->size();
    }
    stack->push_int(len);
}

void C_A_LOAD::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_INT);
    auto ch = ((ArrayObject<int>*)(array))->arr->at(idx);
    stack->push_int(ch);
}

void I_A_LOAD::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_INT);
    auto ch = ((ArrayObject<int>*)(array))->arr->at(idx);
    stack->push_int(ch);
}

void A_A_LOAD::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_OBJECT);
    auto ch = ((ArrayObject<Object*>*)(array))->arr->at(idx);
    stack->push_ref(ch);
}

void I_A_STORE::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto val = stack->pop_int();
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_INT);
    ((ArrayObject<int>*)(array))->arr->at(idx) = val;
}

void C_A_STORE::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto val = stack->pop_int();
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_INT);
    ((ArrayObject<int>*)(array))->arr->at(idx) = val;
}

void A_A_STORE::execute(Frame *frame) {
    auto stack = frame->operation_stack;
    auto val = stack->pop_ref();
    auto idx = stack->pop_int();
    auto array = stack->pop_ref();
    assert(((ArrayObject0*)(array))->type == AT_OBJECT);
    ((ArrayObject<Object*>*)(array))->arr->at(idx) = val;
}
