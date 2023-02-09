#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"

void start_jvm() {
    auto class_loader = ClassLoader();
    auto class_name = "/Users/chaomaer/jvm-demo/target/classes/MyObject.class";
    auto main_class = class_loader.load_class(class_name);

    (*class_loader.class_map)["MyObject"] = main_class;
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