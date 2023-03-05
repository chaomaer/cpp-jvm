#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"
#include "core/universe.h"
#include "native/object.h"
#include "common/debug.h"

void start_jvm(int argc, char** argv) {
    // init native function
    Universe::init();
    auto registry = Universe::registry;
    NativeObject::init(registry);
    auto ps = new std::vector<std::string>(argc);
    for (int i = 1; i<argc; i++) {
        DEBUG_MSG(argv[i] << " =>加入classpath");
        ps->push_back(std::string(argv[i]));
    }
    auto class_loader = new ClassLoader(ps);
    auto class_name = argv[argc-1];
    auto main_class = class_loader->load_class(class_name);

    auto main_method = main_class->find_main_method();
    if (main_method == nullptr) {
        DEBUG_MSG("no main method");
        exit(-1);
    }
    auto vm = new VMThread(main_method);
    vm->t->join();
    Universe::clean_up();
    delete vm;
    delete class_loader;
    delete ps;
    delete[] MemBuffer::buffer;
}

int main(int argc, char** argv) {
    start_jvm(argc, argv);
}