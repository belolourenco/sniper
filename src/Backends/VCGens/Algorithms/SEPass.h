/**
 * SEPass.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/20
 * @copyright : NII 2015
 */


#ifndef _SEVCGENPASS_H
#define _SEVCGENPASS_H

#include <utility>

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"

#include "../VCGenPass.h"
#include "../utils/ListExpr.h"
#include "../utils/PairListExpr.h"
#include "../../../Logic/Expression.h"

using namespace llvm;

/*
This function pass generates symbolic execution verification conditions.
After the pass is run, the set of executions representing the encoding of 
the program and the set of verification conditions can be retrieved through 
the method getEncoding()
*/
class SEPass : public VCGenPass{
private:
  PairListExpr vcs;

public:
  explicit SEPass(Context *context, const std::array<Function *,5> &auxFuncs, int assertInContext);
  ~SEPass();

  virtual ListExpr *getPropertiesForSolver();
  virtual bool runOnFunction(Function &f);
  virtual void printInfo(raw_ostream &OS);
  virtual void print_(raw_ostream &OS);
  virtual unsigned sizeE();
  virtual unsigned sizeP();

  /*
  Methods for encoding the llvm program. Those are going to be applied recursively
  to each llvm instruction.
  */
  void    encodeInst(BasicBlock *p, const ListExpr &psi, BasicBlock::iterator inst);
  void    encodeBr  (const ListExpr &psi, BranchInst *br);
  ExprPtr encodeAnn (const ListExpr &psi, CallInst *call);

};

#endif