//
// Created by chaomaer on 2023/1/29.
//

#include "byteCodeParser.h"
#include "iostream"
#include "constantInfo.h"
#include "string"

ByteCodeParser::ByteCodeParser(BufferedInputStream br) : br(br) {
}

ClassFile *ByteCodeParser::parse() {
    auto *classFile = new ClassFile;
    uint32 magic_number = br.read_uint32();
    classFile->magic = magic_number;
    uint16 minor_version = br.read_uint16();
    classFile->minor_version = minor_version;
    uint16 major_version = br.read_uint16();
    classFile->major_version = major_version;
//    std::cout << "magic_num " << magic_number << std::endl;
//    std::cout << "minor_version " << minor_version << std::endl;
//    std::cout << "major_version " << major_version << std::endl;
    // loads constant pool
    auto cp = load_constant_pool();;
    classFile->constant_pool = cp;
    // access flag & this class & super class
    classFile->access_flags = br.read_uint16();
    classFile->this_class = br.read_uint16();
    classFile->super_class = br.read_uint16();
    // interfaces
    uint16 interface_cnt = br.read_uint16();
    classFile->interfaces_count = interface_cnt;
    classFile->interfaces = new uint16[interface_cnt];
    for (int i = 0; i < interface_cnt; i++) {
        classFile->interfaces[i] = br.read_uint16();
    }
    // fields
    classFile->fields_count = br.read_uint16();
    classFile->fields = new std::vector<FieldInfo *>(classFile->fields_count);
    for (int i = 0; i < classFile->fields_count; i++) {
        auto field = new FieldInfo();
        field->cp = cp;
        field->access_flags = br.read_uint16();
        field->name_index = br.read_uint16();
        field->descriptor_index = br.read_uint16();
        field->attributes = load_attributes(classFile->constant_pool);
        classFile->fields->at(i) = field;
    }
    // methods
    classFile->methods_count = br.read_uint16();
    classFile->methods = new std::vector<MethodInfo *>(classFile->methods_count);
    for (int i = 0; i < classFile->methods_count; i++) {
        auto method = new MethodInfo();
        method->cp = cp;
        method->access_flags = br.read_uint16();
        method->name_index = br.read_uint16();
        method->descriptor_index = br.read_uint16();
        method->attributes = load_attributes(classFile->constant_pool);
        classFile->methods->at(i) = method;
    }
    // attributes
    classFile->attributes = load_attributes(classFile->constant_pool);
    return classFile;
}

std::vector<AttributeInfo *> *ByteCodeParser::load_attributes(ConstantPool *cp) {
    uint16 attribute_cnt = br.read_uint16();
    auto *attributes = new std::vector<AttributeInfo *>(attribute_cnt);
    for (int i = 0; i < attribute_cnt; i++) {
        uint16 attribute_name_index = br.read_uint16();
        auto attribute_name = cp->get_utf8(attribute_name_index);
        // std::cout << "attribute name: " << attribute_name << std::endl;
        attributes->at(i) = read_one_attribute(attribute_name, cp);
    }
    return attributes;
}

AttributeInfo *ByteCodeParser::read_one_attribute(std::string attribute_name, ConstantPool *cp) {
    uint32 attribute_len = br.read_uint32();
    if (attribute_name == "ConstantValue") {
        auto* const_attr = new ConstantValueAttribute;
        const_attr->attribute_name = attribute_name;
        const_attr->constant_value_index = br.read_uint16();
        const_attr->cp = cp;
        return const_attr;
    } else if (attribute_name == "Signature") {
        auto *sig_attr = new SignatureAttribute();
        sig_attr->cp = cp;
        sig_attr->attribute_name = attribute_name;
        sig_attr->signature_index = br.read_uint16();
        std::cout << cp->get_utf8(sig_attr->signature_index) << std::endl;
        return sig_attr;
    } else if (attribute_name == "Code") {
        auto *code_attr = new CodeAttribute();
        code_attr->cp = cp;
        code_attr->attribute_name = attribute_name;
        code_attr->max_stack = br.read_uint16();
        code_attr->max_locals = br.read_uint16();
        int byte_cnt = br.read_uint32();
        code_attr->len = byte_cnt;
        code_attr->byte_code = new uint8[byte_cnt];
        for (int i = 0; i < byte_cnt; i++) {
            code_attr->byte_code[i] = br.read_uint8();
        }
        int exception_table_len = br.read_uint16();
        code_attr->exception_table = new std::vector<ExceptionTableEntry *>(exception_table_len);
        for (int i = 0; i < exception_table_len; i++) {
            code_attr->exception_table->at(i) = new ExceptionTableEntry{
                    br.read_uint16(), br.read_uint16(), br.read_uint16(), br.read_uint16()
            };
        }
        code_attr->attributes = load_attributes(cp);
        return code_attr;
    } else if (attribute_name == "LineNumberTable") {
        auto line_attr = new LineNumberTableAttribute();
        line_attr->attribute_name = attribute_name;
        int line_len = br.read_uint16();
        line_attr->line_number_table_length = line_len;
        line_attr->lineNumberTable = new std::vector<LineNumberTableEntry *>(line_len);
        for (int i = 0; i < line_len; i++) {
            line_attr->lineNumberTable->at(i) = new LineNumberTableEntry{
                    br.read_uint16(), br.read_uint16()
            };
        }
        return line_attr;
    } else if (attribute_name == "LocalVariableTable") {
        auto local_attr = new LocalVariableTableAttribute;
        local_attr->attribute_name = attribute_name;
        int local_len = br.read_uint16();
        local_attr->local_variable_table_length = local_len;
        local_attr->localVariableTable = new std::vector<LocalVariableTableEntry *>(local_len);
        for (int i = 0; i < local_len; i++) {
            local_attr->localVariableTable->at(i) = new LocalVariableTableEntry{
                    br.read_uint16(), br.read_uint16(), br.read_uint16(), br.read_uint16(), br.read_uint16()
            };
        }
        return local_attr;
    } else if (attribute_name == "SourceFile") {
        auto source_attr = new SourceFileAttribute();
        source_attr->cp = cp;
        source_attr->sourcefile_index = br.read_uint16();
        return source_attr;
    } else {
        // discard this attribute
        for (int i = 0; i < attribute_len; i++) {
            br.read_uint8();
        }
//        std::cout << ("unparsed attribute") << std::endl;
        return nullptr;
    }
}

