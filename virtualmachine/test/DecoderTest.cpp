//
//  DecoderTest.cpp
//  virtualmachine
//
//  Created by Jem Tucker on 17/10/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//


#include "gtest/gtest.h"
#include "Decoder.h"

class DecoderTest: public ::testing::Test {
protected:
    vm::Decoder decoder;
};

TEST_F(DecoderTest, ExtractsConditions) {
    vm::DecodedOperation op = decoder.decode(0x40000000);
    EXPECT_EQ(0x4, op.cond);
    
    op = decoder.decode(0x44dd4000);
    EXPECT_EQ(0x4, op.cond);
    
    op = decoder.decode(0xa0000000);
    EXPECT_EQ(0xa, op.cond);
    
    op = decoder.decode(0xab000000);
    EXPECT_EQ(0xa, op.cond);
    
    op = decoder.decode(0xf0000000);
    EXPECT_EQ(0xf, op.cond);
    
    op = decoder.decode(0x01111111);
    EXPECT_EQ(0x0, op.cond);
}

TEST_F(DecoderTest, ExtractsTheIFlag) {
    vm::DecodedOperation op = decoder.decode(0x02000000);
    EXPECT_EQ(0x1, op.i);
    
    op = decoder.decode(0x01000000);
    EXPECT_EQ(0x0, op.i);
}

TEST_F(DecoderTest, ExtractsTheSFlag) {
    vm::DecodedOperation op = decoder.decode(0x00100000);
    EXPECT_EQ(0x1, op.s);
    
    op = decoder.decode(0x00080000);
    EXPECT_EQ(0x0, op.s);
}

TEST_F(DecoderTest, ExtractsOperationCodes) {
    vm::DecodedOperation op = decoder.decode(0x02432001);
    EXPECT_EQ(0x2, op.code);
    
    op = decoder.decode(0x00632000);
    EXPECT_EQ(0x3, op.code);
    
    op = decoder.decode(0x01632000);
    EXPECT_EQ(0xB, op.code);
    
    op = decoder.decode(0x01E32000);
    EXPECT_EQ(0xF, op.code);
}

TEST_F(DecoderTest, ExtractsRn) {
    vm::DecodedOperation op = decoder.decode(0x00010000);
    EXPECT_EQ(0x1, op.reg_n);
    
    op = decoder.decode(0x000F0000);
    EXPECT_EQ(0xF, op.reg_n);
    
    op = decoder.decode(0x001F0000);
    EXPECT_EQ(0xF, op.reg_n);
}

TEST_F(DecoderTest, ExtractsRd) {
    vm::DecodedOperation op = decoder.decode(0x00001000);
    EXPECT_EQ(0x1, op.reg_d);
    
    op = decoder.decode(0x0000F000);
    EXPECT_EQ(0xF, op.reg_d);
    
    op = decoder.decode(0x0001F000);
    EXPECT_EQ(0xF, op.reg_d);
}

TEST_F(DecoderTest, ExtractsRmOnlyIfNotI) {
    vm::DecodedOperation op = decoder.decode(0x02000001);
    EXPECT_EQ(0x0, op.reg_m);
    
    op = decoder.decode(0x0110000F);
    EXPECT_EQ(0xF, op.reg_m);
    
    op = decoder.decode(0x02000001);
    EXPECT_EQ(0x0, op.reg_m);
}

TEST_F(DecoderTest, ExtractsImmOnlyIfNotI) {
    vm::DecodedOperation op = decoder.decode(0x02000001);
    EXPECT_EQ(0x1, op.imm_val);
    
    op = decoder.decode(0x0110000F);
    EXPECT_EQ(0x0, op.imm_val);
    
    op = decoder.decode(0x0200000F);
    EXPECT_EQ(0xF, op.imm_val);
}




