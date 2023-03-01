//
// Created by chaomaer on 2023/2/7.
//

#ifndef CPP_JVM2_CLASSLOADER_H
#define CPP_JVM2_CLASSLOADER_H
#include "vector"
#include "unordered_map"
#include "class.h"

class Class;
class ClassLoader {
public:
    std::vector<std::string>* class_paths;
    std::unordered_map<std::string, Class*>* class_map;
private:
    Class* load_non_array_class(std::string class_name);
    Class* load_array_class(std::string class_name);
    Class* load_primitive_class(std::string class_name);
public:
    ~ClassLoader();
    ClassLoader(std::vector<std::string>* path);
    Class* load_class(std::string class_name);
    ClassFile* read_class(std::string class_name);
    Class* define_class(ClassFile* class_file);
    void debug_class_map();
    void resolve_super(Class *pClass);
    void resolve_interfaces(Class *pClass);
    void link_class(Class *pClass);
    void verify(Class *pClass);
    void prepare(Class *pClass);
};

#endif //CPP_JVM2_CLASSLOADER_H
