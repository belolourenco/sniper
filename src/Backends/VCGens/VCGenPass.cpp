/**
 * VCGen.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourencodero
 * @contact   : belolourencodero@di.uminho.pt
 * @date      : 2015/04/27
 * @copyright : NII 2015
 */

#include "VCGenPass.h"

char VCGenPass::ID = 0;

VCGenPass::VCGenPass(Context *_context, const std::array<Function *,5> &auxFuncs, int _assertInContext)
  :FunctionPass(ID), 
   context(_context), 
   assertF(auxFuncs[0]), 
   assumeF(auxFuncs[1]), 
   non_detF(auxFuncs[2]),
   array_aux_1(auxFuncs[3]),
   array_aux_2(auxFuncs[4]), 
   encoder(_context), 
   postDomTree(),
   solverExprs(NULL),
   hasRunnedOnFunction(false),
   assertInContext(_assertInContext){

    assert(auxFuncs.size() == 5);
  
  }

VCGenPass::~VCGenPass(){}

Context *VCGenPass::getContext(){
  return context;
}

Function *VCGenPass::getAssertFunc(){
  return assertF;
}

Function *VCGenPass::getAssumeFunc(){
  return assumeF;
}

BasicBlock::iterator VCGenPass::rmPhi(BasicBlock *b){
  BasicBlock::iterator it = b -> begin();
  for(; it != b -> end(); ++it){
    if(it->getOpcode() != Instruction::PHI)
      return it;
  }
  return it;
}

ExprPtr VCGenPass::encodeArray(AllocaInst *alloca){
  const Type *t = alloca->getAllocatedType();

  if(const ArrayType *aty = dyn_cast<ArrayType>(t)) {
    const Type *eltty = aty->getElementType();
    if (!eltty->isIntegerTy()) {
      eltty->print(outs());
      assert(0 && "Only integer type is supported in arrays.");
    }
  }else{
      assert(0 && "Only array of integers are supported in the Alloca instructions");
  }

  return Expression::mkTrue();
}

ExprPtr VCGenPass::encodeArray(StoreInst *store){
  Value *ptr = store -> getPointerOperand();
  // Get the index
  ExprPtr idx_expr = context -> getVariable(ptr);
  // Get the value
  Value *value = store -> getValueOperand();
  ExprPtr val_expr    = context -> newVariable(value);
  ExprPtr mem_expr1   = context -> getVariable(context -> getOldArrayName());
  ExprPtr mem_expr2   = context -> getVariable(context -> getNewArrayName());
  assert(mem_expr1 && mem_expr2 && "Some array identifier was not declared");
  ExprPtr update_expr = Expression::mkFunctionUpdate(mem_expr1, idx_expr, val_expr);
  ExprPtr eqExpr      = Expression::mkEq(mem_expr2, update_expr);
  return eqExpr;
}

ExprPtr VCGenPass::encodeArray(LoadInst *load){
  Value *ptr          = load -> getPointerOperand();
  ExprPtr lhs_expr    = context -> newVariable(load);
  ExprPtr mem_expr    = context -> getVariable(context -> getOldArrayName());
  ExprPtr appargExpr  = context -> getVariable(ptr);
  ExprPtr app_expr    = Expression::mkApp(mem_expr, appargExpr); 
  ExprPtr eqExpr      = Expression::mkEq(lhs_expr, app_expr);
  return eqExpr; // hard or soft
}

ExprPtr VCGenPass::encodeArray(GetElementPtrInst *gep){
  if(AllocaInst *a = dyn_cast<AllocaInst>(gep->getPointerOperand())) {

    assert(gep -> hasIndices() && "Only arrays are supported in getelementptr");
    
    Type *ty = a->getAllocatedType();
    assert(ty->isArrayTy() && "Only arrays are supported in getelementptr");

    // get index
    Value *index      = gep -> getOperand(2);
    ExprPtr indexExpr = context -> newVariable(index);
    ExprPtr gepExpr   = context -> newVariable(gep);
    ExprPtr assignExpr = Expression::mkEq(gepExpr, indexExpr);

    return assignExpr;
  }else{
    assert(0 && "Only arrays are supported in the getelementptr instruction");
    return NULL;
  }
}
