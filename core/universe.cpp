//
// Created by chaomaer on 2023/2/19.
//

#include "universe.h"

NativeRegistry* Universe::registry = nullptr;

void Universe::init() {
    registry = NativeRegistry::get_registry();
}
