//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_FRAME_H
#define CPP_JVM_FRAME_H

#include "vector"
#include "stack"

class Object {

};

// primitive type or reference type
class Slot {
public:
    Slot(int numb);

    Slot(Object *ref);

public:
    int numb;
    Object* ref;
};


class LocalVars : public std::vector<Slot *> {
public:
    LocalVars(int size);

    void set_int(int idx, int val);

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
    OperationStack(int size);

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

class Frame {
private:
    int max_stack;
    int max_locals;
    Frame *lower;
public:
    LocalVars *local_vars;
    OperationStack *operation_stack;
public:
    Frame(int maxStack, int maxLocals);
};

#endif //CPP_JVM_FRAME_H
