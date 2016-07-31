/**
 * SPGen.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/30
 * @copyright : NII 2015
 */


 #include "SPGen.h"

SPGen::SPGen(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx)
                      :VCGenPass(context,auxFuncs,assertInCtx){vcs = new ListExpr();}

SPGen::~SPGen(){}

bool SPGen::runOnFunction(Function &f){
  assert(!hasRunnedOnFunction && "the function runOnFunction can be run only once");

  // initialize post dominator tree object with function f
  postDomTree.runOnFunction(f);

  // get entry basic block
  BasicBlock *entry = f.begin();
  assert(entry -> getName() == "entry");

  BasicBlock::iterator it = entry -> begin();
  ExprPtr psi = Expression::mkTrue();
  ExprPtr gamma = Expression::mkTrue();
  std::vector<BasicBlock*> pcds;
  BinaryExprPtr enc = encodeInst(NULL, pcds, psi, gamma, it);

  opEncoding = enc->getExpr1();

  hasRunnedOnFunction = true;
  
  return false;

}

void SPGen::printInfo(raw_ostream &OS){
  vcs->printInfo(OS);
}

void SPGen::print_(raw_ostream &OS){
  vcs->print(OS);
}

unsigned SPGen::sizeE(){
  return 1;
}

unsigned SPGen::sizeP(){
  return vcs->size();
}

