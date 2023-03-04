//
// Created by chaomaer on 2023/2/7.
//

#include "rtConsts.h"

ClassRef::ClassRef(ConstantClassInfo *info, RTConstantPool *cp) : ClassRef(info, cp, CONSTANT_Class) {
}

ClassRef::ClassRef(ConstantClassInfo *info, RTConstantPool *cp, int type) : SymRef(type) {
    if (type == CONSTANT_Class) {
        class_name = str_to_heapStr(info->cp->get_utf8(info->class_index));
    }else {
        class_name = str_to_heapStr(info->cp->get_class_name(info->class_index));
    }
    rt_cp = cp;
}

Class *ClassRef::resolve_class_ref() {
    if (_class != nullptr) {
        return _class;
    }
    auto cur_class = rt_cp->_class;
    _class = cur_class->class_loader->load_class(heapStr_to_str(class_name));
    // todo 权限控制
    return _class;
}

void MemberRef::copy_member_info(ConstantMemberRefInfo *info) {
    auto p = info->cp->get_name_and_type(info->name_and_type_index);
    name = str_to_heapStr(p.first);
    descriptor = str_to_heapStr(p.second);
    class_name = str_to_heapStr(info->cp->get_class_name(info->class_index));
}

MemberRef::MemberRef(ConstantMemberRefInfo *info, RTConstantPool *cp, int type) : ClassRef((ConstantClassInfo *) info,
                                                                                           cp, type) {
    copy_member_info((ConstantMemberRefInfo *) info);
}

Field *FieldRef::resolve_field_ref() {
    if (field != nullptr) {
        return field;
    }
    auto ref_class = resolve_class_ref();
    // todo 权限控制
    field = ref_class->lookup_field(name, descriptor);
    field->_class = ref_class;
    return field;
}

FieldRef::FieldRef(ConstantFieldRefInfo *info, RTConstantPool *cp) : MemberRef(info, cp, CONSTANT_Fieldref) {

}

MethodRef::MethodRef(ConstantMethodRefInfo *info, RTConstantPool *cp) : MethodRef(info, cp, CONSTANT_Methodref) {

}

MethodRef::MethodRef(ConstantMethodRefInfo *info, RTConstantPool *cp, int type) : MemberRef(info, cp, type) {

}

Method *MethodRef::resolve_method_ref() {
    if (method != nullptr) {
        return method;
    }
    auto ref_class = resolve_class_ref();
    method = ref_class->lookup_method(name, descriptor);
    method->_class = ref_class;
    return method;
}

InterfaceMethodRef::InterfaceMethodRef(ConstantInterfaceMethodRefInfo *info, RTConstantPool *cp) :
        MethodRef((ConstantMethodRefInfo *) info, cp, CONSTANT_InterfaceMethodref) {

}


RTConst::RTConst(uint16 type) : type(type) {

}

void *RTConst::operator new(std::size_t n) {
    return MemBuffer::allocate(n);
}

SymRef::SymRef(int type) : RTConst(type) {

}

RTInt_Const::RTInt_Const() : RTConst(CONSTANT_Integer) {

}

RTLong_Const::RTLong_Const() : RTConst(CONSTANT_Long) {

}

RTFloat_Const::RTFloat_Const() : RTConst(CONSTANT_Float) {

}

RTDouble_Const::RTDouble_Const() : RTConst(CONSTANT_Double) {

}

RTString_Const::RTString_Const() : RTConst(CONSTANT_String) {

}

RTClass_Const::RTClass_Const(): RTConst(CONSTANT_Class){

}
