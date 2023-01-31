cmake_minimum_required(VERSION 3.21)
project(cpp_jvm)

include_directories("./")
set(CMAKE_CXX_STANDARD 14)
add_executable(cpp_jvm main.cpp common/type.h parser/classFile.h parser/bufferedInputStream.cpp parser/bufferedInputStream.h parser/byteCodeParser.cpp parser/byteCodeParser.h parser/constantInfo.cpp parser/constantInfo.h tools/mathUtil.cpp tools/mathUtil.h parser/attributeInfo.cpp parser/attributeInfo.h core/thread.cpp core/thread.h core/frame.cpp core/frame.h test/test_frame.h)
