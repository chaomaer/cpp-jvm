//
// Created by chaomaer on 2023/2/28.
//

#ifndef CPP_JVM2_HEAPOBJECT_H
#define CPP_JVM2_HEAPOBJECT_H
#include "common/localArray.h"
#include "vector"

class Class;
class ObjectLocalVars;
class HeapObject {
public:
    Class* _class;
    ObjectLocalVars* fields;
    Class* extra;
};

class ArrayObject0 : public HeapObject {
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

#endif //CPP_JVM2_HEAPOBJECT_H
