/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_ARCH_X86_SEMANTICS_COND_BR_H_
#define REMILL_ARCH_X86_SEMANTICS_COND_BR_H_

namespace {

// TODO(pag): Evaluate branch-free variants. Things to evaluate:
//            - Do branch-free BRANCH_TAKENitionals lead to better native code
//              generation?
//            - Do branch-free BRANCH_TAKENitionals lead to better flag lifetime
//              analysis.
//            - Do branch-free BRANCH_TAKENitionals make it easier or harder to
//              reason about the path BRANCH_TAKENition using an SMT solver (e.g.
//              XOR operations might make things harder rather than easier).
//
// TODO(pag): - Add in an BRANCH_TAKENitional branch intrinsic, e.g.
//                  W(state.gpr.rip) = __remill_BRANCH_TAKENitional_branch(a, b, c);
//              The goal here would be to informa a concolic/symbolic executor
//              about the difference between a BRANCH_TAKENitional branch within the
//              lifted program and the program itself.

DEF_SEM(JNLE, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BAnd(BNot(FLAG_ZF), BXnor(FLAG_SF, FLAG_OF));
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNS, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(FLAG_SF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JL, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BXor(FLAG_SF, FLAG_OF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNP, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(FLAG_PF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNZ, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(FLAG_ZF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNB, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(FLAG_CF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNO, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(FLAG_OF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNL, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BXnor(FLAG_SF, FLAG_OF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JNBE, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BNot(BOr(FLAG_CF, FLAG_ZF));
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JBE, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BOr(FLAG_CF, FLAG_ZF);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JZ, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = FLAG_ZF;
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JP, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = FLAG_PF;
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JS, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = FLAG_SF;
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JO, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = FLAG_OF;
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JB, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = FLAG_CF;
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_SEM(JLE, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = BOr(FLAG_ZF, BXor(FLAG_SF, FLAG_OF));
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

} // namespace

DEF_ISEL(JNLE_RELBRb) = JNLE;
DEF_ISEL(JNLE_RELBRz_8) = JNLE;
DEF_ISEL(JNLE_RELBRz_16) = JNLE;
DEF_ISEL(JNLE_RELBRz_32) = JNLE;
IF_64BIT(DEF_ISEL(JNLE_RELBRz_64) = JNLE;)
DEF_ISEL(JNLE_RELBRd) = JNLE;

DEF_ISEL(JNS_RELBRb) = JNS;
DEF_ISEL(JNS_RELBRz_8) = JNS;
DEF_ISEL(JNS_RELBRz_16) = JNS;
DEF_ISEL(JNS_RELBRz_32) = JNS;
IF_64BIT(DEF_ISEL(JNS_RELBRz_64) = JNS;)
DEF_ISEL(JNS_RELBRd) = JNS;

DEF_ISEL(JL_RELBRb) = JL;
DEF_ISEL(JL_RELBRz_8) = JL;
DEF_ISEL(JL_RELBRz_16) = JL;
DEF_ISEL(JL_RELBRz_32) = JL;
IF_64BIT(DEF_ISEL(JL_RELBRz_64) = JL;)
DEF_ISEL(JL_RELBRd) = JL;

DEF_ISEL(JNP_RELBRb) = JNP;
DEF_ISEL(JNP_RELBRz_8) = JNP;
DEF_ISEL(JNP_RELBRz_16) = JNP;
DEF_ISEL(JNP_RELBRz_32) = JNP;
IF_64BIT(DEF_ISEL(JNP_RELBRz_64) = JNP;)
DEF_ISEL(JNP_RELBRd) = JNP;

DEF_ISEL(JNZ_RELBRb) = JNZ;
DEF_ISEL(JNZ_RELBRz_8) = JNZ;
DEF_ISEL(JNZ_RELBRz_16) = JNZ;
DEF_ISEL(JNZ_RELBRz_32) = JNZ;
IF_64BIT(DEF_ISEL(JNZ_RELBRz_64) = JNZ;)
DEF_ISEL(JNZ_RELBRd) = JNZ;

DEF_ISEL(JNB_RELBRb) = JNB;
DEF_ISEL(JNB_RELBRz_8) = JNB;
DEF_ISEL(JNB_RELBRz_16) = JNB;
DEF_ISEL(JNB_RELBRz_32) = JNB;
IF_64BIT(DEF_ISEL(JNB_RELBRz_64) = JNB;)
DEF_ISEL(JNB_RELBRd) = JNB;

DEF_ISEL(JNO_RELBRb) = JNO;
DEF_ISEL(JNO_RELBRz_8) = JNO;
DEF_ISEL(JNO_RELBRz_16) = JNO;
DEF_ISEL(JNO_RELBRz_32) = JNO;
IF_64BIT(DEF_ISEL(JNO_RELBRz_64) = JNO;)
DEF_ISEL(JNO_RELBRd) = JNO;

DEF_ISEL(JNL_RELBRb) = JNL;
DEF_ISEL(JNL_RELBRz_8) = JNL;
DEF_ISEL(JNL_RELBRz_16) = JNL;
DEF_ISEL(JNL_RELBRz_32) = JNL;
IF_64BIT(DEF_ISEL(JNL_RELBRz_64) = JNL;)
DEF_ISEL(JNL_RELBRd) = JNL;

DEF_ISEL(JNBE_RELBRb) = JNBE;
DEF_ISEL(JNBE_RELBRz_8) = JNBE;
DEF_ISEL(JNBE_RELBRz_16) = JNBE;
DEF_ISEL(JNBE_RELBRz_32) = JNBE;
IF_64BIT(DEF_ISEL(JNBE_RELBRz_64) = JNBE;)
DEF_ISEL(JNBE_RELBRd) = JNBE;

DEF_ISEL(JBE_RELBRb) = JBE;
DEF_ISEL(JBE_RELBRz_8) = JBE;
DEF_ISEL(JBE_RELBRz_16) = JBE;
DEF_ISEL(JBE_RELBRz_32) = JBE;
IF_64BIT(DEF_ISEL(JBE_RELBRz_64) = JBE;)
DEF_ISEL(JBE_RELBRd) = JBE;

DEF_ISEL(JZ_RELBRb) = JZ;
DEF_ISEL(JZ_RELBRz_8) = JZ;
DEF_ISEL(JZ_RELBRz_16) = JZ;
DEF_ISEL(JZ_RELBRz_32) = JZ;
IF_64BIT(DEF_ISEL(JZ_RELBRz_64) = JZ;)
DEF_ISEL(JZ_RELBRd) = JZ;

DEF_ISEL(JP_RELBRb) = JP;
DEF_ISEL(JP_RELBRz_8) = JP;
DEF_ISEL(JP_RELBRz_16) = JP;
DEF_ISEL(JP_RELBRz_32) = JP;
IF_64BIT(DEF_ISEL(JP_RELBRz_64) = JP;)
DEF_ISEL(JP_RELBRd) = JP;

DEF_ISEL(JS_RELBRb) = JS;
DEF_ISEL(JS_RELBRz_8) = JS;
DEF_ISEL(JS_RELBRz_16) = JS;
DEF_ISEL(JS_RELBRz_32) = JS;
IF_64BIT(DEF_ISEL(JS_RELBRz_64) = JS;)
DEF_ISEL(JS_RELBRd) = JS;

DEF_ISEL(JO_RELBRb) = JO;
DEF_ISEL(JO_RELBRz_8) = JO;
DEF_ISEL(JO_RELBRz_16) = JO;
DEF_ISEL(JO_RELBRz_32) = JO;
IF_64BIT(DEF_ISEL(JO_RELBRz_64) = JO;)
DEF_ISEL(JO_RELBRd) = JO;

DEF_ISEL(JB_RELBRb) = JB;
DEF_ISEL(JB_RELBRz_8) = JB;
DEF_ISEL(JB_RELBRz_16) = JB;
DEF_ISEL(JB_RELBRz_32) = JB;
IF_64BIT(DEF_ISEL(JB_RELBRz_64) = JB;)
DEF_ISEL(JB_RELBRd) = JB;

DEF_ISEL(JLE_RELBRb) = JLE;
DEF_ISEL(JLE_RELBRz_8) = JLE;
DEF_ISEL(JLE_RELBRz_16) = JLE;
DEF_ISEL(JLE_RELBRz_32) = JLE;
IF_64BIT(DEF_ISEL(JLE_RELBRz_64) = JLE;)
DEF_ISEL(JLE_RELBRd) = JLE;

DEF_ISEL_SEM(JCXZ_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = UCmpEq(REG_CX, 0_u16);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_ISEL_SEM(JECXZ_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = UCmpEq(REG_ECX, 0_u32);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_ISEL_SEM(JRCXZ_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  auto take_branch = UCmpEq(REG_RCX, 0_u64);
  Write(cond, take_branch);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_ISEL_SEM(LOOP_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  addr_t count = USub(REG_XCX, addr_t(1));
  auto take_branch = UCmpNeq(count, addr_t(0));
  Write(cond, take_branch);
  Write(REG_XCX, count);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_ISEL_SEM(LOOPE_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  addr_t count = USub(REG_XCX, addr_t(1));
  auto take_branch = BAnd(UCmpNeq(count, addr_t(0)), FLAG_ZF);
  Write(cond, take_branch);
  Write(REG_XCX, count);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

DEF_ISEL_SEM(LOOPNE_RELBRb, R8W cond, PC taken_pc, PC not_taken_pc) {
  addr_t count = USub(REG_XCX, addr_t(1));
  auto take_branch = BAnd(UCmpNeq(count, addr_t(0)), BNot(FLAG_ZF));
  Write(cond, take_branch);
  Write(REG_XCX, count);
  Write(REG_PC, Select<addr_t>(take_branch, taken_pc, not_taken_pc));
}

/*
522 XEND XEND COND_BR RTM RTM ATTRIBUTES:

1465 XBEGIN XBEGIN_RELBRz COND_BR RTM RTM ATTRIBUTES: SCALABLE
 */

#endif  // REMILL_ARCH_X86_SEMANTICS_COND_BR_H_
