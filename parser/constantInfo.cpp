//
// Created by chaomaer on 2023/1/29.
//

#include "constantInfo.h"
#include<cassert>

std::string ConstantPool::get_utf8(uint16 index) {
    auto *info = (ConstantUTF8Info *) this->at(index);
    assert(info->type == CONSTANT_Utf8);
    return info->val;
}

std::string ConstantPool::get_class_name(uint16 index) {
    auto *info = (ConstantClassInfo *) this->at(index);
    if (info == nullptr) return "";
    assert(info->type == CONSTANT_Class);
    return get_utf8(info->class_index);
}

ConstantPool::ConstantPool(uint16 cnt) : std::vector<ConstantInfo *>(cnt) {

}

std::pair<std::string, std::string> ConstantPool::get_name_and_type(uint16 index) {
    auto *info = (ConstantNameAndTypeInfo *) this->at(index);
    return {get_utf8(info->name_index), get_utf8(info->descriptor_index)};
}

ConstantInfo::ConstantInfo(int type) : type(type) {

}

ConstantIntegerInfo::ConstantIntegerInfo() : ConstantInfo(CONSTANT_Integer) {

}

ConstantLongInfo::ConstantLongInfo() : ConstantInfo(CONSTANT_Long) {

}

ConstantFloatInfo::ConstantFloatInfo() : ConstantInfo(CONSTANT_Float) {

}

ConstantDoubleInfo::ConstantDoubleInfo() : ConstantInfo(CONSTANT_Double) {

}

ConstantUTF8Info::ConstantUTF8Info() : ConstantInfo(CONSTANT_Utf8) {

}

ConstantStringInfo::ConstantStringInfo() : ConstantInfo(CONSTANT_String) {

}

ConstantClassInfo::ConstantClassInfo() : ConstantInfo(CONSTANT_Class) {

}

ConstantNameAndTypeInfo::ConstantNameAndTypeInfo() : ConstantInfo(CONSTANT_NameAndType) {

}

ConstantMemberRefInfo::ConstantMemberRefInfo(int type) : ConstantInfo(type) {

}

ConstantMethodRefInfo::ConstantMethodRefInfo() : ConstantMemberRefInfo(CONSTANT_Methodref) {

}

ConstantFieldRefInfo::ConstantFieldRefInfo() : ConstantMemberRefInfo(CONSTANT_Fieldref) {

}

ConstantInterfaceMethodRefInfo::ConstantInterfaceMethodRefInfo() : ConstantMemberRefInfo(CONSTANT_InterfaceMethodref) {

}
