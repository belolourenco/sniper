/**
 * VCGen.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/27
 * @copyright : NII 2015
 */

#ifndef VCGEN_H
#define VCGEN_H

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Analysis/PostDominators.h"

#include "Utils/ListExpr.h"
#include "../../Encoder/Context.h"
#include "../../Encoder/Encoder.h"
#include "../../Logic/Expression.h"

class VCGenPass : public FunctionPass{
protected:
  static char ID;
  Context  *context;
  Function *assertF;
  Function *assumeF;
  Function *non_detF;
  Function *array_aux_1;
  Function *array_aux_2;
  Encoder  encoder;
  PostDominatorTree postDomTree;
  // List with the expressions to be sent to the solver
  ListExpr *solverExprs;
  bool hasRunnedOnFunction;
  int assertInContext;

  BasicBlock::iterator rmPhi(BasicBlock *b);

public:
  /*
  The auxFuncs array should contain the auxiliar functions in the following order:
    - void assert(int)
    - void assume(int)
    - int nondet_int(void)
    - void aux_array_1(int)
    - int aux_array_2(int)
  */
  explicit VCGenPass(Context *_ctx, const std::array<Function *,5> &auxFuncs, int _assertInContext);
  ~VCGenPass();

  Context *getContext();
  Function *getAssertFunc();
  Function *getAssumeFunc();

  ExprPtr encodeArray(AllocaInst *alloca);
  ExprPtr encodeArray(StoreInst *store);
  ExprPtr encodeArray(LoadInst *load);
  ExprPtr encodeArray(GetElementPtrInst *gep);

  // Be aware that if the returned ListExpr is a data member,
  // it will be possible to update that data member from the outside.
  // Moreover, this object cannot be destructed while that data member
  // is in use.
  virtual ListExpr *getPropertiesForSolver() = 0;
  virtual bool runOnFunction(Function &f) = 0;
  virtual void printInfo(raw_ostream &OS) = 0;
  virtual void print_(raw_ostream &OS) = 0;
  virtual unsigned sizeE() = 0;
  virtual unsigned sizeP() = 0;
};

#endif