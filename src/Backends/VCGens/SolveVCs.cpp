/**
 * SolveVCs.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/23
 * @copyright : NII 2015
 */

#include "SolveVCs.h"

SolveVCs::SolveVCs(ListExpr *_exprs):exprs(_exprs),solver(new YicesSolver()),valid(0),invalid(0),undef(0),duration(0){}

SolveVCs::~SolveVCs(){
  delete solver;
}

unsigned long SolveVCs::getValid(){
  return valid;
}

unsigned long SolveVCs::getInvalid(){
  return invalid;
}

unsigned long SolveVCs::getUndef(){
  return undef;
}

double SolveVCs::getDuration(){
  return duration;
}

Profiling SolveVCs::getProfiling(){
  return solver -> getProfiling();
}

void SolveVCs::toFile(){
  //int cont = 0;

  // for(ExprPtr e : exprs -> getExprs()){
    
  //   solver -> init();
  //   ExprPtr notE = Expression::mkNot(e);
  //   solver -> createFile(notE,cont);

  //   solver -> clean();
  //   cont++;
  // }

  solver -> init();
  solver -> createFilePushPop(exprs -> getExprs());
  solver -> clean();
}

void SolveVCs::checkVCValidity(){

  auto total = std::chrono::nanoseconds(0);

  int counter = 0;
  //ExprPtr e = exprs -> conjunction();
  for(ExprPtr e : exprs -> getExprs()){
    std :: cout << "\nSolving VC " << counter++ << "\n";
    
//////////////////////////////////////////////////

    // solver -> init();
    // ExprPtr notE = Expression::mkNot(e);

    // solver -> addToContext(notE);

    // //int i;
    // //std::cout << "\n\nWAITING\n\n";
    // //scanf("%d",&i);

    // auto start_time = std::chrono::steady_clock::now();
    // int result = solver -> check();
    // auto end_time = std::chrono::steady_clock::now();
    // auto diff = end_time - start_time;
    // std::cout << std::chrono::duration <double, std::milli> (diff).count();
    // total += std::chrono::duration_cast<std::chrono::nanoseconds>(diff);

    // solver -> clean();

//////////////////////////////////////////////////

    ExprPtr notE = Expression::mkNot(e);

    YicesSolver solver;
    solver.init();
    solver.addExpr(notE);
    auto start_time = std::chrono::steady_clock::now();
    solver.addExprsToContext();
    int result = solver.check();
    auto end_time = std::chrono::steady_clock::now();
    auto diff = end_time - start_time;
    std::cout << std::chrono::duration <double, std::milli> (diff).count();
    total += std::chrono::duration_cast<std::chrono::nanoseconds>(diff);

    solver.clean();

//////////////////////////////////////////////////

    switch(result){
      case l_false:{
        valid++;
        break;
      }
      case l_undef:{
        undef++;
        break;
      }
      case l_true:{
        invalid ++;
        //std::cout << solver -> getModel();
        break;
      }
    }
    if(invalid){
      std::cout << "\n Assertion failed:\n";
      //e -> print(outs());
      break;
    }
  }
  duration = std::chrono::duration <double, std::milli> (total).count();
}

void SolveVCs::checkInWhy3(){

  int counter = 0;

  for(ExprPtr e : exprs -> getExprs()){
    std :: cout << "\nWhy3 VC " << counter << "\n";

    //ExprPtr notE = Expression::mkNot(e);
    
    std::string errorMessage = ""; 
    std::string fileName = "./vcs/vc" + std::to_string(counter) + ".why";
    raw_fd_ostream ostream(fileName.c_str(), errorMessage);
    if(!errorMessage.empty()){
      errs() << "Error opening file to write VCs" << "\n";
      exit(1);
    }

    Why3Gen w3gen;
    w3gen.init();
    w3gen.addToTheory(std::to_string(counter),e);
    w3gen.prettyprintTheory(ostream);

    counter++;
  }
}

void SolveVCs::generateSMTLib2(){
  int counter = 0;

  SMTLib2Gen smt;
  smt.init();

  for(ExprPtr e : exprs -> getExprs()){
    std :: cout << "\nSMTLib VC " << counter;

    ExprPtr notE = Expression::mkNot(e);

    smt.encode(notE);

    counter++;
  }

  std::string errorMessage = ""; 
  std::string fileName = "./vcs/vc" + std::to_string(counter) + ".smt2";
  raw_fd_ostream ostream(fileName.c_str(), errorMessage);
  if(!errorMessage.empty()){
    errs() << "Error opening file to write VCs" << "\n";
    exit(1);
  }

  smt.prettyprint(ostream);
}

void SolveVCs::printInfo(raw_ostream &OS){
    OS <<   "# Valid  : " << valid   << "\n";
    OS <<   "# Invalid: " << invalid << "\n";
    OS <<   "# Undef  : " << undef   << "\n";
    OS <<   "# Int vars: " << solver -> getProfiling().int_vars << "\n";
    OS <<   "# Bool vars: " << solver -> getProfiling().bool_vars << "\n";
    OS <<   "#                             #\n";
    std::ostringstream strs;
    strs << duration;
    OS <<   "# Time: " << std::to_string(duration) << "\n";
    OS <<   "###############################\n";
}
