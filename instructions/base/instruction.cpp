//
// Created by chaomaer on 2023/1/31.
//

#include "instruction.h"
#include "iostream"

void invoke_method(Frame* invoker_frame, Method* method) {
    if (method->is_native()) {
        return;
    }
    auto t = invoker_frame->thread;
    auto new_frame = t->new_frame(method);
    t->push_frame(new_frame);
    auto arg_slot = method->arg_slot_number;
    for (int i = arg_slot-1; i>=0; i--) {
        new_frame->local_vars->set_slot(i, invoker_frame->operation_stack->pop_slot());
    }
}

void Index8Instruction::fetch_operands(BytecodeReader *reader) {
    index = reader->read_uint8();
}

void Index16Instruction::fetch_operands(BytecodeReader *reader) {
    index = reader->read_uint16();
}

void BranchInstruction::fetch_operands(BytecodeReader *reader) {
    offset = reader->read_uint16();
}

void BytecodeReader::reset(uint8 *code, int pc) {
    this->code = code;
    this->pc = pc;
}

uint8 BytecodeReader::read_uint8() {
    int idx = pc++;
    return code[idx];
}

uint16 BytecodeReader::read_uint16() {
    uint16 u1 = (uint16)read_uint8();
    uint16 u2 = (uint16)read_uint8();
    return u1 << 8 | u2;
}

uint32 BytecodeReader::read_uint32() {
    uint32 u1 = (uint32)read_uint16();
    uint32 u2 = (uint32)read_uint16();
    return u1 << 16 | u2;
}

uint64 BytecodeReader::read_uint64() {
    uint64 u1 = (uint64)read_uint32();
    uint32 u2 = (uint64)read_uint32();
    return u1 << 32 | u2;
}

BytecodeReader::BytecodeReader(uint8 *code): code(code) {
}

BytecodeReader::BytecodeReader() {
}

void BytecodeReader::reset_cp(int pc) {
    this->pc = pc;
}
