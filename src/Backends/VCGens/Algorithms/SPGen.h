/**
 * SPGen.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/30
 * @copyright : NII 2015
 */


#ifndef SPGEN_H
#define SPGEN_H

#include "../../../Logic/Expression.h"
#include "../../../Logic/ExprUtils.h"
#include "../VCGenPass.h"
#include "../Utils/ListExpr.h"

// This class abstract 



// This VCGen captures the SP algorithm from the
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
class SPGen : public VCGenPass{

protected:
  ExprPtr opEncoding; //Operational Encoding
  ListExpr *vcs;       //Set of verification conditions

public:
  explicit SPGen(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx);
  ~SPGen();

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
  BinaryExprPtr   encodeInst(BasicBlock *p, std::vector<BasicBlock *> &pcds, const ExprPtr psi, const ExprPtr gamma, BasicBlock::iterator it);
  BinaryExprPtr   encodeBr  (std::vector<BasicBlock*> &pcds, const ExprPtr psi, const ExprPtr gamma, BranchInst *br);
  virtual ExprPtr encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call) = 0;

};

class SPPartial : public SPGen{
public:
  explicit SPPartial(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx);
  ExprPtr encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

class SPPartialAssert : public SPGen{
public:
  explicit SPPartialAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx);
  ExprPtr encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};


class SPGlobal : public SPGen{
public:
  explicit SPGlobal(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx);
  ExprPtr encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

class SPGlobalAssert : public SPGen{
public:
  explicit SPGlobalAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx);
  ExprPtr encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call);
  ListExpr *getPropertiesForSolver();
};

#endif