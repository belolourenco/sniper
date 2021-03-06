/**
 * VCGenFrontend.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/11/20
 * @copyright : NII 2015
 */

#include "VCGenFrontend.h"


VCGenFrontend::VCGenFrontend(Options *_opts, raw_ostream *_OS){
  opts    = _opts;
  OS = _OS;
}

void VCGenFrontend::init(char *prog_name){

  if(opts -> listVCGens()){
    listVCGens();
    exit(0);
  }

  sys::PrintStackTraceOnErrorSignal();

  // Lot of copy-paste from lli.cpp
  LLVMContext &llvmctx = getGlobalContext();
 
  // If we have a native target, initialize it to ensure  
  // it is linked in and usable by the JIT.
  InitializeNativeTarget();

  llvmMod = NULL;
  SMDiagnostic Err;
  llvmMod = ParseIRFile(opts->getInputIRFilename(), Err, llvmctx);
  if (!llvmMod) {
      Err.print(prog_name, errs());
      exit(1);
  } 

  debug   = new Debug(llvmMod, opts -> getFunctionName());
  
  if(opts -> printIntermediateIR())
    debug -> output("initial");

  targetF = llvmMod->getFunction(opts -> getFunctionName());
  if(!targetF){
    *OS << "Input function not found!";
    exit(1);
  }

  PassManager *PMY = new PassManager();
  AuxFuncsPass *auxFuncs = new AuxFuncsPass(); 
  PMY -> add(auxFuncs);
  PMY -> run(*llvmMod);
  delete PMY;

  DataLayout  *DL = new DataLayout(llvmMod);
  PassManager *PM = new PassManager();
  PM->add(DL);
  // !!!!!!!!!!!!!!!!ATTENTION - FUNCITONS ARE NOT BEING INLINED
  // The reason is that we don't want the non_det() function to be inlined
  // To support inlining, FullFunctionInliningPass has to be updated
  //PM->add(new FullFunctionInliningPass(options));
  PM->add(createFunctionInliningPass());
  PM->run(*llvmMod); // First round
  delete PM;

  // Save local variable names before processing the bytecode
  LocalVariables *LV = new LocalVariables(); 
  LV->processLoadStore(targetF);

  // Process global variables
  GlobalVariables *GV = new GlobalVariables();
  GV->process(targetF);
  delete GV;

  // Promote alloca instructions to SSA registers
  // & Assign names to anonymous instructions
  FunctionPassManager *FPM = new FunctionPassManager(llvmMod);
  FPM->add(createPromoteMemoryToRegisterPass());
  FPM->add(createInstructionNamerPass());
  // Unroll loops
  FPM->add(createLoopSimplifyPass());
  FPM->add(createLoopRotatePass());
  FPM->add(createLCSSAPass());
  // Unroll loops regardless of how much code expansion would result
  int Threshold = 32767;
  int Count = opts->getUnrollCount();
  int AllowPartial = 1; // true
  FPM->add(createLoopUnrollPass(Threshold, Count, AllowPartial));
  //++FPM->add(createCFGSimplificationPass());
  FPM->doInitialization();
  FPM->run(*targetF); 
  delete FPM;

  // FunctionPassManager *FPM_aux = new FunctionPassManager(llvmMod);
  // FPM_aux -> add(createIndVarSimplifyPass());
  // FPM_aux -> doInitialization();
  // FPM_aux -> run(*targetF);
  // delete FPM_aux;

  // Get information about loops
  // FunctionPassManager *FPM2 = new FunctionPassManager(llvmMod);
  // LoopInfoPass *LIP = new LoopInfoPass(llvmMod, opts->dbgMsg());
  // FPM2->add(LIP); 
  // FPM2->doInitialization();
  // FPM2->run(*targetF); 
  // delete FPM2;

  // Process the phi instructions
  // LV->processPhi();
  // Process returns
  // processFunctionReturns(targetF);

  // Check the signature of the target function
  // and deppending on the type try to simplify the function
  bool hasArgv = isStandardFunctionSignature(targetF);
  if (hasArgv) {
      //bool simplified = simplifyFunctionSignature(targetF);
      //if (simplified) {
      //    std::cout << "info: the function was successfully simplified!\n";
      //}
  } else {
      checkFunctionSignature(targetF);
  }

  if(opts -> printIntermediateIR())
    debug -> output("before_rm_loops");

  assertF = llvmMod -> getFunction("assert");
  assumeF = llvmMod -> getFunction("assume");
  nondetF = llvmMod -> getFunction("nondet_int");
  nondetF = llvmMod -> getFunction("nondet_int");
  arrayAux1 = llvmMod -> getFunction("ARRAY_AUX_1");
  arrayAux2 = llvmMod -> getFunction("ARRAY_AUX_2");

  assert(assertF && "assert function not found");
  assert(assumeF && "assume function not found");
  assert(nondetF && "nondet_int function not found");
  assert(arrayAux1);
  assert(arrayAux2);

  Function *unwindAnnotation;
  if(opts -> isAssertAnnotation())
      unwindAnnotation = assertF;
  else
      unwindAnnotation = assumeF;

  RmLoopPass *rmLoop;
  if(opts -> getVCGen() == 0)
      rmLoop = new RmLoopPass(unwindAnnotation,true);
  else
      rmLoop = new RmLoopPass(unwindAnnotation,false);
  FunctionPassManager *FPM4 = new FunctionPassManager(llvmMod);
  FPM4 -> add(rmLoop);
  FPM4 -> doInitialization();
  FPM4 -> run(*targetF);
  delete FPM4;

  VarsForArrays *arrays_pass = new VarsForArrays(arrayAux1,arrayAux2,allArrayVars);
  FunctionPassManager *FPM5 = new FunctionPassManager(llvmMod);
  FPM5 -> add(arrays_pass);
  FPM5 -> doInitialization();
  FPM5 -> run(*targetF);
  delete FPM5;

  FunctionPassManager *FPM6 = new FunctionPassManager(llvmMod);
  FPM6 -> add(createConstantPropagationPass());
  FPM6 -> doInitialization();
  FPM6 -> run(*targetF);
  delete FPM6;

  // std::cout << "\n########################\n";
  // for(std::set<Value*>::iterator it = allArrayVars.begin(); it != allArrayVars.end();it++){
  //   (*it) -> print(outs());
  //   std::cout << "\n";
  // }
  // std::cout << "\n########################\n";

  if(opts -> printIntermediateIR())
    debug -> output("final");

  if(opts -> printIntermediateIR()){
    *OS << "Converting initial CFG to PNG\n";
    debug -> toCFG("initial");
    *OS << "Converting intermediate CFG to PNG\n";
    debug -> toCFG("before_rm_loops");
    *OS << "Converting final CFG to PNG\n";
    debug -> toCFG("final");
  }

  ctx = new Context(LV);

  ctx -> arrayVars(allArrayVars);

  chooseVCGen(opts -> getAssertInContext());

  cyclomatic_complexity();
}

