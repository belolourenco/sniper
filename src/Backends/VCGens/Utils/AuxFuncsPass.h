/**
 * AuxFuncsPass.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/23
 * @copyright : NII 2015
 */

#ifndef AUXFUNCSPASS_H
#define AUXFUNCSPASS_H

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"

using namespace llvm;

class AuxFuncsPass : public ModulePass {
  static char ID;

public:
  AuxFuncsPass():ModulePass(ID){};
  ~AuxFuncsPass(){};

  bool runOnModule(Module &M);

};

#endif