ConstantPool *ByteCodeParser::load_constant_pool() {
    uint16 constant_pool_count = br.read_uint16();
    //std::cout << "constant_pool_count " << constant_pool_count << std::endl;
    auto *constantPool = new ConstantPool(constant_pool_count);
    for (int i = 1; i < constant_pool_count; i++) {
        uint8 constant_type = br.read_uint8();
        switch (constant_type) {
            case CONSTANT_Integer: {
                auto *x = new ConstantIntegerInfo();
                x->val = br.read_uint32();
                constantPool->at(i) = x;
                break;
            }
            case CONSTANT_Long: {
                auto *x = new ConstantLongInfo();
                constantPool->at(i) = x;
                x->val = br.read_uint64();
                i++;
                break;
            }
            case CONSTANT_Float: {
                auto *x = new ConstantFloatInfo();
                constantPool->at(i) = x;
                x->val = br.read_float();
                std::cout << x->val << " float" << std::endl;
                break;
            }
            case CONSTANT_Double: {
                auto *x = new ConstantDoubleInfo();
                constantPool->at(i) = x;
                x->val = br.read_double();
                std::cout << x->val << " double" << std::endl;
                i++;
                break;
            }
            case CONSTANT_Utf8: {
                int len = br.read_uint16();
                char str[len + 1];
                str[len] = '\0';
                for (int idx = 0; idx < len; idx++) {
                    str[idx] = br.read_uint8();
                }
                auto *x = new ConstantUTF8Info;
                constantPool->at(i) = x;
                x->val = std::string(str);
                // std::cout << "utf: " << i << " " << x->val << std::endl;
                break;
            }
            case CONSTANT_String: {
                uint16 string_index = br.read_uint16();
                auto *x = new ConstantStringInfo;
                constantPool->at(i) = x;
                x->string_index = string_index;
                break;
            }
            case CONSTANT_Class: {
                uint16 class_index = br.read_uint16();
                auto *x = new ConstantClassInfo;
                constantPool->at(i) = x;
                x->class_index = class_index;
                x->cp = constantPool;
                break;
            }
            case CONSTANT_NameAndType: {
                uint16 name_index = br.read_uint16();
                uint16 descriptor_index = br.read_uint16();
                auto *x = new ConstantNameAndTypeInfo;
                constantPool->at(i) = x;
                x->name_index = name_index;
                x->descriptor_index = descriptor_index;
                x->cp = constantPool;
                break;
            }
            case CONSTANT_Fieldref: {
                uint16 class_index = br.read_uint16();
                uint16 name_and_type_index = br.read_uint16();
                auto *x = new ConstantFieldRefInfo();
                constantPool->at(i) = x;
                x->class_index = class_index;
                x->name_and_type_index = name_and_type_index;
                x->cp = constantPool;
                break;
            }
            case CONSTANT_Methodref: {
                uint16 class_index = br.read_uint16();
                uint16 name_and_type_index = br.read_uint16();
                auto *x = new ConstantMethodRefInfo();
                constantPool->at(i) = x;
                x->class_index = class_index;
                x->name_and_type_index = name_and_type_index;
                x->cp = constantPool;
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                uint16 class_index = br.read_uint16();
                uint16 name_and_type_index = br.read_uint16();
                auto *x = new ConstantInterfaceMethodRefInfo();
                constantPool->at(i) = x;
                x->class_index = class_index;
                x->name_and_type_index = name_and_type_index;
                x->cp = constantPool;
                break;
            }
            case CONSTANT_InvokeDynamic: {
                br.discard_uint8s(4);
                break;
            }
            case CONSTANT_MethodHandle: {
                br.discard_uint8s(3);
                break;
            }
            case CONSTANT_MethodType: {
                br.discard_uint8s(2);
                break;
            }
        }
    }
    return constantPool;
}
