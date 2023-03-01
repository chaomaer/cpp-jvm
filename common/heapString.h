//
// Created by chaomaer on 2023/2/28.
//

#ifndef CPP_JVM2_HEAPSTRING_H
#define CPP_JVM2_HEAPSTRING_H
#include "string"
#include "heapAllocator.h"

typedef std::basic_string<char, std::char_traits<char>, HeapAllocator<char>> JString;
class HeapString :  public JString {
public:
    using JString::basic_string;
    void* operator new(std::size_t n) {
        return MemBuffer::allocate(n);
    }
};

std::string heapStr_to_str(HeapString s);
HeapString str_to_heapStr(std::string s);

#endif //CPP_JVM2_HEAPSTRING_H
