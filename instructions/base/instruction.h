//
// Created by chaomaer on 2023/1/31.
//

#ifndef CPP_JVM2_INSTRUCTION_H
#define CPP_JVM2_INSTRUCTION_H
#include "core/frame.h"
#include "common/type.h"

class BytecodeReader {
public:
    uint8* code;
    int pc;
public:
    BytecodeReader(uint8* code);
    BytecodeReader();
    void reset_cp(int pc);
    void reset(uint8* code, int pc);
    uint8 read_uint8();
    uint16 read_uint16();
    uint32 read_uint32();
    uint64 read_uint64();
};

void invoke_method(Frame* frame, Method* method);

class Instruction {
public:
    virtual void fetch_operands(BytecodeReader* reader) {}
    virtual void execute(Frame* frame) {}
    virtual ~Instruction() = default;
};

class NoOperandsInstruction : public Instruction {

};

class BranchInstruction : public Instruction {
public:
    short offset;
    void fetch_operands(BytecodeReader* reader);
};

class Index8Instruction : public Instruction {
public:
    unsigned int index;
    void fetch_operands(BytecodeReader* reader);
};

class Index16Instruction : public Instruction {
public:
    unsigned int index;
    void fetch_operands(BytecodeReader* reader);
};


#endif //CPP_JVM2_INSTRUCTION_H