void VCGenFrontend::launch(){

  *OS << "\n\n ============= Starting VC Generation ================\n\n";
  
  if(opts -> executeBench()){
    executeBench(ctx);
    exit(0);
  }

  *OS << "\n" << vcgenName << " VCs started being generated\n";

  FunctionPassManager *FPM6 = new FunctionPassManager(llvmMod);
  FPM6 -> add(vcgen);
  FPM6 -> doInitialization();

  auto vc_gen_start_time = std::chrono::steady_clock::now();
  FPM6 -> run(*targetF);
  auto vc_gen_end_time = std::chrono::steady_clock::now();
  auto vc_gen_total_time = vc_gen_end_time - vc_gen_start_time;
  *OS << vcgenName
      << " VCs are now generated\n"
      << " Elapsed time: "
      << std::chrono::duration <double, std::milli> (vc_gen_total_time).count() 
      << " ms\n";

  *OS << "\n@@@@@@" << vcgenName << "@@@@@@\n";
  vcgen -> printInfo(outs());
  *OS <<   "\n\n\tcyclomatic_complexity: " << cycl_comp << "\n";
  *OS << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

  //vcgen -> print(outs());
  //vcgen -> getPropertiesForSolver() -> print(outs());
  SolveVCs solver = SolveVCs(vcgen -> getPropertiesForSolver());

  delete FPM6;

  *OS << "\n" << vcgenName << " VCs started being solved";

  //solver.toFile();

  if(opts -> genWhy3()){
    *OS << "\n Generating Why3 file\n";
    solver.checkInWhy3();
    *OS << "\n Why3 file successfully generated\n";
  }
  
  if(opts -> genSMTLib2()){
    *OS << "\n Generating SMTLib v2 file\n";
    solver.generateSMTLib2();
    *OS << "\n SMTLib v2 file successfully generated\n";
  }
  
  if(!opts -> genWhy3() && !opts -> genSMTLib2()){
    solver.checkVCValidity();
  
    solver.printInfo(outs());
  }

  *OS << "\n\n ============= DONE ================\n\n";

  return;
}

