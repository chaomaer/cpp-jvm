//
// Created by chaomaer on 2023/2/7.
//

#include "classLoader.h"
#include "parser/byteCodeParser.h"
#include "iostream"

Class *ClassLoader::load_class(std::string class_name) {
    if (class_map->count(class_name)) {
        return class_map->at(class_name);
    }
    Class* val = load_non_array_class(class_name);
    std::cout << "load class " << class_name << " over " << std::endl;
    return val;
}

Class* ClassLoader::load_non_array_class(std::string class_name) {
    // read class file
    auto class_file = read_class(class_name);
    // generate class
    Class* _class = define_class(class_file);
    (*class_map)[class_name] = _class;
    // link class
    link_class(_class);
    return _class;
}

ClassFile* ClassLoader::read_class(std::string class_name) {
    auto class_parser = new ByteCodeParser(BufferedInputStream(std::move(class_name)));
    auto class_file = class_parser->parse();
    return class_file;
}

Class *ClassLoader::define_class(ClassFile *class_file) {
    auto * _class = new Class(class_file);
    _class->class_loader = this;
    resolve_super(_class);
    resolve_interfaces(_class);
    return _class;
}

void ClassLoader::resolve_super(Class *pClass) {
    auto name = pClass->name;
    if (name != "java/lang/Object") {
        pClass->super_class = load_class(pClass->superClass_name);
    }
}

void ClassLoader::resolve_interfaces(Class *pClass) {
    auto interfaces = *pClass->interface_names;
    pClass->interface_classes = new std::vector<Class*>(interfaces.size());
    for (int i = 0; i<interfaces.size(); i++) {
        pClass->interface_classes->at(i) = load_class(interfaces.at(i));
    }
}

void ClassLoader::link_class(Class *pClass) {
    verify(pClass);
    prepare(pClass);
}

void ClassLoader::verify(Class *pClass) {
}

void ClassLoader::prepare(Class *pClass) {
    pClass->calc_instance_field_ids();
    pClass->calc_static_field_ids();
    pClass->init_static_fields();
}

ClassLoader::ClassLoader(): class_map(new std::unordered_map<std::string, Class*>) {
}

