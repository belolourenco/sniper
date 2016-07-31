/**
 * SEPass.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/20
 * @copyright : NII 2015
 */

#include "SEPass.h"

SEPass::SEPass(Context *context, const std::array<Function *,5>  &auxFuncs, int assertInContext)
  :VCGenPass(context, auxFuncs, assertInContext),vcs(){}

SEPass::~SEPass(){}

ListExpr *SEPass::getPropertiesForSolver(){
  assert(hasRunnedOnFunction && "the function runOnFunction was not executed");
  if(!solverExprs)
    solverExprs = &vcs.getP();
  return solverExprs;
}

void SEPass::printInfo(raw_ostream &OS){
  vcs.printInfo(OS);
}

void SEPass::print_(raw_ostream &OS){
  vcs.print(OS);
}

unsigned SEPass::sizeE(){
  return vcs.getSizeE();
}

unsigned SEPass::sizeP(){
  return vcs.getSizeP();
}

bool SEPass::runOnFunction(Function &f){
  assert(!hasRunnedOnFunction && "the function runOnFunction can be run only once");

  // Get entry basic block
  BasicBlock *entry = f.begin();
  assert(entry -> getName() == "entry");
  
  BasicBlock::iterator it = entry -> begin();
  ListExpr psi = ListExpr();
  encodeInst(NULL, psi, it);

  hasRunnedOnFunction = true;

  return false;
}

