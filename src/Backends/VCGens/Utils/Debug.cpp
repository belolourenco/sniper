/**
 * Debug.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/20
 * @copyright : NII 2015
 */

#include "Debug.h"

Debug::Debug(Module *_llvmMod, std::string _targetF){
  llvmMod = _llvmMod;
  targetF = _targetF; 
}

void Debug::output(std::string index){
  std::string error;
  std::string outputfile;
  outputfile = "./debug/" + index + ".ll";

  raw_ostream *ostream = new raw_fd_ostream(outputfile.c_str(),error);
  if(!error.empty()){
    std::cout << "Folder debug must be created!\n";
    std::cout << error.c_str() << std::endl;
    exit(0);
  }
  llvmMod->print(*ostream, NULL);
}

void Debug::toCFG(std::string index){
  std::string cmd = "opt -dot-cfg ./debug/" + index + ".ll";
  std::string cmd2 = "dot -Tpng cfg."+ targetF +".dot -o ./debug/" + index + ".png";
  std::cout << cmd << std::endl;
  system(cmd.c_str());
  std::cout << cmd2 << std::endl;
  system(cmd2.c_str());
}