void VCGenFrontend::executeBench(Context *ctx){

    std::string execution_nr;
    std::fstream config_file;
    config_file.open("./src/Backends/VCGens/Benchmarks/config.txt");
    getline(config_file, execution_nr);
    std::string file_name = "./src/Backends/VCGens/Benchmarks/results/"+execution_nr+".csv";

    std::ofstream outputfile;
    if(!std::ifstream(file_name)){ //if file does not exists
        outputfile.open(file_name.c_str());
        outputfile << opts -> getInputCSourceFilename() << std::endl
                   << "Function: " << opts -> getFunctionName() 
                   << ",CC," << cycl_comp << std::endl
                   << "Unwind: " << ((opts -> isAssertAnnotation())?"assert":"assume") << std::endl
                   << "Unwind nr:, " << opts -> getUnrollCount() << std::endl
                   << "Assert in Context: "
                     << ((opts -> getAssertInContext() == 0)?"default":((opts -> getAssertInContext() == 1)?"yes":"no"))
                   << std::endl
                   << std::endl;
    
        outputfile << "Alg,N_Enc,N_Prop,Time_to_gen,"
                   << "true_exps,false_exps,num_exps,int_var_exps,bool_var_exps,bool_vars,int_vars,"
                   << "comparison_ops,not_ops,and_ops,or_ops,xor_ops,sum_ops,sub_ops,mul_ops,ite_ops,"
                   << "app_ops,update_ops,div_ops,mod_ops,parse_exps,"
                   << "1_Val,1_Inv,1_Und,1_time"
                   << std::endl
                   << std::endl;
    }else{
        outputfile.open(file_name.c_str(), std::ios::app);
    }

    *OS << "\nExecute Bench started execution\n";
    
    FunctionPassManager *FPM6 = new FunctionPassManager(llvmMod);
    FPM6 -> add(vcgen);
    FPM6 -> doInitialization();
    *OS <<  vcgenName << " VCs started being generated\n";

    auto vc_gen_start_time = std::chrono::steady_clock::now();
    FPM6 -> run(*targetF);
    auto vc_gen_end_time = std::chrono::steady_clock::now();
    auto vc_gen_total_time = vc_gen_end_time - vc_gen_start_time;
    double duration = 
        std::chrono::duration <double, std::milli> (vc_gen_total_time).count();
    *OS << vcgenName << " VCs are now generated. Time: " << std::to_string(duration) << "\n";
    outputfile << vcgenName << "," 
               << vcgen -> sizeE() << "," << vcgen -> sizeP() << "," << duration;
    // std::cout << "\n\n#############################################\n";
    // vcgen -> getPropertiesForSolver() -> print(outs());
    // std::cout << "\n#############################################\n\n";
    unsigned valid = 0,invalid = 0,undef = 0;
    Profiling p;
    ListExpr *vcs = vcgen -> getPropertiesForSolver();
    delete FPM6;
    for(int y = 0; y < 1; ++y){
        SolveVCs solver = SolveVCs(vcs);
        * OS <<  vcgenName << " VCs iteration " << y
             << " started being solved\n";

        solver.checkVCValidity();
        
        if(y == 0){
            valid   = solver.getValid();
            invalid = solver.getInvalid();
            undef   = solver.getUndef();
            p = solver.getProfiling();
            
            outputfile << "," << p.true_exps
                       << "," << p.false_exps
                       << "," << p.num_exps
                       << "," << p.int_var_exps
                       << "," << p.bool_var_exps
                       << "," << p.bool_vars
                       << "," << p.int_vars
                       << "," << p.comparison_ops
                       << "," << p.not_ops
                       << "," << p.and_ops
                       << "," << p.or_ops
                       << "," << p.xor_ops
                       << "," << p.sum_ops
                       << "," << p.sub_ops
                       << "," << p.mul_ops
                       << "," << p.ite_ops
                       << "," << p.app_ops
                       << "," << p.update_ops
                       << "," << p.div_ops
                       << "," << p.mod_ops
                       << "," << p.parse_exps
                       << "," << valid << "," << invalid
                       << "," << undef;
        }else{
            assert( valid == solver.getValid() && invalid == solver.getInvalid() && undef == solver.getUndef());
        }
        outputfile << "," << solver.getDuration();
        *OS <<  vcgenName << " VCs iteration " << y << " are now solved"
            << "\n";
    }
    outputfile << std::endl;
    outputfile.close();
}

