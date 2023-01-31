//
// Created by chaomaer on 2023/1/31.
//

#include "frame.h"

union float_int {
    float f_val;
    int i_val;
};

union double_long {
    double d_val;
    long l_val;
};

void LocalVars::set_int(int idx, int val) {
    this->at(idx) = new Slot(val);
}

int LocalVars::get_int(int idx) {
    return this->at(idx)->numb;
}

void LocalVars::set_float(int idx, float val) {
    float_int floatInt{};
    floatInt.f_val = val;
    this->at(idx) = new Slot(floatInt.i_val);
}

float LocalVars::get_float(int idx) {
    float_int floatInt{};
    floatInt.i_val = this->at(idx)->numb;
    return floatInt.f_val;
}

void LocalVars::set_long(int idx, long val) {
    int val1 = val;
    int val2 = (long)val >> 32;
    set_int(idx, val1);
    set_int(idx+1, val2);
}

long LocalVars::get_long(int idx) {
    int val1 = get_int(idx);
    int val2 = get_int(idx+1);
    return (long )val2 << 32 | (val1 & 0xffffffffL);
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
    this->at(idx) = new Slot(ref);
}

Object *LocalVars::get_ref(int idx) {
    return this->at(idx)->ref;
}

LocalVars::LocalVars(int size): std::vector<Slot *>(size) {
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
    long val = get_long(index-2);
    index -= 2;
    return val;
}

void OperationStack::push_double(double val) {
    set_double(index, val);
    index+= 2;
}

double OperationStack::pop_double() {
    double val = get_double(index-2);
    index -= 2;
    return val;
}

void OperationStack::push_ref(Object *ref) {
    set_ref(index++, ref);
}

Object *OperationStack::pop_ref() {
    return get_ref(--index);
}

OperationStack::OperationStack(int size): size(size), index(0), LocalVars(size) {

}

Frame::Frame(int maxStack, int maxLocals) : max_stack(maxStack), max_locals(maxLocals) {
    local_vars = new LocalVars(max_locals);
    operation_stack = new OperationStack(max_stack);
}
