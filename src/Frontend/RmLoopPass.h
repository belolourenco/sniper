/**
 * RmLoopPass.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/03/31
 * @copyright : NII 2015
 */

#ifndef RmLoopPass_H
#define RmLoopPass_H

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <assert.h>

#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

class RmLoopPass : public LoopPass {
  static char ID;

private:
  Function *function;
  bool unreachable; // Sets whether an unreachable instruction or branch instruction 
                    // is inserted after the assert(0) or assume(0)
  std::vector<BasicBlock *> createdBB;

public:
  // Receives a function which will be inserted after the unwound loop
  // The received function should be the assert or assume function
  // The unreachable parameter if set to true will originate an unreachable instruction 
  // after the assert(0) or assume(0) statement - if set to false, a new unconditional 
  // br instruction to the basic block immediately after the loop is inserted.
  RmLoopPass(Function *inst_function, bool _unreachable)
  :LoopPass(ID),function(inst_function), unreachable(_unreachable),createdBB(std::vector<BasicBlock *>()){};
  ~RmLoopPass() {};
  bool runOnLoop(Loop *L, LPPassManager &LPM);

};

#endif