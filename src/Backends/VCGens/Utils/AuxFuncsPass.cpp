/**
 * AuxFuncsPass.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/23
 * @copyright : NII 2015
 */

#include "AuxFuncsPass.h"

char AuxFuncsPass::ID = 0;

bool AuxFuncsPass::runOnModule(Module &M){
  Type *int32ty = Type::getInt32Ty(M.getContext());
  Type *voidty = Type::getVoidTy(M.getContext());

  M.getOrInsertFunction("assert", voidty, int32ty, NULL);
  M.getOrInsertFunction("assume", voidty, int32ty, NULL);
  M.getOrInsertFunction("nondet_int", AttributeSet(), int32ty, NULL);
  M.getOrInsertFunction("ARRAY_AUX_1", voidty, int32ty, NULL);
  M.getOrInsertFunction("ARRAY_AUX_2", int32ty, int32ty, NULL);

  return true;
}