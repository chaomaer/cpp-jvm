//
// Created by chaomaer on 2023/2/16.
//

#include "object.h"

void NativeObject::init(NativeRegistry* registry){
    registry->_register("java/lang/Object", "getClass", "()Ljava/lang/Class;", getClass);
    registry->_register("java/lang/Class", "getPrimitiveClass",
                        "(Ljava/lang/String;)Ljava/lang/Class;", getPrimitiveClass);
    registry->_register("java/lang/Class", "getName0", "()Ljava/lang/String;", getName0);
    registry->_register("java/lang/Class", "desiredAssertionStatus0",
                        "(Ljava/lang/Class;)Z", desiredAssertionStatus0);
    registry->_register("java/lang/Thread", "currentThread",
                        "()Ljava/lang/Thread;", currentThread);
    registry->_register("java/security/AccessController", "getStackAccessControlContext",
                        "()Ljava/security/AccessControlContext;", getStackAccessControlContext);
}

void NativeObject::getClass(Frame *frame) {
    auto _this = frame->local_vars->get_ref(0);
    frame->operation_stack->push_ref(_this->_class->jClass);
}

void NativeObject::getPrimitiveClass(Frame *frame) {
    auto name = frame->local_vars->get_ref(0);
    auto str_name = to_string(name);
    auto loader = frame->method->_class->class_loader;
    auto _class = loader->load_class(str_name);
    frame->operation_stack->push_ref(_class->jClass);
}

void NativeObject::getName0(Frame *frame) {
    auto _this = frame->local_vars->get_ref(0);
    auto str_object = new_string_object(_this->extra->class_loader, _this->extra->name);
    frame->operation_stack->push_ref(str_object);
}

void NativeObject::desiredAssertionStatus0(Frame *frame) {
    frame->operation_stack->push_int(0);
}

void NativeObject::currentThread(Frame *frame) {
    //todo 暂行方案
    auto class_loader = frame->method->_class->class_loader;
    auto thread_class = class_loader->load_class("java/lang/Thread");
    auto group_class = class_loader->load_class("java/lang/ThreadGroup");
    auto thread_object = thread_class->new_object();
    auto group_object = group_class->new_object();
    auto group_f = thread_class->lookup_field("group", "Ljava/lang/ThreadGroup;");
    auto group_id = group_f->slot_id;
    thread_object->fields->set_ref(group_id, group_object);
    auto priority_f = thread_class->lookup_field("priority", "I");
    auto priority_id = priority_f->slot_id;
    thread_object->fields->set_int(priority_id, 1);
    frame->operation_stack->push_ref(thread_object);
}

void NativeObject::getStackAccessControlContext(Frame *frame) {
    //todo 暂行方案
    frame->operation_stack->push_ref(nullptr);
}
