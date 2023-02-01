//
// Created by chaomaer on 2023/2/1.
//

#include "goto.h"
#include "iostream"

void GOTO::execute(Frame *frame) {
    frame->branch(offset);
}
