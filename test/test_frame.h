//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM_TEST_FRAME_H
#define CPP_JVM_TEST_FRAME_H

#include "iostream"
#include "core/frame.h"

#define SetInt set_int
#define SetLong set_long
#define SetFloat set_float
#define SetDouble set_double
#define SetRef set_ref
#define nil nullptr
#define println std::cout <<
#define GetInt get_int
#define GetLong get_long
#define GetFloat get_float
#define GetDouble get_double
#define GetRef get_ref

#define PushInt push_int
#define PushLong push_long
#define PushFloat push_float
#define PushDouble push_double
#define PushRef push_ref
#define PopInt pop_int
#define PopFloat pop_float
#define PopDouble pop_double
#define PopLong pop_long
#define PopRef pop_ref

void test_locals() {
    auto frame = new Frame(100, 100);
    auto vars = *(frame->local_vars);
    auto op_stack = frame->operation_stack;
    vars.SetInt(0, 100);
    vars.SetInt(1, -100);
    vars.SetLong(2, 2997924580);
    vars.SetLong(4, -2997924580);
    vars.SetFloat(6, 3.1415926);
    vars.SetDouble(7, 2.71828182845);
    vars.SetRef(9, nil);
    println(vars.GetInt(0)) << std::endl;
    println(vars.GetInt(1)) << std::endl;
    println(vars.GetLong(2)) << std::endl;
    println(vars.GetLong(4)) << std::endl;
    println(vars.GetFloat(6)) << std::endl;
    println(vars.GetDouble(7)) << std::endl;
    println(vars.GetRef(9)) << std::endl;
}

void test_operation(){
    auto frame = new Frame(100, 100);
    auto ops = *(frame->operation_stack);
    ops.PushInt(100);
    ops.PushInt(-100);
    ops.PushLong(2997924580);
    ops.PushLong(-2997924580);
    ops.PushFloat(3.1415926);
    ops.PushDouble(2.71828182845);
    ops.PushRef(nil);
    println(ops.PopRef()) << std::endl;
    println(ops.PopDouble()) << std::endl;
    println(ops.PopFloat()) << std::endl;
    println(ops.PopLong()) << std::endl;
    println(ops.PopLong()) << std::endl;
    println(ops.PopInt()) << std::endl;
    println(ops.PopInt()) << std::endl;
}

#endif //CPP_JVM_TEST_FRAME_H
