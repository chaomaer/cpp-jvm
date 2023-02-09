//
// Created by chaomaer on 2023/2/9.
//

#include "reference.h"
#include <iostream>

void static_put(OperationStack* stack, LocalVars* vars, Field* f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        vars->set_int(id, stack->pop_int());
    }else if (des == "J") {
        vars->set_long(id, stack->pop_long());
    }else if (des == "F") {
        vars->set_float(id, stack->pop_float());
    }else if (des == "D") {
        vars->set_double(id, stack->pop_double());
    }else if (des == "L") {
        vars->set_ref(id, stack->pop_ref());
    }else {
        std::cout << "unsupported descriptor" << std::endl;
    }
}

void static_get(OperationStack* stack, LocalVars* vars, Field* f) {
    auto id = f->slot_id;
    auto des = f->descriptor;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        stack->push_int(vars->get_int(id));
    }else if (des == "J") {
        stack->push_long(vars->get_long(id));
    }else if (des == "F") {
        stack->push_float(vars->get_float(id));
    }else if (des == "D") {
        stack->push_double(vars->get_double(id));
    }else if (des == "L") {
        stack->push_ref(vars->get_ref(id));
    }else {
        std::cout << "unsupported descriptor" << std::endl;
    }
}

void field_put(OperationStack* stack, Field* f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        auto val = stack->pop_int();
        auto ref = stack->pop_ref();
        ref->fields->set_int(id, val);
    }else if (des == "J") {
        auto val = stack->pop_long();
        auto ref = stack->pop_ref();
        ref->fields->set_long(id, val);
    }else if (des == "F") {
        auto val = stack->pop_float();
        auto ref = stack->pop_ref();
        ref->fields->set_float(id, val);
    }else if (des == "D") {
        auto val = stack->pop_double();
        auto ref = stack->pop_ref();
        ref->fields->set_double(id, val);
    }else if (des == "L") {
        auto val = stack->pop_ref();
        auto ref = stack->pop_ref();
        ref->fields->set_ref(id, val);
    }else {
        std::cout << "unsupported descriptor" << std::endl;
    }
}

void field_get(OperationStack* stack, Field* f) {
    auto des = f->descriptor;
    auto id = f->slot_id;
    auto vars = stack->pop_ref()->fields;
    if (des == "Z" || des == "B" || des == "C" || des == "S" || des == "I") {
        stack->push_int(vars->get_int(id));
    }else if (des == "J") {
        stack->push_long(vars->get_long(id));
    }else if (des == "F") {
        stack->push_float(vars->get_float(id));
    }else if (des == "D") {
        stack->push_double(vars->get_double(id));
    }else if (des == "L") {
        stack->push_ref(vars->get_ref(id));
    }else {
        std::cout << "unsupported descriptor" << std::endl;
    }
}

void NEW::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef*)cp->at(index);
    auto _class = class_ref->resolve_class_ref();
    auto object = _class->new_object();
    frame->operation_stack->push_ref(object);
}

void PUT_STATIC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef*)cp->at(index);
    auto field = field_ref->resolve_field_ref();
    static_put(frame->operation_stack, field->_class->static_vars, field);
}

void GET_STATIC::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef*)cp->at(index);
    auto field = field_ref->resolve_field_ref();
    static_get(frame->operation_stack, field->_class->static_vars, field);
}

void PUT_FIELD::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef*)cp->at(index);
    auto field = field_ref->resolve_field_ref();
    field_put(frame->operation_stack, field);
}

void GET_FIELD::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto field_ref = (FieldRef*)cp->at(index);
    auto field = field_ref->resolve_field_ref();
    field_get(frame->operation_stack, field);
}

void IS_INSTANCE_OF::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef*)cp->at(index);
    auto ref_class = class_ref->resolve_class_ref();
    auto stack = frame->operation_stack;
    auto ref = stack->pop_ref();
    // todo 处理接口
    if (ref->_class->is_sub_of(ref_class)) {
        stack->push_int(1);
    }else {
        stack->push_int(0);
    }
}

void CHECK_CAST::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto class_ref = (ClassRef*)cp->at(index);
    auto ref_class = class_ref->resolve_class_ref();
    auto stack = frame->operation_stack;
    auto ref = stack->pop_ref();
    stack->push_ref(ref);
    // todo 处理接口
    if (ref->_class->is_sub_of(ref_class)) {

    }else {
        std::cout << "can't cast " << std::endl;
    }
}

void INVOKE_SPECIAL::execute(Frame *frame) {
    // todo
    frame->operation_stack->pop_ref();
}
void INVOKE_VIRTUAL::execute(Frame *frame) {
    auto cp = frame->method->_class->rt_constant_pool;
    auto method_ref = (MethodRef*)cp->at(index);
    auto stack = frame->operation_stack;
    auto des = method_ref->descriptor;
    std::cout << "************" << std::endl;
    if (method_ref->name == "println") {
        if (des == "(Z)V") {
            std::cout << (stack->pop_int() == 1) << std::endl;
        }else if (des == "(C)V" || des == "(B)V" || des == "(S)V" || des == "(I)V") {
            std::cout << stack->pop_int() << std::endl;
        }else if (des == "(F)V") {
            std::cout << stack->pop_float() << std::endl;
        }else if (des == "(D)V") {
            std::cout << stack->pop_double() << std::endl;
        }else if (des == "(J)V") {
            std::cout << stack->pop_long() << std::endl;
        }else {
            std::cout << "unsupported type" << std::endl;
        }
    }
}