void VCGenFrontend::finish(){
}

void VCGenFrontend::listVCGens(){
  *OS << "\n";
  *OS << "0  - Symbolic Execution\n";
  *OS << "1  - CNF global     + asserts  (assert IN context)\n";
  *OS << "2  - CNF global                (assert NOT IN context)\n";
  *OS << "3  - CNF partial    + asserts  (assert IN context)\n";
  *OS << "4  - CNF partial               (assert NOT IN context)\n\n";
  *OS << "5  - SSA global     + asserts  (assert IN context)\n";
  *OS << "6  - SSA global                (assert NOT IN context)\n";
  *OS << "7  - SSA partial    + asserts  (assert IN context)\n";
  *OS << "8  - SSA partial               (assert NOT IN context)\n\n";
  *OS << "9  - SP global      + asserts  (assert IN context)\n";
  *OS << "10 - SP global                 (assert NOT IN context)\n";
  *OS << "11 - SP partial     + asserts  (assert IN context)\n";
  *OS << "12 - SP partial                (assert NOT IN context)\n\n";
  *OS << "13 - Linear global  + asserts  (assert IN context)\n";
  *OS << "14 - Linear global             (assert NOT IN context)\n";
  *OS << "15 - Linear partial + asserts  (assert IN context)\n";
  *OS << "16 - Linear partial            (assert NOT IN context)\n\n";
}

