/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

TEST_BEGIN(XADDr8r8, 2)
TEST_INPUTS(
    0, 0,
    1, 0,
    0xFF, 1,
    0x7F, 1,
    0x7F, 0xFF,
    0xFF, 0xFF)

    mov ebx, ARG1_32
    mov eax, ARG2_32
    xadd bl, al
TEST_END

TEST_BEGIN_64(XADDr8r8_64, 1)
TEST_INPUTS(
    0, 0,
    1, 0,
    0xFF, 1,
    0x7F, 1,
    0x7F, 0xFF,
    0xFF, 0xFF)

    xadd ARG1_8, ARG2_8
TEST_END_64

TEST_BEGIN(XADDr16r16, 2)
TEST_INPUTS(
    0, 0,
    1, 0,
    0xFF, 1,
    0x7F, 1,
    0x7F, 0xFF,
    0xFF, 0xFF,
    0x7FFF, 1,
    0x7FFF, 0xFFFF,
    0xFFFF, 0xFFFF)

    xadd ARG1_16, ARG2_16
TEST_END

TEST_BEGIN(XADDr32r32, 2)
TEST_INPUTS(
    0, 0, /* ZF */
    1, 0,
    0xFFFFFFFF, 1, /* OF, CF */
    0xFFFFFFFF, 0xFFFFFFFF, /* OF */
    0x7FFFFFFF, 1, /* SF */
    0, 0x10, /* AF */
    0x7F, 0x10 /* PF */)

    xadd ARG1_32, ARG2_32
TEST_END

TEST_BEGIN_64(XADDr64r64_64, 2)
TEST_INPUTS(
    0, 0, /* ZF */
    1, 0,
    0xFFFFFFFF, 1, /* OF, CF */
    0xFFFFFFFF, 0xFFFFFFFF, /* OF */
    0x7FFFFFFF, 1, /* SF */
    0, 0x10, /* AF */
    0x7F, 0x10, /* PF */
    0x7FFFFFFFFFFFFFFF, 1,
    0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF,
    0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
    0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)

    xadd ARG1_64, ARG2_64
TEST_END_64
