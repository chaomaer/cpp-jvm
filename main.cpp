#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"

void start_jvm() {
    auto class_loader = new ClassLoader();
    class_loader->class_paths->push_back("/Users/chaomaer/jvm-demo/target/classes/");
    class_loader->class_paths->push_back("/Users/chaomaer/Desktop/lib/");
    auto class_name = "BubbleSortTest";
    auto main_class = class_loader->load_class(class_name);

    auto main_method = main_class->find_main_method();
    if (main_method == nullptr) {
        std::cout << "no main method" << std::endl;
    }
    auto interpreter = new Interpreter();
    interpreter->run(main_method );
}

int main() {
    start_jvm();
}