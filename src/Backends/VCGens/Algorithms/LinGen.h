/**
 * LinGen.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/31
 * @copyright : NII 2015
 */


#ifndef LinGEN_H
#define LinGEN_H

#include "../../../Logic/Expression.h"
#include "../../../Logic/ExprUtils.h"
#include "../VCGenPass.h"
#include "../Utils/ListExpr.h"

// This class abstract 


// This VCGen captures the Linear SP algorithm from the
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
class LinGen : public VCGenPass{
private:
  bool globalCtx;

protected:
  ExprPtr opEncoding; //Operational Encoding
  ListExpr *vcs;       //Set of verification conditions

public:
  explicit LinGen(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _globalCtx);
  ~LinGen();

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
  TrinaryExprPtr   encodeInst(BasicBlock *p, std::vector<BasicBlock *> &pcds, BasicBlock::iterator it);
  TrinaryExprPtr   encodeBr  (std::vector<BasicBlock*> &pcds, BranchInst *br);
  virtual BinaryExprPtr encodeAnn(CallInst *call) = 0;

};

class Lin : public LinGen{
public:
  explicit Lin(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _globalCtx);
  BinaryExprPtr encodeAnn(CallInst *call);
};

class LinAssert : public LinGen{
public:
  explicit LinAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx, bool _globalCtx);
  BinaryExprPtr encodeAnn(CallInst *call);
};

#endif