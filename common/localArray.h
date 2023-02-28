//
// Created by chaomaer on 2023/2/28.
//

#ifndef CPP_JVM2_LOCALARRAY_H
#define CPP_JVM2_LOCALARRAY_H
#include "vector"
#include "heapVector.h"
#include "core/heapObject.h"

// primitive type or reference type or array type
class HeapObject;
class Slot {
public:
    Slot(int numb);

    Slot(HeapObject *ref);

public:
    int numb;
    HeapObject* ref;
};

template<template<typename> class V>
class LocalVars {
public:
    V<Slot*>* _inner;
public:
    void print();

    LocalVars(int size);

    void set_int(int idx, int val);

    void set_slot(int idx, Slot* val);

    int get_int(int idx);

    void set_float(int idx, float val);

    float get_float(int idx);

    void set_long(int idx, long val);

    long get_long(int idx);

    void set_double(int idx, double val);

    double get_double(int idx);

    void set_ref(int idx, HeapObject *ref);

    HeapObject *get_ref(int idx);
};

template<typename T>
class StackVector : public std::vector<T>{
public:
    StackVector(int i): std::vector<T>(i) {};
};

class ObjectLocalVars : public LocalVars<HeapVector>{
public:
    ObjectLocalVars(int size): LocalVars<HeapVector>(size){}
};

typedef LocalVars<StackVector> OperationLocalVars;

class OperationStack : public LocalVars<StackVector> {
private:
    int index;
    int size;
public:
    Slot* top();
    HeapObject* top_ref(int number);
    OperationStack(int size);

    void push_slot(Slot* slot);

    Slot* pop_slot();

    void push_int(int val);

    int pop_int();

    void push_float(float val);

    float pop_float();

    void push_long(long val);

    long pop_long();

    void push_double(double val);

    double pop_double();

    void push_ref(HeapObject *ref);

    HeapObject *pop_ref();
};

#endif //CPP_JVM2_LOCALARRAY_H
