/**
 * RmLoopPass.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/03/31
 * @copyright : NII 2015
 */

#include "RmLoopPass.h"

char RmLoopPass::ID = 0;

// Inserts an unwinding annotation (assume or assert, depending on the function
// given in the constructor) and removes the loop.
bool RmLoopPass::runOnLoop(Loop *L, LPPassManager &LPM){

  BasicBlock *latch  = L -> getLoopLatch();
  BasicBlock *header = L -> getHeader();
  SmallVector<BasicBlock *, 1> exitBBs;
  L -> getExitBlocks(exitBBs);
  BasicBlock *exitBB = NULL;
  SmallVector<BasicBlock *, 1>::iterator it = exitBBs.begin();
  for(; it != exitBBs.end() && !exitBB; ++it){
    if(std::find(createdBB.begin(), createdBB.end(), *it) == createdBB.end())
      exitBB = *it;
  }

  assert(exitBB && "exitBB is null");

  // std::cout << "\n\n LOOP REMOVAL:\n";
  // std::cout << "Latch: " << latch -> getName().str() << "\n";
  // std::cout << "Header: " << header -> getName().str() << "\n";
  // std::cout << "ExitBB: " << exitBB -> getName().str() << "\n";
  //assert(exitBBs.size() == 1 && "RmLoopPass - more than one exit BB");
  // At this point we have an header, a latch and an exit BasicBlock 
  // and they all are different
  assert(latch && header
        && "Not able to obtain some loop basic block; try to run doInitialization before");
  
  // Get loop last branch instruction
  BranchInst *br = cast<BranchInst>(latch -> getTerminator());
  // assert(br -> isConditional() && "loop terminator with unconditional branch");
  // Get loop's last iteration condition
  Value *cond = NULL;      // Loop last iteration branch condition
  if(br -> isConditional())
    cond = br -> getCondition();
  else{
    std::cout << "\n************************************************************\n";
    std::cout <<   "*BE CAREFUL!!!! There is a latch with unconditional branch!*\n";
    std::cout <<   "************************************************************\n";
  }

  // In order to remove the back edge, we need to remove the loop from the LPPAssManager
  LPM.deleteLoopFromQueue(L);

  // Create a new BasicBlock with the unwinding annotation.
  // Unreachable instruction is used as a terminator instruction in this BasicBlock
  BasicBlock *newBB = BasicBlock::Create(header -> getContext()
                                        , "unwinding_annotation"
                                        , header -> getParent());
  createdBB.push_back(newBB);
  Type *t = Type::getInt32Ty(header -> getContext());
  Constant *c = llvm::ConstantInt::get(t,uint32_t(0));
  ArrayRef<Value *> *param = new ArrayRef<Value *>(c);
  CallInst::Create(function, *param, "", newBB);
  if(unreachable){
    new UnreachableInst(header -> getContext(), newBB); 
  }else{
    BranchInst::Create(exitBB,newBB);
    for(BasicBlock::iterator it = exitBB->begin(); it != exitBB->end();++it){
      PHINode *phi = dyn_cast<PHINode>(it);
      if(!phi)
        break;
      //Value *latchValue = phi->getIncomingValueForBlock(latch);
      phi->addIncoming(UndefValue::get(phi -> getType()),newBB);
    }
  }

  BranchInst *newBr = NULL;
  if(cond){
    if(br -> getSuccessor(0) == header){
      newBr = BranchInst::Create(newBB,br -> getSuccessor(1),cond);
    }else{
      newBr = BranchInst::Create(br -> getSuccessor(1),newBB,cond);
    }
  }else{
    newBr = BranchInst::Create(newBB);
  }
  ReplaceInstWithInst(br,newBr);

  // The latch BasicBlock must be removed from the PHI nodes in
  // the header BasicBlock
  for(BasicBlock::iterator it = header->begin(); it != header->end();++it){
    PHINode *phi = dyn_cast<PHINode>(it);
    if(!phi)
      break;
    int latchIndex = phi->getBasicBlockIndex(latch);
    phi->removeIncomingValue(latchIndex);
  }

 //std::cout << "\n---- NewBB ------\n";

 //newBB -> print(outs());

 //std::cout << "\n---- ExitBB\n";

 //exitBB -> print(outs());


  return true;
}