/**
 * VCGenFrontend.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/20
 * @copyright : NII 2015
 */

#ifndef VCGENFRONTEND_H
#define VCGENFRONTEND_H

#include <iostream>

#include <llvm/Pass.h>
#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/Signals.h>
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"

#include "../../Options.h"
#include "../../Frontend/LocalVariables.h"
#include "../../Frontend/GlobalVariables.h"
#include "../../Frontend/LoopInfoPass.h"
#include "../../Frontend/RmLoopPass.h"
#include "../../Frontend/VarsForArrays.h"
#include "../../Encoder/Context.h"
#include "Utils/Debug.h"
#include "Utils/AuxFuncsPass.h"
#include "VCGenPass.h"
#include "SolveVCs.h"
#include "Algorithms/SEPass.h"
#include "Algorithms/CNFGen.h"
#include "Algorithms/SPGen.h"
#include "Algorithms/LinGen.h"

using namespace llvm;

class VCGenFrontend{

private:
  Module *llvmMod;
  Options *opts;
  Debug *debug;
  raw_ostream *OS;
  Function *targetF;
  Function *assertF;
  Function *assumeF;
  Function *nondetF;
  Function *arrayAux1;
  Function *arrayAux2;
  Context *ctx;
  long cycl_comp;
  VCGenPass *vcgen;
  std::string vcgenName;
  std::set<Value*> allArrayVars;

public:
  VCGenFrontend(Options *_opts, raw_ostream *_OS);
  ~VCGenFrontend(){};
  void init(char *prog_name);
  void launch();
  void finish();

private:
  void cyclomatic_complexity();
  void executeBench(Context *ctx);
  void listVCGens();
  void chooseVCGen(int assertInCtx);
  void processFunctionReturns(Function *f);
  void checkFunctionSignature(Function *targetF);
  bool isStandardFunctionSignature(Function *targetF);

};

#endif