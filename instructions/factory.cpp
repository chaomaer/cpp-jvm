//
// Created by chaomaer on 2023/2/1.
//

#include "factory.h"
#include "instructions/constants/constant.h"
#include "instructions/stores/store.h"
#include "instructions/loads/load.h"
#include "instructions/math/arithmetic.h"
#include "instructions/control/goto.h"
#include "instructions/comparisons/comparison.h"

Instruction *InstructionFactory::new_instruction(int op_code) {
    switch (op_code) {
        case 0x03:
            return new I_CONST_0();
        case 0x04:
            return new I_CONST_1();
        case 0x10:
            return new B_I_PUSH();
        case 0x1b:
            return new I_LOAD_1();
        case 0x1c:
            return new I_LOAD_2();
        case 0x3c:
            return new I_STORE_1();
        case 0x3d:
            return new I_STORE_2();
        case 0x60:
            return new I_ADD();
        case 0x84:
            return new I_INC();
        case 0xa3:
            return new IF_I_CMP_GT();
        case 0xa7:
            return new GOTO();
        default:
            printf("op_code : %x is not supported\n", op_code);
            exit(0);
    }
}