void SEPass::encodeInst(BasicBlock *p, const ListExpr &psi, BasicBlock::iterator it){

  //std::cout << "\n\nInstruction" << std::endl;
  //it -> print(outs());
  //std::cout << std::endl;

  BasicBlock *currentBB = it -> getParent();

  assert(currentBB && "current basic block is null");

  ListExpr psi2 = ListExpr(psi);
  switch (it->getOpcode()) {
    case Instruction::Br:{
      encodeBr(psi, cast<BranchInst>(it));
      break;
    }
    case Instruction::Call:{
      ExprPtr e = encodeAnn(psi, cast<CallInst>(it));
      if(e)
        psi2.andInAll(e);
      break;
    }
    case Instruction::Ret:{
      vcs.addToE(psi);
      break;
    }
    case Instruction::Unreachable:{
      vcs.addToE(psi);
      break;
    }
    case Instruction::Add:
    case Instruction::FAdd:
    case Instruction::Sub:
    case Instruction::FSub:
    case Instruction::Mul:
    case Instruction::FMul:
    case Instruction::UDiv:
    case Instruction::SDiv:
    case Instruction::FDiv:
    case Instruction::URem:
    case Instruction::SRem:
    case Instruction::FRem:
    case Instruction::And:
    case Instruction::Or:
    case Instruction::Xor:
    case Instruction::Shl:
    case Instruction::LShr:
    case Instruction::AShr:{
      ExprPtr e = encoder.encode(cast<BinaryOperator>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::ICmp:{
      ExprPtr e = encoder.encode(cast<ICmpInst>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::SExt:{
      ExprPtr e = encoder.encode(cast<SExtInst>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::ZExt:{
      ExprPtr e = encoder.encode(cast<ZExtInst>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::Select:{
      ExprPtr e = encoder.encode(cast<SelectInst>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::PHI:{
      ExprPtr e = encoder.encode(cast<PHINode>(it),p);
      psi2.andInAll(e);
      break;
    }
    // NOT IMPLEMENTED
    case Instruction::Switch:{
      assert(0 && "switch not implemented yet");
      ExprPtr e = encoder.encode(cast<SwitchInst>(it));
      psi2.andInAll(e);
      break;
    }
    case Instruction::Alloca:{
      assert(0 && "Alloca not implemented yet");
      // ExprPtr e = encoder.encode(cast<AllocaInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::Store:{
      assert(0 && "Store not implemented yet");
      // ExprPtr e = encoder.encode(cast<StoreInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::Load:{
      assert(0 && "Load not implemented yet");
      // ExprPtr e = encoder.encode(cast<LoadInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::GetElementPtr:{
      assert(0 && "GetElementPtr not implemented yet");
      // ExprPtr e = encoder.encode(cast<GetElementPtrInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::PtrToInt:{
      assert(0 && "PtrToInt not implemented yet");
      // ExprPtr e = encoder.encode(cast<PtrToIntInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::VAArg:{
      assert(0 && "VAArg not implemented yet");
      // ExprPtr e = encoder.encode(cast<VAArgInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::Invoke:{
      assert(0 && "Invoke not implemented yet");
      // ExprPtr e = encoder.encode(cast<InvokeInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::Trunc:{
      assert(0 && "Trunc not implemented yet");
      // ExprPtr e = encoder.encode(cast<TruncInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::FPTrunc:{
      assert(0 && "FPTrunc not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPTruncInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::FPExt:{
      assert(0 && "FPExt not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPExtInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::UIToFP:{
      assert(0 && "UIToFP not implemented yet");
      // ExprPtr e = encoder.encode(cast<UIToFPInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::SIToFP:{
      assert(0 && "SIToFP not implemented yet");
      // ExprPtr e = encoder.encode(cast<SIToFPInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::FPToUI:{
      assert(0 && "FPToUI not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPToUIInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::FPToSI:{
      assert(0 && "FPToSI not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPToSIInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::IntToPtr:{
      assert(0 && "IntToPtr not implemented yet");
      // ExprPtr e = encoder.encode(cast<IntToPtrInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::BitCast:{
      assert(0 && "switch not implemented yet");
      // ExprPtr e = encoder.encode(cast<BitCastInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::FCmp:{
      assert(0 && "FCmp not implemented yet");
      // ExprPtr e = encoder.encode(cast<FCmpInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::ExtractElement:{
      assert(0 && "ExtractElement not implemented yet");
      // ExprPtr e = encoder.encode(cast<ExtractElementInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::InsertElement:{
      assert(0 && "InsertElement not implemented yet");
      // ExprPtr e = encoder.encode(cast<InsertElementInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::ShuffleVector:{
      assert(0 && "ShuffleVector not implemented yet");
      // ExprPtr e = encoder.encode(cast<ShuffleVectorInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::ExtractValue:{
      assert(0 && "ExtractValue not implemented yet");
      // ExprPtr e = encoder.encode(cast<ExtractValueInst>(it));
      // psi2.andInAll(e);
      break;
    }
    case Instruction::InsertValue:{
      assert(0 && "InsertValue not implemented yet");
      // ExprPtr e = encoder.encode(cast<InsertValueInst>(it));
      // psi2.andInAll(e);
      break;
    }
    default:
      std::cout << "UNREACHABLE OPCODE: "
                << it->getOpcode()
                << std::endl;
      llvm_unreachable("Illegal opcode!");
  }

  ++it;
  if(it != currentBB -> end()){
    encodeInst(p,psi2,it);
  }
  return;
}

void SEPass::encodeBr(const ListExpr &psi, BranchInst *br){
  // std::cout << "BranchInst" << std::endl;

  BasicBlock *c = br -> getParent();

  if(br -> isConditional()){
    
    // condition encoding
    Value *cond = br -> getCondition();
    ExprPtr condExpr = context->getVariable(cond);
    if(!condExpr) {
        condExpr = context->newVariable(cond);
    }

    BasicBlock *next1 = br -> getSuccessor(0);
    BasicBlock *next2 = br -> getSuccessor(1);

    ListExpr psi1 = ListExpr(psi);
    ListExpr psi2 = ListExpr(psi);
    psi1.andInAll(condExpr);
    psi2.andInAll(Expression::mkNot(condExpr));

    encodeInst(c,psi1,next1 -> begin());
    encodeInst(c,psi2,next2 -> begin());
  }else{
    BasicBlock *next = br -> getSuccessor(0);
    encodeInst(c,psi,next->begin());
  }
}

ExprPtr SEPass::encodeAnn(const ListExpr &psi, CallInst *call){
  // std::cout << "CallInst" << std::endl;
  Function *f = call -> getCalledFunction();
  if(f == assertF || f == assumeF){

    // Encode assumed/asserted expression
    Value *attr = call -> getArgOperand(0);
    ExprPtr attrExpr = context->getVariable(attr);
    if(!attrExpr) {
        attrExpr = context->newVariable(attr);
    }

    ExprPtr cond = Expression::mkDiseq(attrExpr,Expression::mkUInt32Num(0));

    if(f == assumeF) return cond;

    ListExpr l = ListExpr(psi);
    l.implInAll(cond);
    vcs.addToP(l);
    
    if(assertInContext == 0 || assertInContext == 1) // 0 is default behavior, 1 is insert "assert into context"
      return cond;

    if(assertInContext == -1)
      return ExprPtr();

    std::cout << "ERROR: -assert_in_context with invalid value";
    exit(1);

  }  else if(f == non_detF){
    context -> newVariable(call);
    return ExprPtr();
  } else {
    assert(0 && "function call unauthorized here");
  }
}