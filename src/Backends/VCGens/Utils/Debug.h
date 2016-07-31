/**
 * Debug.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/20
 * @copyright : NII 2015
 */


#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>

#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

class Debug{

private:
  Module *llvmMod;
  std::string targetF;

public:
  Debug(Module *_llvmMod, std::string _targetF);
  ~Debug(){};
  void output(std::string index);
  void toCFG(std::string index);
};

#endif