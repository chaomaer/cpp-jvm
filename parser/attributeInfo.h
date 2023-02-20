//
// Created by chaomaer on 2023/1/30.
//

#ifndef CPP_JVM2_ATTRIBUTEINFO_H
#define CPP_JVM2_ATTRIBUTEINFO_H

#include "common/type.h"
#include "constantInfo.h"
#include "vector"

class AttributeInfo {
public:
    std::string attribute_name;
};

class DeprecatedAttribute : public AttributeInfo {
};

class SyntheticAttribute : public AttributeInfo {
};

class SignatureAttribute : public AttributeInfo {
public:
    ConstantPool* cp;
    uint16 signature_index;
};

class SourceFileAttribute : public AttributeInfo {
public:
    ConstantPool* cp;
    uint16 sourcefile_index;
};

class ConstantValueAttribute : public AttributeInfo {
public:
    ConstantPool* cp;
    uint16 constant_value_index;
};

class ExceptionTableEntry {
public:
    ExceptionTableEntry(uint16 startPc, uint16 endPc, uint16 handlerPc, uint16 catchType);
    uint16 start_pc;
    uint16 end_pc;
    uint16 handler_pc;
    uint16 catch_type;
};

class CodeAttribute : public AttributeInfo {
public:
    ConstantPool* cp;
    uint16 max_stack;
    uint16 max_locals;
    uint8* byte_code;
    int len;
    std::vector<ExceptionTableEntry*>* exception_table;
    std::vector<AttributeInfo*>* attributes;
};

class ExceptionAttribute : public AttributeInfo {
public:
    uint16 number_of_exceptions;
    uint16* exception_index_table;
};

class LineNumberTableEntry {
public:
    LineNumberTableEntry(uint16 startPc, uint16 lineNumber);

    uint16 start_pc;
    uint16 line_number;
};

class LineNumberTableAttribute : public AttributeInfo {
public:
    uint16 line_number_table_length;
    std::vector<LineNumberTableEntry*>* lineNumberTable;
};

class LocalVariableTableEntry {
public:
    LocalVariableTableEntry(uint16 startPc, uint16 length, uint16 nameIndex, uint16 descriptorIndex, uint16 index);

    uint16 start_pc;
    uint16 length;
    uint16 name_index;
    uint16 descriptor_index;
    uint16 index;
};

class LocalVariableTableAttribute : public AttributeInfo {
public:
    uint16 local_variable_table_length;
    std::vector<LocalVariableTableEntry*>* localVariableTable;
};




#endif //CPP_JVM2_ATTRIBUTEINFO_H
