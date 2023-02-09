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
#include "instructions/references/reference.h"
#include "instructions/stacks/dup.h"
#include "instructions/control/return.h"

Instruction *InstructionFactory::new_instruction(int op_code) {
    switch (op_code) {
        case 0x03:
            return new I_CONST_0();
        case 0x04:
            return new I_CONST_1();
        case 0x10:
            return new B_I_PUSH();
        case 0x12:
            return new IDC();
        case 0x1b:
            return new I_LOAD_1();
        case 0x1c:
            return new I_LOAD_2();
        case 0x2c:
            return new A_LOAD_2();
        case 0x2d:
            return new A_LOAD_3();
        case 0x3c:
            return new I_STORE_1();
        case 0x3d:
            return new I_STORE_2();
        case 0x4d:
            return new A_STORE_2();
        case 0x4e:
            return new A_STORE_3();
        case 0x59:
            return new DUP();
        case 0x60:
            return new I_ADD();
        case 0x84:
            return new I_INC();
        case 0x99:
            return new IF_EQ();
        case 0xa3:
            return new IF_I_CMP_GT();
        case 0xa7:
            return new GOTO();
        case 0xb1:
            return new RETURN();
        case 0xb2:
            return new GET_STATIC();
        case 0xb3:
            return new PUT_STATIC();
        case 0xb4:
            return new GET_FIELD();
        case 0xb5:
            return new PUT_FIELD();
        case 0xb6:
            return new INVOKE_VIRTUAL();
        case 0xb7:
            return new INVOKE_SPECIAL();
        case 0xbb:
            return new NEW();
        case 0xc0:
            return new CHECK_CAST();
        case 0xc1:
            return new IS_INSTANCE_OF();
        default:
            printf("op_code : %x is not supported\n", op_code);
            exit(0);
    }
}