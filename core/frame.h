//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_FRAME_H
#define CPP_JVM_FRAME_H

#include "vector"
#include "stack"
#include "thread.h"
#include "heap/class.h"

class Class;
class LocalVars;
class Object {
public:
    Class* _class;
    LocalVars* fields;
    Class* extra;
};

class ArrayObject0 : public Object {
public:
    int type;
};

template<typename T>
class ArrayObject : public ArrayObject0 {
public:
    ArrayObject(Class* aClass, int size);
    std::vector<T>* arr;
    int size();
};

// primitive type or reference type or array type
class Slot {
public:
    Slot(int numb);

    Slot(Object *ref);

public:
    int numb;
    Object* ref;
};


class LocalVars{
public:
    std::vector<Slot *>* _inner;
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

    void set_ref(int idx, Object *ref);

    Object *get_ref(int idx);
};

class OperationStack : public LocalVars {
private:
    int index;
    int size;
public:
    Slot* top();
    Object* top_ref(int number);
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

    void push_ref(Object *ref);

    Object *pop_ref();
};

class Method;
class FrameManager;
class Frame {
public:
    int pc;
    int max_stack;
    int max_locals;
    FrameManager* manager;
    Method* method;
public:
    LocalVars *local_vars;
    OperationStack *operation_stack;
public:
    Frame(int maxStack, int maxLocals, FrameManager* manager, Method* method);
    Frame(FrameManager* manager, Method* method);
    void branch(short offset);
};

#endif //CPP_JVM_FRAME_H
