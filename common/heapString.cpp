//
// Created by chaomaer on 2023/2/28.
//

#include "heapString.h"

std::string heapStr_to_str(HeapString s) {
    return *(std::string*)&s;
}
HeapString str_to_heapStr(std::string s) {
    return *(HeapString*)&s;
}