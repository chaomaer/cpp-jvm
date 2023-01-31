#include "iostream"
#include "core/byteCodeParser.h"

int main() {
    BufferedInputStream bf("/Users/chaomaer/jvm-demo/target/classes/HelloWord.class");
    ByteCodeParser bp(bf);
    bp.parse();
}