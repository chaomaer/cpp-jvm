//
// Created by chaomaer on 2023/2/28.
//

#include "heapAllocator.h"

int MemBuffer::index;
char *MemBuffer::buffer = new char[1024*1024];
std::mutex MemBuffer::lock;
