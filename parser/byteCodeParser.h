//
// Created by chaomaer on 2023/1/29.
//

#ifndef CPP_JVM2_BYTECODEPARSER_H
#define CPP_JVM2_BYTECODEPARSER_H
#include "bufferedInputStream.h"
#include "classFile.h"

class ByteCodeParser {
public:
    BufferedInputStream* br;
public:
    explicit ByteCodeParser(BufferedInputStream* bf);
    ClassFile* parse();
    ConstantPool* load_constant_pool();
    std::vector<AttributeInfo*>* load_attributes(ConstantPool* cp);
    AttributeInfo* read_one_attribute(std::string attribute_name, ConstantPool* cp);
};

#endif //CPP_JVM2_BYTECODEPARSER_H