void VCGenFrontend::chooseVCGen(int assertInCtx){
  std::array<Function *, 5> auxFuncs = {assertF,assumeF,nondetF,arrayAux1,arrayAux2};
  switch(opts -> getVCGen()){
        case 0:{ 
            vcgen = new SEPass(ctx,auxFuncs,assertInCtx);
            vcgenName = "SE    ";
            break;
        }case 1:{
            vcgen = new CNFGlobalAssert(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "CNF G+A ";
            break;
        }case 2:{
            vcgen = new CNFGlobal(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "CNF G ";
            break;
        }case 3:{
            vcgen = new CNFPartialAssert(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "CNF P + A ";
            break;
        }case 4:{
            vcgen = new CNFPartial(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "CNF P ";
            break;
        }case 5:{
            vcgen = new CNFGlobalAssert(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "SSA G+A ";
            break;
        }case 6:{
            vcgen = new CNFGlobal(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "SSA G ";
            break;
        }case 7:{
            vcgen = new CNFPartialAssert(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "SSA P + A ";
            break;
        }case 8:{
            vcgen = new CNFPartial(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "SSA P ";
            break;
        }case 9:{
            vcgen = new SPGlobalAssert(ctx,auxFuncs,assertInCtx);
            vcgenName = "SP G+A ";
            break;
        }case 10:{
            vcgen = new SPGlobal(ctx,auxFuncs,assertInCtx);
            vcgenName = "SP G ";
            break;
        }case 11:{
            vcgen = new SPPartialAssert(ctx,auxFuncs,assertInCtx);
            vcgenName = "SP P + A ";
            break;
        }case 12:{
            vcgen = new SPPartial(ctx,auxFuncs,assertInCtx);
            vcgenName = "SP P ";
            break;
        }case 13:{
            vcgen = new LinAssert(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "Lin G+A ";
            break;
        }case 14:{
            vcgen = new Lin(ctx,auxFuncs,assertInCtx,true);
            vcgenName = "Lin G ";
            break;
        }case 15:{
            vcgen = new LinAssert(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "Lin P + A ";
            break;
        }case 16:{
            vcgen = new Lin(ctx,auxFuncs,assertInCtx,false);
            vcgenName = "Lin P ";
            break;
        }
        default: assert(0 && "executeBench something went wrong");
    }
}

void VCGenFrontend::cyclomatic_complexity(){
    long nodes=0;
    long edges=0;
    cycl_comp = 0;
    Function::iterator it = targetF -> begin();
    for(; it != targetF -> end(); ++it){
        nodes++;
        edges += it -> getTerminator() -> getNumSuccessors();
    }
    cycl_comp = edges-nodes+2;
}


// ============================================================================
// isStandardFunctionSignature 
// 
// return true if the function is of type: int main(int argc, char **argv)
// else return false.
// =============================================================================
bool VCGenFrontend::isStandardFunctionSignature(Function *targetF) {
    if (!targetF->getReturnType()->isIntegerTy(32)) {
        return false;
    }
    if (targetF->arg_size()!=2) {
        return false;
    }
    Function::arg_iterator ait = targetF->arg_begin();
    Value *argc = ait++;
    if (!argc->getType()->isIntegerTy(32)) {
        return false;
    }
    Value *argv = ait;    
    const Type *T = argv->getType();
    if(!T->isPointerTy() || T->getNumContainedTypes()!=1) {
        return false;
    }
    const Type *T2 = T->getContainedType(0);
    if (!T2->isPointerTy() || T2->getNumContainedTypes()!=1) {
        return false;
    }
    const Type *T3 = T2->getContainedType(0);
    if (!T3->isIntegerTy(8)) {
        return false;
    }
    return true;
}

// ============================================================================
// checkFunctionSignature 
// 
// Check if the function signature can be handle by SNIPER's formula encoder.
// Exit the program if the function signature is not supported.
// =============================================================================
void VCGenFrontend::checkFunctionSignature(Function *targetF) {
    // Check the number of args
    // unsigned size = targetF->arg_size();
    // if (size==0) {
    //     std::cout << "exit: The function " << targetF->getName().str();
    //     std::cout << " does not take any arguments.\n";
    //     exit(1);
    // }
    // Check function return type  
    // const Type *retTy =  targetF->getReturnType();
    // if (targetF->isVarArg() || (!retTy->isIntegerTy(32) && !retTy->isVoidTy())) {
    //     std::cout << "error: the type of the function ";
    //     std::cout << targetF->getName().str();
    //     std::cout << " is not supported.\n";
    //     exit(1);
    // } 
    // Check the type of the arguments
    const FunctionType *FTy = targetF->getFunctionType();
    Function::arg_iterator ait;
    for (ait = targetF->arg_begin(); ait != targetF->arg_end(); ++ait) {
        const unsigned argNo = ait->getArgNo();
        const Type *argTy = FTy->getParamType(argNo);
        if (!argTy->isIntegerTy(32)) {
            *OS << "error: the type of the function ";
            *OS << targetF->getName().str();
            *OS << " is not supported.\n";
            exit(1);
        }
    }
}

void VCGenFrontend::processFunctionReturns(Function *f) {
    std::vector<Instruction*> worklist;
    for (inst_iterator I = inst_begin(f), E = inst_end(f); I != E; ++I) {
        /*MDNode *N = I->getMetadata("dbg");
        if (N) {
            DILocation Loc(N);
            unsigned line = Loc.getLineNumber();
            std::cout << line << ", ";
        }*/
        if(I->getOpcode()==Instruction::Add
           && I->getName().substr(0, 4) == "_ret") {
            worklist.push_back(&*I);
        }
    }
    //std::cout << std::endl;
    // Replace the dummy instructions _retx = v + v by
    // _retx = v + 0
    for (Instruction *I : worklist) {
        Value *V = I->getOperand(0);
        Value *zeroVal = ConstantInt::get(V->getType(), 0);
        BinaryOperator *addInst = BinaryOperator::CreateAdd(V, zeroVal);
        // Set debugging metadata
        MDNode *N = I->getMetadata("dbg");
        if (N) {
            addInst->setMetadata("dbg", N);
        } else {
            I->dump();
            *OS << "warning : metadata!\n";
        }
        BasicBlock::iterator ii(I);
        ReplaceInstWithInst(I->getParent()->getInstList(), ii, addInst);
    }
}