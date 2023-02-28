//
// Created by chaomaer on 2023/2/28.
//

#include "localArray.h"
#include "iostream"

Slot::Slot(int numb) : numb(numb) {}

Slot::Slot(HeapObject *ref) : ref(ref) {}

union float_int {
    float f_val;
    int i_val;
};

union double_long {
    double d_val;
    long l_val;
};

template<template<typename> class V>
void LocalVars<V>::set_slot(int idx, Slot *val) {
    (*_inner)[idx] = val;
}

template<template<typename> class V>
void LocalVars<V>::set_int(int idx, int val) {
    _inner->at(idx) = new Slot(val);
}

template<template<typename> class V>
int LocalVars<V>::get_int(int idx) {
    //todo 绕行方案
    auto s = _inner->at(idx);
    return s == nullptr ? 0 : s->numb;
}

template<template<typename> class V>
void LocalVars<V>::set_float(int idx, float val) {
    float_int floatInt{};
    floatInt.f_val = val;
    _inner->at(idx) = new Slot(floatInt.i_val);
}

template<template<typename> class V>
float LocalVars<V>::get_float(int idx) {
    float_int floatInt{};
    floatInt.i_val = _inner->at(idx)->numb;
    return floatInt.f_val;
}
template<template<typename> class V>
void LocalVars<V>::set_long(int idx, long val) {
    int val1 = val;
    int val2 = (long) val >> 32;
    set_int(idx, val1);
    set_int(idx + 1, val2);
}
template<template<typename> class V>
long LocalVars<V>::get_long(int idx) {
    int val1 = get_int(idx);
    int val2 = get_int(idx + 1);
    return (long) val2 << 32 | (val1 & 0xffffffffL);
}
template<template<typename> class V>
void LocalVars<V>::set_double(int idx, double val) {
    double_long doubleLong{};
    doubleLong.d_val = val;
    set_long(idx, doubleLong.l_val);
}
template<template<typename> class V>
double LocalVars<V>::get_double(int idx) {
    double_long doubleLong{};
    doubleLong.l_val = get_long(idx);
    return doubleLong.d_val;
}
template<template<typename> class V>
void LocalVars<V>::set_ref(int idx, HeapObject *ref) {
    _inner->at(idx) = new Slot(ref);
}
template<template<typename> class V>
HeapObject *LocalVars<V>::get_ref(int idx) {
    //todo 绕行方案
    auto s = _inner->at(idx);
    return s == nullptr ? nullptr : s->ref;
}

template<template<typename> class V>
LocalVars<V>::LocalVars(int size) {
    _inner = new V<Slot*>(size);
//    for (int i = 0; i < _inner->size(); i++) {
//        if (_inner->at(i) != nullptr) {
//            std::cout << i << " -> " << _inner->at(i)->numb << std::endl;
//        }
//    }
//    std::cout << "-------" << std::endl;
}

template<template<typename> class V>
void LocalVars<V>::print() {
    for (int i = 0; i < _inner->size(); i++) {
        if (_inner->at(i) != nullptr) {
            std::cout << i << " -> " << _inner->at(i)->numb << std::endl;
        }
    }
    std::cout << "-------" << std::endl;
}

template class LocalVars<StackVector>;
template class LocalVars<HeapVector>;