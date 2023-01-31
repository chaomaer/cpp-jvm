cmake_minimum_required(VERSION 3.21)
project(cpp_jvm)

include_directories("./")
set(CMAKE_CXX_STANDARD 14)
add_executable(cpp_jvm main.cpp common/type.h core/classFile.h core/bufferedInputStream.cpp core/bufferedInputStream.h core/byteCodeParser.cpp core/byteCodeParser.h core/constantInfo.cpp core/constantInfo.h tools/mathUtil.cpp tools/mathUtil.h core/attributeInfo.cpp core/attributeInfo.h)
