#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"
#include "core/universe.h"
#include "native/object.h"

void start_jvm() {
    // init native function
    Universe::init();
    auto registry = Universe::registry;
    NativeObject::init(registry);
    std::cout << registry->size() << std::endl;
    auto ps = new std::vector<std::string>{"/Users/chaomaer/jvm-demo/target/classes/", "/Users/chaomaer/Desktop/lib/"};
    auto class_loader = new ClassLoader(ps);
    auto class_name = "BubbleSortTest";
    auto main_class = class_loader->load_class(class_name);

    auto main_method = main_class->find_main_method();
    if (main_method == nullptr) {
        std::cout << "no main method" << std::endl;
        exit(-1);
    }
    auto vm = new VMThread(main_method);
    auto t = vm->start();
    t->join();
}

int main() {
    start_jvm();
}