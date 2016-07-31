/**
 * VarsForArrays.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/01/06
 * @copyright : NII 2015
 */

#ifndef VARSFORARRAYS_H
#define VARSFORARRAYS_H

#include <iostream>
#include <map>
#include <set>
#include <assert.h>

#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Transforms/Scalar.h>
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

/*
This pass is used to insert auxiliary variables to be used when encoding
arrays. The result is that 
  - before each AllocaInst it is added a call instruction to function
    array_aux_2 whose name is an identifier for the initial array.
  - before each GetElementPtrInst (if there is a LOAD instruction after it) a
    call to the array_aux_1 function is added - the identifier for the
    previous array
  - before each GetElementPtrInst (if there is a STORE instruction after it)
    a call to the array_aux_2 function is added - it will have as name the
    identifier for the new array and as parameter the identifier for the previous
    array
*/
class VarsForArrays : public FunctionPass {
  static char ID;

private:
  Function *array_aux_1;
  Function *array_aux_2;
  Type *int32_type;
  Constant *const0;
  std::map<AllocaInst *, Instruction *> vars;
  std::vector<Instruction*> createdCalls;
  std::set<Value*> &allArrayVars;

  void processGetElementInstr(Function &f, BasicBlock *b, GetElementPtrInst *getInstr);
  void processAlloca(Function &f, BasicBlock *b, AllocaInst *alloca);
  void varsInPhi(PHINode *phi);

public:
  // _allArrayVars will contain all the values, whose names are going to be used to identify arrays
  VarsForArrays(Function *_array_aux_1, Function *_array_aux_2, std::set<Value*> &_allArrayVars);
  ~VarsForArrays();
  virtual bool runOnFunction(Function &f);

};

#endif