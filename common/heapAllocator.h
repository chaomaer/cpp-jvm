//
// Created by chaomaer on 2023/2/28.
//

#ifndef CPP_JVM2_HEAPALLOCATOR_H
#define CPP_JVM2_HEAPALLOCATOR_H
#include "iostream"

class MemBuffer {
public:
    static std::mutex lock;
    static int index;
    static char* buffer;
public:
    static void* allocate(int size) {
        std::lock_guard<std::mutex> guard(lock);
        auto p = buffer + index;
        index += size;
        return p;
    }
};

template<typename T>
class HeapAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    HeapAllocator() = default;
    pointer allocate(std::size_t n) {
        auto p = MemBuffer::allocate(sizeof (value_type)*n);
        return static_cast<T*>(p);
    }
    void deallocate(T* p, std::size_t n) {
        //gc 处理
        //std::cout << "deallocate " << n << std::endl;
    }
};

template<class T, class U>
bool operator==(const HeapAllocator <T>&, const HeapAllocator <U>&) { return true; }

template<class T, class U>
bool operator!=(const HeapAllocator <T>&, const HeapAllocator <U>&) { return false; }

#endif //CPP_JVM2_HEAPALLOCATOR_H
