//
// Created by chaomaer on 2023/1/31.
//

#include "frame.h"
#include "iostream"
#include "heapObject.h"

#include <cassert>

void OperationStack::push_int(int val) {
    set_int(index++, val);
}

int OperationStack::pop_int() {
    int val = get_int(--index);
    return val;
}

void OperationStack::push_float(float val) {
    set_float(index++, val);
}

float OperationStack::pop_float() {
    float val = get_float(--index);
    return val;
}

void OperationStack::push_long(long val) {
    set_long(index, val);
    index += 2;
}

long OperationStack::pop_long() {
    long val = get_long(index - 2);
    index -= 2;
    return val;
}

void OperationStack::push_double(double val) {
    set_double(index, val);
    index += 2;
}

double OperationStack::pop_double() {
    double val = get_double(index - 2);
    index -= 2;
    return val;
}

void OperationStack::push_ref(HeapObject *ref) {
    set_ref(index++, ref);
}

HeapObject *OperationStack::pop_ref() {
    return get_ref(--index);
}

OperationStack::OperationStack(int size) : size(size), index(0), LocalVars(size) {

}

void OperationStack::push_slot(Slot *slot) {
    _inner->at(index++) = slot;
}

Slot *OperationStack::pop_slot() {
    return _inner->at(--index);
}

Slot *OperationStack::top() {
    assert(index >= 1 && "operation_stack size is < 1");
    return _inner->at(index - 1);
}

HeapObject *OperationStack::top_ref(int number) {
    auto slot = _inner->at(index-number);
    return slot->ref;
}

Frame::Frame(FrameManager* manager, Method *method) : manager(manager), pc(0), method(method) {
    max_locals = method->max_locals;
    max_stack = method->max_stack;
    local_vars = new OperationLocalVars(max_locals);
    operation_stack = new OperationStack(max_stack);
}

void Frame::branch(short offset) {
    pc = manager->pc + offset;
}

Frame::Frame(int maxStack, int maxLocals, FrameManager *manager, Method *method) :pc(0), max_stack(maxStack), max_locals(maxLocals),
                                                                                         manager(manager), method(method) {
    local_vars = new OperationLocalVars (max_locals);
    operation_stack = new OperationStack(max_stack);
}

Frame::~Frame() {
    if (local_vars != nullptr) {
        if (local_vars->_inner) {
            delete local_vars->_inner;
        }
        delete local_vars;
    }
    if (operation_stack != nullptr) {
        if (operation_stack->_inner) {
            delete operation_stack->_inner;
        }
        delete operation_stack;
    }
}

template<typename T>
ArrayObject<T>::ArrayObject(Class* aClass, int size) {
    arr = new HeapVector<T>(size);
    _class = aClass;
    if (std::is_same<T, float>::value) {
        type = AT_FLOAT;
    }else if (std::is_same<T, int>::value) {
        type = AT_INT;
    }else if (std::is_same<T, double>::value) {
        type = AT_DOUBLE;
    }else if (std::is_same<T, long>::value) {
        type = AT_LONG;
    }else {
        type = AT_OBJECT;
    }
}

template<typename T>
int ArrayObject<T>::size() {
    return arr->size();
}

//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
template class ArrayObject<int>;
template class ArrayObject<long>;
template class ArrayObject<float>;
template class ArrayObject<HeapObject*>;
template class ArrayObject<double>;

void *HeapObject::operator new(std::size_t n) {
    return MemBuffer::allocate(n);
}
