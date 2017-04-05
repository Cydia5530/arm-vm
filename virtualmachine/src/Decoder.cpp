//
//  Decoder.cpp
//  virtualmachine
//
//  Created by Jem Tucker on 17/10/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Decoder.h"

/**
 *
 * Structure of bits
 *
 *   3                   2                   1                   0
 * 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  cond  |   |i|op_code|s| reg_n | reg_d |        operand_2
 *
 */
namespace vm {

DecodedOperation Decoder::decode(uint32_t instr) {
    DecodedOperation op;
    
    op.cond = (instr & 0xF0000000) >> 28;
    
    op.i = (instr >> 25) & 1;
    op.s = (instr >> 20) & 1;
    
    op.code  = (instr >> 21) & 0xF;
    op.reg_d = (instr >> 12) & 0xF;
    op.reg_n = (instr >> 16) & 0xF;
    
    if (op.i) {
        op.imm_val = instr & 0x000000FF;
        op.imm_rot = instr & 0x00000F00;
    } else {
        op.reg_m = instr & 0x0000000F;
        op.reg_s = instr & 0x00000FF0;
    }
    
    return op;
}
    
} // namespace vm