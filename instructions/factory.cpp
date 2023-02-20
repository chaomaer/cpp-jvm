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
#include "instructions/stacks/pop.h"
#include "instructions/control/return.h"

Instruction *InstructionFactory::new_instruction(int op_code) {
    switch (op_code) {
        case 0x01:
            return new A_CONST_NULL();
        case 0x03:
            return new I_CONST_0();
        case 0x04:
            return new I_CONST_1();
        case 0x05:
            return new I_CONST_2();
        case 0x06:
            return new I_CONST_3();
        case 0x07:
            return new I_CONST_4();
        case 0x08:
            return new I_CONST_5();
        case 0x10:
            return new B_I_PUSH();
        case 0x11:
            return new S_I_PUSH();
        case 0x12:
            return new LDC();
        case 0x14:
            return new LDC2_W();
        case 0x15:
            return new I_LOAD();
        case 0x19:
            return new A_LOAD();
        case 0x1a:
            return new I_LOAD_0();
        case 0x1b:
            return new I_LOAD_1();
        case 0x1c:
            return new I_LOAD_2();
        case 0x1d:
            return new I_LOAD_3();
        case 0x2a:
            return new A_LOAD_0();
        case 0x2b:
            return new A_LOAD_1();
        case 0x2c:
            return new A_LOAD_2();
        case 0x2d:
            return new A_LOAD_3();
        case 0x2e:
            return new I_A_LOAD();
        case 0x32:
            return new A_A_LOAD();
        case 0x34:
            return new C_A_LOAD();
        case 0x36:
            return new I_STORE();
        case 0x3a:
            return new A_STORE();
        case 0x3c:
            return new I_STORE_1();
        case 0x3d:
            return new I_STORE_2();
        case 0x3e:
            return new I_STORE_3();
        case 0x4c:
            return new A_STORE_1();
        case 0x4d:
            return new A_STORE_2();
        case 0x4e:
            return new A_STORE_3();
        case 0x4f:
            return new I_A_STORE();
        case 0x53:
            return new A_A_STORE();
        case 0x55:
            return new C_A_STORE();
        case 0x57:
            return new POP();
        case 0x59:
            return new DUP();
        case 0x60:
            return new I_ADD();
        case 0x64:
            return new I_SUB();
        case 0x84:
            return new I_INC();
        case 0x99:
            return new IF_EQ();
        case 0x9a:
            return new IF_NE();
        case 0xa2:
            return new IF_I_CMP_GE();
        case 0xa3:
            return new IF_I_CMP_GT();
        case 0xa4:
            return new IF_I_CMP_LE();
        case 0xa6:
            return new IF_A_CMP_NE();
        case 0xa7:
            return new GOTO();
        case 0xac:
            return new I_RETURN();
        case 0xb0:
            return new A_RETURN();
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
        case 0xb8:
            return new INVOKE_STATIC();
        case 0xb9:
            return new INVOKE_INTERFACE();
        case 0xbb:
            return new NEW();
        case 0xbc:
            return new NEW_ARRAY();
        case 0xbd:
            return new A_NEW_ARRAY();
        case 0xbe:
            return new ARRAY_LENGTH();
        case 0xc0:
            return new CHECK_CAST();
        case 0xc1:
            return new IS_INSTANCE_OF();
        case 0xc7:
            return new IF_NON_NULL();
        case 0xfe:
            return new INVOKE_NATIVE();
        default:
            printf("op_code : %x is not supported\n", op_code);
            exit(0);
    }
}
