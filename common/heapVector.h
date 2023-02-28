//
// Created by chaomaer on 2023/2/28.
//

#ifndef CPP_JVM2_HEAPVECTOR_H
#define CPP_JVM2_HEAPVECTOR_H

#include "vector"
#include "heapAllocator.h"
#include "iostream"

template<typename T>
class HeapVector : public std::vector<T, HeapAllocator<T>> {
public:
    //using std::vector<T, HeapVector<T>>::vector;
    HeapVector(int i): std::vector<T, HeapAllocator<T>>(i) {}
    HeapVector(): std::vector<T, HeapAllocator<T>>(){}
    //using std::vector<T, HeapVector<T>>::vector;
    void *operator new(std::size_t n) {
        return MemBuffer::allocate(n);
    }
};

#endif //CPP_JVM2_HEAPVECTOR_H
