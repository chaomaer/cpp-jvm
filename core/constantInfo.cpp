//
// Created by chaomaer on 2023/1/29.
//

#include "constantInfo.h"

std::string ConstantPool::get_utf8(uint16 index) {
    auto* info = (ConstantUTF8Info*)this->at(index);
    return info->val;
}

ConstantPool::ConstantPool(uint16 cnt) : std::vector<ConstantInfo *>(cnt) {

}
