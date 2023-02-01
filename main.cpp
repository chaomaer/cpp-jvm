#include "iostream"
#include "parser/byteCodeParser.h"
#include "core/frame.h"
#include "test/test_frame.h"
#include "core/interpreter.h"

int main() {
    BufferedInputStream bf("/Users/chaomaer/jvm-demo/target/classes/HelloWord.class");
    ByteCodeParser bp(bf);
    auto class_file = bp.parse();
    auto interpreter = new Interpreter();
    interpreter->run(class_file);
}