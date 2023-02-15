//
// Created by chaomaer on 2023/2/9.
//

#ifndef CPP_JVM2_REFERENCE_H
#define CPP_JVM2_REFERENCE_H
#include "instructions/base/instruction.h"

Class* get_primitive_array_class(ClassLoader *pLoader, unsigned int type);

class NEW : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class PUT_STATIC : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class GET_STATIC : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class PUT_FIELD : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class GET_FIELD : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class IS_INSTANCE_OF : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class CHECK_CAST : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class INVOKE_STATIC : public Index16Instruction {
public:
    void execute(Frame* frame);
};

//https://stackoverflow.com/questions/13764238/why-invokespecial-is-needed-when-invokevirtual-exists
class INVOKE_SPECIAL : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class INVOKE_VIRTUAL : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class INVOKE_INTERFACE : public Instruction {
public:
    int index;
public:
    void fetch_operands(BytecodeReader* reader);
    void execute(Frame* frame);
};

class NEW_ARRAY : public Index8Instruction {
public:
    void execute(Frame* frame);
};

class A_NEW_ARRAY : public Index16Instruction {
public:
    void execute(Frame* frame);
};

class ARRAY_LENGTH : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_A_LOAD : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class C_A_LOAD : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_A_LOAD : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class A_A_STORE : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class C_A_STORE : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

class I_A_STORE : public NoOperandsInstruction {
public:
    void execute(Frame* frame);
};

#endif //CPP_JVM2_REFERENCE_H
