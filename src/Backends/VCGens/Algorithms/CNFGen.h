/**
 * CNFGen.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/28
 * @copyright : NII 2015
 */

#ifndef CNFGEN_H
#define CNFGEN_H

#include "../../../Logic/Expression.h"
#include "../../../Logic/ExprUtils.h"
#include "../VCGenPass.h"
#include "../Utils/ListExpr.h"

// This class abstract 



// This VCGen captures the all the CNF and SSA algorithms from the
// following cube 
//
//          Lin(G).........SP(G)............CNF(G)..........SSA(G)
//         .   .          .   .             .   .            . .
//       .     .        .     .           .     .          .   .
//     .       .      .       .         .       .        .     .
//   .         .    .         .       .         .      .       .
// Lin(G+A)......SP(G+A).........CNF(G+A)..........SSA(G+A)    . 
//   .         .    .         .       .         .     .        .
//   .      Lin(P). .  . .  SP(P) . .  . . . CNF(P) .  . . . SSA(P)
//   .       .      .       .         .       .       .       .
//   .     .        .     .           .     .         .     .
//   .   .          .   .             .   .           .   .
//   . .            . .               . .             . .
//   .              .                 .               .
// Lin(P+A)......SP(P+A)..........CNF(P+A)..........SSA(P+A)
class CNFGen : public VCGenPass{

protected:
  ExprPtr opEncoding; //Operational Encoding
  ListExpr *vcs;       //Set of verification conditions
  bool piInAssign;

public:                           // Function *assertF, Function *assumeF, Function *non_detF,
  explicit CNFGen(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _piInAssign);
  ~CNFGen();

  virtual ListExpr *getPropertiesForSolver() = 0;
  virtual bool runOnFunction(Function &f);
  virtual void printInfo(raw_ostream &OS);
  virtual void print_(raw_ostream &OS);
  virtual unsigned sizeE();
  virtual unsigned sizeP();

    /*
  Methods for encoding the llvm program. Those are going to be applied recursively
  to each llvm instruction.
  */
  BinaryExprPtr   encodeInst(BasicBlock *p, std::vector<BasicBlock *> &pcds, const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, BasicBlock::iterator it);
  BinaryExprPtr   encodeBr  (std::vector<BasicBlock*> &pcds, const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, BranchInst *br);
  virtual ExprPtr encodeAnn(const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, CallInst *call) = 0;

};

class CNFPartial : public CNFGen{
public:                                 // Function *assertF, Function *assumeF, Function *non_detF,
  explicit CNFPartial(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _piInAssign);
  ExprPtr encodeAnn(const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

class CNFPartialAssert : public CNFGen{
public:                                     // Function *assertF, Function *assumeF, Function *non_detF,
  explicit CNFPartialAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _piInAssign);
  ExprPtr encodeAnn(const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};


class CNFGlobal : public CNFGen{
public:                              // Function *assertF, Function *assumeF, Function *non_detF,
  explicit CNFGlobal(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _piInAssign);
  ExprPtr encodeAnn(const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

class CNFGlobalAssert : public CNFGen{
public:                                    // Function *assertF, Function *assumeF, Function *non_detF,
  explicit CNFGlobalAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _piInAssign);
  ExprPtr encodeAnn(const ExprPtr pi, const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

#endif