//
// Created by chaomaer on 2023/2/16.
//

#include "native.h"
#include <cassert>

NativeRegistry* NativeRegistry::registry = nullptr;

NativeRegistry* NativeRegistry::get_registry() {
    if (registry == nullptr) {
        registry = new NativeRegistry();
    }
    return registry;
}

void NativeRegistry::_register(std::string class_name, std::string name, std::string des, nativeFunc func) {
    auto key = class_name + "::" + name + ":" + des;
    (*native_methods)[key] = func;
}

NativeRegistry::NativeRegistry() {
    native_methods = new std::unordered_map<std::string, nativeFunc>;
}

nativeFunc NativeRegistry::find_native_method(std::string class_name, std::string name, std::string des) {
    auto key = class_name + "::" + name + ":" + des;
    if (native_methods->count(key)) {
        return native_methods->at(key);
    }
    return [](Frame* frame) {};
}

int NativeRegistry::size() {
    assert(registry != nullptr);
    return registry->native_methods->size();
}