BinaryExprPtr SPGen::encodeInst(BasicBlock *p, std::vector<BasicBlock *> &pcds, const ExprPtr psi, const ExprPtr gamma, BasicBlock::iterator it){
  
  BasicBlock *currentBB  = it -> getParent();

  assert(currentBB && "current basic block is null");

  // std::cout << "\nInstruction" << std::endl;
  // it -> print(outs());
  // std::string s = p ? p -> getName().str() : "null";
  // std::string postDomName = !pcds.empty() ? pcds.back()->getName().str()
  //                                           : "null";
  // std::cout << "CURRENT BB: " 
  //           << currentBB -> getName().str() 
  //           << "PREVIOUS BB: "
  //           << s
  //           <<"Common: "
  //           << postDomName
  //           << std::endl;

  unsigned opcode = it->getOpcode();
  if(opcode != Instruction::PHI && !pcds.empty() && pcds.back() == currentBB)
    return Expression::mkBinExpr(Expression::mkTrue(),Expression::mkTrue());

  BinaryExprPtr enc;
  switch (opcode) {
    case Instruction::Br:{
      enc = encodeBr(pcds, psi, gamma, cast<BranchInst>(it));
      break;
    }
    case Instruction::Call:{
      // check if this call was inserted by the VarsForArrays pass. If such then
      // only its name and its first parameters name are relevant.
      CallInst *call = dyn_cast<CallInst>(it);
      Function *f = call -> getCalledFunction();
      
      if(f == array_aux_1 || f == array_aux_2){
        Value *param = call -> getArgOperand(0);

        context -> setOldArrayName(param);

        if(f == array_aux_2){
          context -> setNewArrayName(call);
        }

        enc = Expression::mkBinExpr(Expression::mkTrue(),Expression::mkTrue());  

      } else {
        enc = Expression::mkBinExpr(Expression::mkTrue(),encodeAnn(psi, gamma, cast<CallInst>(it)));
      }
      break;
    }
    case Instruction::Ret:{
      enc = Expression::mkBinExpr(Expression::mkTrue(),Expression::mkTrue());
      break;
    }
    case Instruction::Unreachable:{
      enc = Expression::mkBinExpr(Expression::mkTrue(),Expression::mkTrue());
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
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::ICmp:{
      ExprPtr e = encoder.encode(cast<ICmpInst>(it));
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::SExt:{
      ExprPtr e = encoder.encode(cast<SExtInst>(it));
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::ZExt:{
      ExprPtr e = encoder.encode(cast<ZExtInst>(it));
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::Select:{
      ExprPtr e = encoder.encode(cast<SelectInst>(it));
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::PHI:{
      assert(p && "trying to encode a phi instruction with no previous block\n");
      ExprPtr e = encoder.encode(cast<PHINode>(it),p);
      enc = Expression::mkBinExpr(e, Expression::mkTrue());
      break;
    }
    case Instruction::Switch:{
      assert(0 && "switch not implemented yet");
      // ExprPtr e = encoder.encode(cast<SwitchInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::Alloca:{
      ExprPtr e = encodeArray(cast<AllocaInst>(it));
      enc = Expression::mkBinExpr(e,Expression::mkTrue());
      break;
    }
    case Instruction::Store:{
      ExprPtr e = encodeArray(cast<StoreInst>(it));
      enc = Expression::mkBinExpr(e,Expression::mkTrue());
      break;
    }
    case Instruction::Load:{
      ExprPtr e = encodeArray(cast<LoadInst>(it));
      enc = Expression::mkBinExpr(e,Expression::mkTrue());
      break;
    }
    case Instruction::GetElementPtr:{
      ExprPtr e = encodeArray(cast<GetElementPtrInst>(it));
      enc = Expression::mkBinExpr(e,Expression::mkTrue());
      break;
    }
    case Instruction::PtrToInt:{
      assert(0 && "PtrToInt not implemented yet");
      // ExprPtr e = encoder.encode(cast<PtrToIntInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::VAArg:{
      assert(0 && "VAArg not implemented yet");
      // ExprPtr e = encoder.encode(cast<VAArgInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::Invoke:{
      assert(0 && "Invoke not implemented yet");
      // ExprPtr e = encoder.encode(cast<InvokeInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::Trunc:{
      assert(0 && "Trunc not implemented yet");
      // ExprPtr e = encoder.encode(cast<TruncInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::FPTrunc:{
      assert(0 && "FPTrunc not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPTruncInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::FPExt:{
      assert(0 && "FPExt not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPExtInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::UIToFP:{
      assert(0 && "UIToFP not implemented yet");
      // ExprPtr e = encoder.encode(cast<UIToFPInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::SIToFP:{
      assert(0 && "SIToFP not implemented yet");
      // ExprPtr e = encoder.encode(cast<SIToFPInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::FPToUI:{
      assert(0 && "FPToUI not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPToUIInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::FPToSI:{
      assert(0 && "FPToSI not implemented yet");
      // ExprPtr e = encoder.encode(cast<FPToSIInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::IntToPtr:{
      assert(0 && "IntToPtr not implemented yet");
      // ExprPtr e = encoder.encode(cast<IntToPtrInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::BitCast:{
      assert(0 && "BitCast not implemented yet");
      // ExprPtr e = encoder.encode(cast<BitCastInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::FCmp:{
      assert(0 && "FCmp not implemented yet");
      // ExprPtr e = encoder.encode(cast<FCmpInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::ExtractElement:{
      assert(0 && "ExtractElement not implemented yet");
      // ExprPtr e = encoder.encode(cast<ExtractElementInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::InsertElement:{
      assert(0 && "InsertElement not implemented yet");
      // ExprPtr e = encoder.encode(cast<InsertElementInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::ShuffleVector:{
      assert(0 && "ShuffleVector not implemented yet");
      // ExprPtr e = encoder.encode(cast<ShuffleVectorInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::ExtractValue:{
      assert(0 && "ExtractValue not implemented yet");
      // ExprPtr e = encoder.encode(cast<ExtractValueInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
      break;
    }
    case Instruction::InsertValue:{
      assert(0 && "InsertValue not implemented yet");
      // ExprPtr e = encoder.encode(cast<InsertValueInst>(it));
      // ExprPtr impl = ExprUtils::mkImpl(pi.encode(), e);
      // vcs.addToE(impl);
      // psi2.add(impl);
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
    ExprPtr psi2 = ExprUtils::mkAnd(psi,enc->getExpr1());
    ExprPtr gamma2 = ExprUtils::mkAnd(gamma,enc->getExpr2());
    BinaryExprPtr enc2 = encodeInst(p,pcds,psi2,gamma2,it);
    return Expression::mkBinExpr(ExprUtils::mkAnd(enc -> getExpr1(), enc2 -> getExpr1()),
                                 ExprUtils::mkAnd(enc -> getExpr2(), enc2 -> getExpr2()));
  }
  else
    return enc;
}

BinaryExprPtr SPGen::encodeBr(std::vector<BasicBlock*> &pcds, const ExprPtr psi, const ExprPtr gamma, BranchInst *br){
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

    // CALCULATE POST COMMON DOMINATOR
    BasicBlock *npcd = postDomTree.findNearestCommonDominator(next1,next2);

    ExprPtr notCondExpr = ExprUtils::mkNeg(condExpr);

    ExprPtr gammat = ExprUtils::mkAnd(gamma,condExpr);
    ExprPtr gammaf = ExprUtils::mkAnd(gamma,notCondExpr);

    // ExprPtr psit = ExprUtils::mkAnd(psi,condExpr);
    // ExprPtr psif = ExprUtils::mkAnd(psi,notCondExpr);

    pcds.push_back(npcd);
    BinaryExprPtr enc1 = encodeInst(c,pcds,psi,gammat,next1 -> begin());
    BinaryExprPtr enc2 = encodeInst(c,pcds,psi,gammaf,next2 -> begin());
    pcds.pop_back();

    BinaryExprPtr enc 
      = Expression::mkBinExpr(ExprUtils::mkOr(ExprUtils::mkAnd(condExpr, enc1 -> getExpr1())
                                             ,ExprUtils::mkAnd(notCondExpr, enc2 -> getExpr1()))
                             , ExprUtils::mkOr(ExprUtils::mkAnd(condExpr, enc1 -> getExpr2())
                                              ,ExprUtils::mkAnd(notCondExpr, enc2 -> getExpr2())));

    if(std::find(pcds.begin(),pcds.end(),npcd) == pcds.end()){
      ExprPtr psiForPost = ExprUtils::mkAnd(psi,enc->getExpr1());
      ExprPtr gammaForPost = ExprUtils::mkAnd(gamma,enc->getExpr2());
      BinaryExprPtr enc3 = encodeInst(NULL,pcds,psiForPost,gammaForPost,rmPhi(npcd));

      return Expression::mkBinExpr(ExprUtils::mkAnd(enc -> getExpr1(), enc3 -> getExpr1()),
                                   ExprUtils::mkAnd(enc -> getExpr2(), enc3 -> getExpr2()));
    }else{
      return enc;
    }
  }else{
    BasicBlock *next = br -> getSuccessor(0);
    return encodeInst(c,pcds, psi, gamma, next->begin());
  }
}

// -----------------------------------------------------------
// ------------PARTIAL----------------------------------------

SPPartial::SPPartial(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx)
  :SPGen(context,auxFuncs,assertInCtx){ 
  std::cout << "\n******Running SP P******\n";
}

ExprPtr SPPartial::encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call){
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

    //if reached it is an assert
    vcs->add(ExprUtils::mkImpl(psi,ExprUtils::mkImpl(gamma, cond)));
    
    if(assertInContext == 0 || assertInContext == -1) // 0 is default behavior, -1 is DO NOT insert "assert into context"
      return Expression::mkTrue();
    
    if(assertInContext == 1)
      return cond;

    std::cout << "ERROR: -assert_in_context with invalid value";
    exit(1);

  } else if(f == non_detF){
    context -> newVariable(call);
    return Expression::mkTrue();
  } else {
    assert(0 && "function call unauthorized here");
  }
}

ListExpr *SPPartial::getPropertiesForSolver(){
  assert(hasRunnedOnFunction && "the function runOnFunction was not executed");
  if(!solverExprs)
    solverExprs = vcs;
  return solverExprs;
}

// -----------------------------------------------------------
// ------------PARTIAL + ASSERT-------------------------------

SPPartialAssert::SPPartialAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx)
:SPGen(context,auxFuncs,assertInCtx){
  std::cout << "\n******Running SP P + A******\n";
}

ExprPtr SPPartialAssert::encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call){
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

    //if reached it is an assert
    vcs->add(ExprUtils::mkImpl(psi,ExprUtils::mkImpl(gamma, cond)));
    
    if(assertInContext == -1) // 0 is default behavior, -1 is DO NOT insert "assert into context"
      return Expression::mkTrue();
    
    if(assertInContext == 0 || assertInContext == 1)
      return cond;

    std::cout << "ERROR: -assert_in_context with invalid value";
    exit(1);

  } else if(f == non_detF){
    context -> newVariable(call);
    return Expression::mkTrue();
  } else {
    assert(0 && "function call unauthorized here");
  }
}

ListExpr *SPPartialAssert::getPropertiesForSolver(){
  assert(hasRunnedOnFunction && "the function runOnFunction was not executed");
  if(!solverExprs)
    solverExprs = vcs;
  return solverExprs;
}

// -----------------------------------------------------------
// ------------GLOBAL-----------------------------------------

SPGlobal::SPGlobal(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx)
  :SPGen(context,auxFuncs,assertInCtx){ 
  std::cout << "\n******Running SP G******\n";
}

ExprPtr SPGlobal::encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call){
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

    //if reached it is an assert
    vcs->add(ExprUtils::mkImpl(gamma, cond));
    
    if(assertInContext == 0 || assertInContext == -1) // 0 is default behavior, -1 is DO NOT insert "assert into context"
      return Expression::mkTrue();
    
    if(assertInContext == 1)
      return cond;

    std::cout << "ERROR: -assert_in_context with invalid value";
    exit(1);

  } else if(f == non_detF){
    context -> newVariable(call);
    return Expression::mkTrue();
  } else {
    assert(0 && "function call unauthorized here");
  }
}

ListExpr *SPGlobal::getPropertiesForSolver(){
  assert(hasRunnedOnFunction && "the function runOnFunction was not executed");
  if(!solverExprs)
    solverExprs = new ListExpr(ExprUtils::mkImpl(opEncoding,vcs->conjunction()));
  return solverExprs;
}

// -----------------------------------------------------------
// ------------GLOBAL + ASSERT -------------------------------

SPGlobalAssert::SPGlobalAssert(Context *context, const std::array<Function *,5> &auxFuncs, int assertInCtx)
  :SPGen(context,auxFuncs,assertInCtx){
  std::cout << "\n******Running SP G + A******\n";
}

ExprPtr SPGlobalAssert::encodeAnn(const ExprPtr psi, const ExprPtr gamma, CallInst *call){
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

    //if reached it is an assert
    vcs->add(ExprUtils::mkImpl(gamma, cond));
    
    if(assertInContext == -1) // 0 is default behavior, -1 is DO NOT insert "assert into context"
      return Expression::mkTrue();
    
    if(assertInContext == 0 || assertInContext == 1)
      return cond;

    std::cout << "ERROR: -assert_in_context with invalid value";
    exit(1);

  } else if(f == non_detF){
    context -> newVariable(call);
    return Expression::mkTrue();
  } else {
    assert(0 && "function call unauthorized here");
  }
}

ListExpr *SPGlobalAssert::getPropertiesForSolver(){
  assert(hasRunnedOnFunction && "the function runOnFunction was not executed");
  if(!solverExprs)
    solverExprs = new ListExpr(ExprUtils::mkImpl(opEncoding,vcs->conjunction()));
  return solverExprs;
}