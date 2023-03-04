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
    void* operator new(std::size_t n);
    Class* _class{nullptr};
    ObjectLocalVars* fields{nullptr};
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
    HeapVector<T>* arr{nullptr};
    int size();
};

#endif //CPP_JVM2_HEAPOBJECT_H
