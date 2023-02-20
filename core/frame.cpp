//
// Created by chaomaer on 2023/1/31.
//

#include "frame.h"
#include "iostream"

union float_int {
    float f_val;
    int i_val;
};

union double_long {
    double d_val;
    long l_val;
};

void LocalVars::set_slot(int idx, Slot *val) {
    (*_inner)[idx] = val;
}

void LocalVars::set_int(int idx, int val) {
    _inner->at(idx) = new Slot(val);
}

int LocalVars::get_int(int idx) {
    //todo 绕行方案
    auto s = _inner->at(idx);
    return s == nullptr ? 0 : s->numb;
}

void LocalVars::set_float(int idx, float val) {
    float_int floatInt{};
    floatInt.f_val = val;
    _inner->at(idx) = new Slot(floatInt.i_val);
}

float LocalVars::get_float(int idx) {
    float_int floatInt{};
    floatInt.i_val = _inner->at(idx)->numb;
    return floatInt.f_val;
}

void LocalVars::set_long(int idx, long val) {
    int val1 = val;
    int val2 = (long) val >> 32;
    set_int(idx, val1);
    set_int(idx + 1, val2);
}

long LocalVars::get_long(int idx) {
    int val1 = get_int(idx);
    int val2 = get_int(idx + 1);
    return (long) val2 << 32 | (val1 & 0xffffffffL);
}

void LocalVars::set_double(int idx, double val) {
    double_long doubleLong{};
    doubleLong.d_val = val;
    set_long(idx, doubleLong.l_val);
}

double LocalVars::get_double(int idx) {
    double_long doubleLong{};
    doubleLong.l_val = get_long(idx);
    return doubleLong.d_val;
}

void LocalVars::set_ref(int idx, Object *ref) {
    _inner->at(idx) = new Slot(ref);
}

Object *LocalVars::get_ref(int idx) {
    //todo 绕行方案
    auto s = _inner->at(idx);
    return s == nullptr ? nullptr : s->ref;
}

LocalVars::LocalVars(int size) {
    _inner = new std::vector<Slot*>(size);
}

void LocalVars::print() {
    for (int i = 0; i < _inner->size(); i++) {
        if (_inner->at(i) != nullptr) {
            std::cout << i << " -> " << _inner->at(i)->numb << std::endl;
        }
    }
    std::cout << "-------" << std::endl;
}

Slot::Slot(int numb) : numb(numb) {}

Slot::Slot(Object *ref) : ref(ref) {}

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

void OperationStack::push_ref(Object *ref) {
    set_ref(index++, ref);
}

Object *OperationStack::pop_ref() {
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

Object *OperationStack::top_ref(int number) {
    auto slot = _inner->at(index-number);
    return slot->ref;
}

Frame::Frame(Thread *thread, Method *method) : thread(thread), pc(0), method(method) {
    max_locals = method->max_locals;
    max_stack = method->max_stack;
    local_vars = new LocalVars(max_locals);
    operation_stack = new OperationStack(max_stack);
}

void Frame::branch(short offset) {
    pc = thread->pc + offset;
}

Frame::Frame(int maxStack, int maxLocals, Thread *thread, Method *method) :pc(0), max_stack(maxStack), max_locals(maxLocals),
                                                                            thread(thread), method(method) {
    local_vars = new LocalVars(max_locals);
    operation_stack = new OperationStack(max_stack);
}

template<typename T>
ArrayObject<T>::ArrayObject(Class* aClass, int size) {
    arr = new std::vector<T>(size);
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
template class ArrayObject<Object*>;
template class ArrayObject<double>;