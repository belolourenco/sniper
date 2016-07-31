/**
 * VarsForArrays.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/01/06
 * @copyright : NII 2015
 */

 #include "VarsForArrays.h"


char VarsForArrays::ID = 0;

VarsForArrays::VarsForArrays(Function *_array_aux_1, Function *_array_aux_2, std::set<Value*> &_allArrayVars)
  :FunctionPass(ID),allArrayVars(_allArrayVars){
  array_aux_1 = _array_aux_1;
  array_aux_2 = _array_aux_2;
};

VarsForArrays::~VarsForArrays(){
};

bool VarsForArrays::runOnFunction(Function &f){
  int32_type = Type::getInt32Ty(f.getContext());
  const0 = ConstantInt::get(int32_type,uint32_t(0));

  for(Function::iterator bb_it = f.begin(); bb_it != f.end();++bb_it){
    for(BasicBlock::iterator intrs_it = bb_it -> begin()
        ; intrs_it != bb_it -> end(); ++intrs_it){
      GetElementPtrInst *getInstr = dyn_cast<GetElementPtrInst>(intrs_it);
      if(getInstr){
        processGetElementInstr(f,bb_it,getInstr);
        continue;
      }
      AllocaInst *alloca = dyn_cast<AllocaInst>(intrs_it);
      if(alloca){
        processAlloca(f,bb_it,alloca);
        continue;
      }
    }

  }

  FunctionPassManager *FPM6 = new FunctionPassManager(f.getParent());
  FPM6->add(createPromoteMemoryToRegisterPass());
  FPM6->doInitialization();
  FPM6->run(f); 
  delete FPM6;

  //Collect all the introduced variables, that is, all introduced call instructions and
  // all the phi nodes created to propagate their values. First we iterate through all the 
  //the introduced calls to array_aux_2 
  for(std::vector<Instruction*>::iterator it = createdCalls.begin(); it != createdCalls.end(); it++){
    allArrayVars.insert(*it);

    //Then we check if there is some phi node using it. If so, and if this node name is not
    //yet in the list we add it to the list and recursively look for other nodes
    for(Value::use_iterator use = (*it) -> use_begin(); use != (*it) -> use_end(); use++){
      if(PHINode *phi = dyn_cast<PHINode>(*use)){
        if(allArrayVars.find(phi) == allArrayVars.end()){
          varsInPhi(phi);
          allArrayVars.insert(phi);
        }
      }
    }
  }

  return true;
}

// It recursively adds to allArrayVars all phi nodes not yet there 
void VarsForArrays::varsInPhi(PHINode *phi){
  for(Value::use_iterator use = phi -> use_begin(); use != phi -> use_end(); use++){
    if(PHINode *phi = dyn_cast<PHINode>(*use)){
      if(allArrayVars.find(phi) == allArrayVars.end()){
          allArrayVars.insert(phi);
          varsInPhi(phi);
        }
    }
  }

}

void VarsForArrays::processGetElementInstr(Function &f, BasicBlock *b, GetElementPtrInst *getInstr){
  AllocaInst *alloca = dyn_cast<AllocaInst>(getInstr -> getPointerOperand());
  
  assert(alloca && "Something wrong with arrays: ");

  LoadInst *load = new LoadInst(vars.find(alloca)->second);
  b -> getInstList().insert(getInstr,load);

  BasicBlock::iterator it(getInstr);
  Instruction * loadOrStore = ++it;
  if(dyn_cast<LoadInst>(loadOrStore)){
    CallInst *call = CallInst::Create(array_aux_1,load);
    b -> getInstList().insert(getInstr,call);
  }
  else if(dyn_cast<StoreInst>(loadOrStore)){
    CallInst *call = CallInst::Create(array_aux_2,load,"array_" + alloca -> getName());
    StoreInst *store = new StoreInst(call,vars.find(alloca)->second);
    b -> getInstList().insert(getInstr,call);
    b -> getInstList().insert(getInstr,store);
    createdCalls.push_back(call);
  }
  else assert(0 && "Operation after GetElementPtrInst is not a load or a store");
}


void VarsForArrays::processAlloca(Function &f, BasicBlock *b, AllocaInst *alloca){
  CallInst *call = CallInst::Create(array_aux_2,const0,"array_" + alloca -> getName());
  AllocaInst *new_alloca = new AllocaInst(int32_type, "array_" + alloca -> getName());
  StoreInst *store = new StoreInst(call,new_alloca);

  b -> getInstList().insert(alloca,call);
  b -> getInstList().insert(alloca,new_alloca);
  b -> getInstList().insert(alloca,store);

  vars.insert(std::pair<AllocaInst*,Instruction*>(alloca,new_alloca));
  createdCalls.push_back(call);
}