cmake_minimum_required(VERSION 3.20)
project(cpp_jvm)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "-std=c++17 -lstdc++fs -pthread") 

include_directories("./")
add_executable(cpp_jvm main.cpp common/type.h parser/bufferedInputStream.cpp parser/bufferedInputStream.h parser/byteCodeParser.cpp parser/byteCodeParser.h parser/constantInfo.cpp parser/constantInfo.h tools/mathUtil.cpp tools/mathUtil.h parser/attributeInfo.cpp parser/attributeInfo.h core/thread.cpp core/thread.h core/frame.cpp core/frame.h test/test_frame.h instructions/base/instruction.cpp instructions/base/instruction.h instructions/constants/constant.cpp instructions/constants/constant.h instructions/loads/load.cpp instructions/loads/load.h instructions/stores/store.cpp instructions/stores/store.h instructions/stacks/pop.cpp instructions/stacks/pop.h instructions/stacks/dup.cpp instructions/stacks/dup.h instructions/stacks/swap.cpp instructions/stacks/swap.h instructions/conversions/conversion.cpp instructions/conversions/conversion.h instructions/comparisons/comparison.cpp instructions/comparisons/comparison.h instructions/math/arithmetic.cpp instructions/math/arithmetic.h instructions/control/goto.cpp instructions/control/goto.h core/interpreter.cpp core/interpreter.h instructions/factory.cpp instructions/factory.h heap/class.cpp heap/class.h heap/accessFlags.cpp heap/accessFlags.h parser/classFile.cpp parser/classFile.h heap/rtConsts.cpp heap/rtConsts.h heap/classLoader.cpp heap/classLoader.h instructions/references/reference.cpp instructions/references/reference.h instructions/control/return.cpp instructions/control/return.h core/native.cpp core/native.h native/object.cpp native/object.h core/universe.cpp core/universe.h instructions/monitor/monitor.cpp instructions/monitor/monitor.h common/heapVector.cpp common/heapVector.h common/heapAllocator.cpp common/heapAllocator.h common/heapString.cpp common/heapString.h common/localArray.cpp common/localArray.h core/heapObject.cpp core/heapObject.h)
target_link_libraries(cpp_jvm stdc++fs)
