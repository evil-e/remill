/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef MCSEMA_ARCH_X86_TRANSLATOR_H_
#define MCSEMA_ARCH_X86_TRANSLATOR_H_

#include <string>
#include <vector>

#include "mcsema/Arch/X86/XED.h"

namespace llvm {
class Context;
class Function;
class Type;
}  // namespace llvm

namespace mcsema {
namespace cfg {
class Instr;
}  // namespace cfg

class Translator;

namespace x86 {

class X86Arch;
class RegisterAnalysis;

// Convenience class that lets us keep all the instruction-specific state
// in on spot. This is more like a bag of sort of disorganized state that is
// needed to lift XED operands into LLVM.
class InstructionTranslator {
 public:
  InstructionTranslator(RegisterAnalysis &analysis_,
                        const cfg::Block &block_,
                        const cfg::Instr &instr_,
                        const struct xed_decoded_inst_s &xedd_);

  void LiftIntoBlock(const Translator &lifter, llvm::BasicBlock *B_);

 private:
  void LiftPC(uintptr_t next_pc);
  llvm::Value *ReadPC(llvm::BasicBlock *block);
  void LiftGeneric(const Translator &lifter);
  llvm::Function *GetInstructionFunction(void);
  bool CheckArgumentTypes(const llvm::Function *F,
                          const std::string &func_name);
  void LiftConditionalBranch(const Translator &lifter);
  void LiftOperand(const Translator &lifter, unsigned op_num);
  void LiftMemory(const Translator &lifter, const xed_operand_t *xedo,
                  unsigned op_num);
  void LiftImmediate(xed_operand_enum_t op_name);
  void LiftRegister(const xed_operand_t *xedo);
  void LiftBranchDisplacement(void);

  void AddTerminatingKills(const Translator &lifter,
                           const BasicBlockRegs *regs,
                           llvm::BasicBlock *B);

  bool IsBranch(void) const;

  bool IsFunctionCall(void) const;
  bool IsFunctionReturn(void) const;

  bool IsDirectFunctionCall(void) const;
  bool IsIndirectFunctionCall(void) const;

  bool IsJump(void) const;
  bool IsDirectJump(void) const;
  bool IsIndirectJump(void) const;

  bool IsSystemCall(void) const;
  bool IsSystemReturn(void) const;

  bool IsInterruptCall(void) const;
  bool IsInterruptReturn(void) const;

  bool IsNoOp(void) const;
  bool IsError(void) const;

  uintptr_t NextPC(void) const;
  uintptr_t TargetPC(void) const;

  RegisterAnalysis * const analysis;

  const cfg::Block *block;
  const cfg::Instr *instr;

  const xed_decoded_inst_t * const xedd;
  const xed_inst_t * const xedi;
  const xed_iclass_enum_t iclass;

  llvm::BasicBlock *B;
  llvm::Function *F;
  llvm::Module *M;
  llvm::LLVMContext *C;

  std::vector<llvm::Value *> args;
  std::vector<llvm::Instruction *> prepend_instrs;
  std::vector<llvm::Instruction *> append_instrs;
};

}  // namespace x86
}  // namespace mcsema

#endif  // MCSEMA_ARCH_X86_TRANSLATOR_H_
