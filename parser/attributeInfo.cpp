//
// Created by chaomaer on 2023/1/30.
//

#include "attributeInfo.h"

ExceptionTableEntry::ExceptionTableEntry(uint16 startPc, uint16 endPc, uint16 handlerPc, uint16 catchType) : start_pc(
        startPc), end_pc(endPc), handler_pc(handlerPc), catch_type(catchType) {}

LineNumberTableEntry::LineNumberTableEntry(uint16 startPc, uint16 lineNumber) : start_pc(startPc),
                                                                                line_number(lineNumber) {}

LocalVariableTableEntry::LocalVariableTableEntry(uint16 startPc, uint16 length, uint16 nameIndex,
                                                 uint16 descriptorIndex, uint16 index) : start_pc(startPc),
                                                                                         length(length),
                                                                                         name_index(nameIndex),
                                                                                         descriptor_index(
                                                                                                 descriptorIndex),
                                                                                         index(index) {}

CodeAttribute::~CodeAttribute() {
    delete byte_code;
    for (auto& et : *exception_table) {
        delete et;
    }
    delete exception_table;
    for (auto& att: *attributes) {
        delete att;
    }
    delete attributes;
}

ExceptionAttribute::~ExceptionAttribute() {
    delete exception_index_table;
}

LineNumberTableAttribute::~LineNumberTableAttribute() {
    for (auto& le: *lineNumberTable) {
        delete le;
    }
    delete lineNumberTable;
}

LocalVariableTableAttribute::~LocalVariableTableAttribute() {
    for (auto& le: *localVariableTable) {
        delete le;
    }
    delete localVariableTable;
}
