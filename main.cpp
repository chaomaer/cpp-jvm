#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"
#include "core/universe.h"
#include "native/object.h"

void start_jvm(int argc, char** argv) {
    // init native function
    Universe::init();
    auto registry = Universe::registry;
    NativeObject::init(registry);
    std::cout << registry->size() << std::endl;
    auto ps = new std::vector<std::string>(argc);
    for (int i = 1; i<argc; i++) {
        std::cout << argv[i] << " =>加入classpath" << std::endl;
        ps->push_back(std::string(argv[i]));
    }
    auto class_loader = new ClassLoader(ps);
    auto class_name = argv[argc-1];
    auto main_class = class_loader->load_class(class_name);

    auto main_method = main_class->find_main_method();
    if (main_method == nullptr) {
        std::cout << "no main method" << std::endl;
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
    std::cout << MemBuffer::index << std::endl;
}