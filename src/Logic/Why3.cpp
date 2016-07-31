/**
 * Why3.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/04/20
 * @copyright : NII 2015
 */

#include "Why3.h"

W3UsePtr  W3Decl::mkUseImport(const std::string &theory){\
  return std::make_shared<W3Use>(W3Use::W3Import,theory);
}

W3UsePtr  W3Decl::mkUseExport(const std::string &theory){\
  return std::make_shared<W3Use>(W3Use::W3Export,theory);
}

W3GoalPtr W3Decl::mkGoal(const std::string &name, W3ExprPtr e){\
  return std::make_shared<W3Goal>(name,e);
}

W3LitExprPtr W3Expr::mkTrue(){
  return std::make_shared<W3LitExpr>(true);
}

W3LitExprPtr W3Expr::mkFalse(){
  return std::make_shared<W3LitExpr>(false);
}

W3LitExprPtr W3Expr::mkInt(int i){
  return std::make_shared<W3LitExpr>(i);
}

W3LitExprPtr W3Expr::mkUInt(unsigned int i){
  return std::make_shared<W3LitExpr>(i);
}

W3AppExprPtr W3Expr::mkApp(const std::string &name, W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>(name,e1,e2);
}

W3AppExprPtr W3Expr::mkIntVar(const std::string &n){
  return std::make_shared<W3AppExpr>(n);
}

W3AppExprPtr W3Expr::mkBoolVar(const std::string &n){
  return std::make_shared<W3AppExpr>(n);
}

W3AppExprPtr W3Expr::mkIntArrayVar(const std::string &n){
  return std::make_shared<W3AppExpr>(n);
}

W3AppExprPtr W3Expr::mkEq(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("=",e1,e2);
}

W3AppExprPtr W3Expr::mkDiseq(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("<>",e1,e2);
}

W3AppExprPtr W3Expr::mkLt(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("<",e1,e2);
}

W3AppExprPtr W3Expr::mkLe(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("<=",e1,e2);
}

W3AppExprPtr W3Expr::mkGt(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>(">",e1,e2);
}

W3AppExprPtr W3Expr::mkGe(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>(">=",e1,e2);
}

W3AppExprPtr W3Expr::mkSum(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("+",e1,e2);
}

W3AppExprPtr W3Expr::mkSum(const std::vector<W3ExprPtr> &es){
  return std::make_shared<W3AppExpr>("+",es);
}

W3AppExprPtr W3Expr::mkSub(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("-",e1,e2);
}

W3AppExprPtr W3Expr::mkSub(const std::vector<W3ExprPtr> &es){
  return std::make_shared<W3AppExpr>("-",es);
}

W3AppExprPtr W3Expr::mkMul(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("*",e1,e2);
}

W3AppExprPtr W3Expr::mkMul(const std::vector<W3ExprPtr> &es){
  return std::make_shared<W3AppExpr>("*",es);
}

W3AppExprPtr W3Expr::mkDiv(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("div",e1,e2);
}

W3AppExprPtr W3Expr::mkMod(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3AppExpr>("mod",e1,e2);
}

W3ConnExprPtr W3Expr::mkAnd(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3ConnExpr>(W3ConnExpr::W3And,e1,e2);
}

W3ConnExprPtr W3Expr::mkAnd(const std::vector<W3ExprPtr> &es){
  return std::make_shared<W3ConnExpr>(W3ConnExpr::W3And, es);
}

W3ConnExprPtr W3Expr::mkOr(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3ConnExpr>(W3ConnExpr::W3Or,e1,e2);
}

W3ConnExprPtr W3Expr::mkOr(const std::vector<W3ExprPtr> &es){
  return std::make_shared<W3ConnExpr>(W3ConnExpr::W3Or,es);
}

W3ConnExprPtr W3Expr::mkImpl(W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3ConnExpr>(W3ConnExpr::W3Implies,e1,e2);
}

W3NotExprPtr W3Expr::mkNot(W3ExprPtr e){
  return std::make_shared<W3NotExpr>(e);
}

W3QuantExprPtr W3Expr::mkUQuant(const std::vector<std::string> &_int_vars, 
                                const std::vector<std::string> &_bool_vars, 
                                W3ExprPtr _e){
  return std::make_shared<W3QuantExpr>(_int_vars,_bool_vars,_e,W3QuantExpr::W3ForAll);
}

W3QuantExprPtr W3Expr::mkUQuant(const std::vector<std::string> &_int_vars, 
                                const std::vector<std::string> &_bool_vars, 
                                const std::vector<std::string> &_int_to_int_vars, 
                                W3ExprPtr _e){
  return std::make_shared<W3QuantExpr>(_int_vars,_bool_vars,_int_to_int_vars,_e,W3QuantExpr::W3ForAll);
}

W3QuantExprPtr W3Expr::mkEQuant(const std::vector<std::string> &_int_vars, 
                                const std::vector<std::string> &_bool_vars, 
                                W3ExprPtr _e){
  return std::make_shared<W3QuantExpr>(_int_vars,_bool_vars,_e,W3QuantExpr::W3Exists);
}


W3IfExprPtr W3Expr::mkIte(W3ExprPtr cond, W3ExprPtr e1, W3ExprPtr e2){
  return std::make_shared<W3IfExpr>(cond,e1,e2);
}


W3ArrayExprPtr W3Expr::mkArrayAccess(W3ExprPtr name, W3ExprPtr index){
  return std::make_shared<W3ArrayExpr>(name,index);
}

W3ArrayUpdExprPtr W3Expr::mkArrayUpdate(W3ExprPtr name, W3ExprPtr index, W3ExprPtr value){
  return std::make_shared<W3ArrayUpdExpr>(name, index, value);
}

void W3Theory::add(W3DeclPtr d){
  decls.push_back(d);
}

void W3Theory::prettyprint(llvm::raw_ostream &os){
  os << "theory" << " " << this -> name << "\n\n";
  for(W3DeclPtr d : this -> decls){
    os << "    ";
    d -> prettyprint(os);
    os << "\n\n";
  }
  os << "end";
}

void W3Goal::prettyprint(llvm::raw_ostream &os){
  os << "goal" << " " << "G" << this -> name << ": ";
  e -> prettyprint(os);
}

void W3Use::prettyprint(llvm::raw_ostream &os){
  os << "use" << " " << ((op == this -> W3Import)?"import":"export")
     << " " << this -> theory;
}

void W3LitExpr::prettyprint(llvm::raw_ostream &os){
  switch(this -> type){
    case W3LitExpr::W3Int: {
      if(this -> value.W3Int < 0)
        os << "(" + std::to_string(this -> value.W3Int) + ")";
      else
        os << std::to_string(this -> value.W3Int);
      break;
    }case W3LitExpr::W3UInt: {
      os << std::to_string(this -> value.W3UInt);
      break;
    }case W3LitExpr::W3Real: {
      /*
      ATTENTION to this! I'm not sure if the format of floating
      points is the same
      */
      os << this -> value.W3Real;
      break;
    }case W3LitExpr::W3Bool: {
      if(this -> value.W3Bool)
        os << "true";
      else
        os << "false";
      break;
    }
  }
}

void W3LitExpr::toSMTLib2(llvm::raw_ostream & os){
  switch(this -> type){
    case W3LitExpr::W3Int: {
      if(this -> value.W3Int < 0)
        os << "(" << "- " + std::to_string(- (this -> value.W3Int)) << ")";
      else
        os << std::to_string(this -> value.W3Int);
      break;
    }case W3LitExpr::W3UInt: {
      os << std::to_string(this -> value.W3UInt);
      break;
    }case W3LitExpr::W3Real: {
      /*
      ATTENTION to this! I'm not sure if the format of floating
      points is the same
      */
      os << this -> value.W3Real;
      break;
    }case W3LitExpr::W3Bool: {
      if(this -> value.W3Bool)
        os << "true";
      else
        os << "false";
      break;
    }
  }
}

void W3AppExpr::prettyprint(llvm::raw_ostream &os){
  if(exprs.empty()){
    os << this -> name;
    return;
  }

  std::vector<W3ExprPtr>::iterator it = this -> exprs.begin();

  os << "(";
  (*it) -> prettyprint(os);
  os << ")";
  
  ++it;
  for(;it != exprs.end(); ++it){
    os << " " << this -> name << " ";
    os << "(";
    (*it) -> prettyprint(os);
    os << ")";
  }
}

void W3AppExpr::toSMTLib2(llvm::raw_ostream & os){
  if(exprs.empty()){
    os << this -> name;
    return;
  }

  os << "(" << this -> name;
  
  for(W3ExprPtr e : this -> exprs){
    os << " ";
    e -> toSMTLib2(os);
  }

  os << ")";
}

std::string W3ConnExpr::connToString(){
  switch(conn){
    case W3And:{
      return "/\\";
      break;
    }case W3AsymAnd:{
      return "&&";
      break;
    }case W3Or:{
      return "\\/";
      break;
    }case W3AsymOr:{
      return "||";
      break;
    }case W3Implies:{
      return "->";
      break;
    }case W3Iff:{
      return "<->";
      break;
    }default:{
      std::cout << "Unknown operator in Why3 expression";
      exit(1);
    }
  }
}

void W3ConnExpr::prettyprint(llvm::raw_ostream &os){
  std::vector<W3ExprPtr>::iterator it = this -> exprs.begin();

  os << "(";
  (*it) -> prettyprint(os);
  os << ")";

  ++it;
  for(;it != exprs.end(); ++it){
    os << " " << connToString() << " ";
    os << "(";
    (*it) -> prettyprint(os);
    os << ")";
  }
}

std::string W3ConnExpr::connToStringSMTLib(){
  switch(conn){
    case W3And:{
      return "and";
      break;
    }case W3Or:{
      return "or";
      break;
    }case W3Implies:{
      return "=>";
      break;
    }case W3Iff:{
      return "=";
      break;
    }default:{
      std::cout << "Unknown operator in Why3 expression";
      exit(1);
    }
  }
}

void W3ConnExpr::toSMTLib2(llvm::raw_ostream & os){
  std::vector<W3ExprPtr>::iterator it = this -> exprs.begin();

  os << "(" << connToStringSMTLib();

  for(W3ExprPtr e : this -> exprs){
    os << " ";
    e -> toSMTLib2(os);
  }
  os << ")";
}

void W3NotExpr::prettyprint(llvm::raw_ostream &os){
  os << "not (";
  expr -> prettyprint(os);
  os << ")";
}

void W3NotExpr::toSMTLib2(llvm::raw_ostream & os){
  os << "(";
  os << "not" << " ";
  expr -> toSMTLib2(os);
  os << ")";
}

void W3QuantExpr::prettyprint(llvm::raw_ostream &os){
  os << ((this -> quant == W3QuantExpr::W3ForAll)?"forall":"exists") << " ";

  for(std::string t : int_vars){
    os << t;
    os << " ";
  }
  if(!int_vars.empty()){
    os << ":" << "int";
    if(!bool_vars.empty() || !int_to_int_vars.empty())
      os << "," << " ";
  }

  for(std::string t : bool_vars){
    os << t;
    os << " ";
  }
  if(!bool_vars.empty()){
    os << ":" << "bool";
    if(!int_to_int_vars.empty())
      os << "," << " ";
  }

  for(std::string t : int_to_int_vars){
    os << t;
    os << " ";
  }
  if(!int_to_int_vars.empty())
    os << ":" << "array int";

  os << "." << " ";

  e -> prettyprint(os);
}

void W3QuantExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3IfExpr::prettyprint(llvm::raw_ostream &os){
  os << "if" << " ";
  cond -> prettyprint(os);
  os << " " << "then" << " ";
  e1 -> prettyprint(os);
  os << " " << "else" << " ";
  e2 -> prettyprint(os);
}

void W3IfExpr::toSMTLib2(llvm::raw_ostream & os){
  os << "(";
  os << "ite" << " ";
  cond -> toSMTLib2(os);
  os << " ";
  e1 -> toSMTLib2(os);
  os << " ";
  e2 -> toSMTLib2(os);
  os << ")";
}

void W3ArrayUpdExpr::prettyprint(llvm::raw_ostream &os){
  name -> prettyprint(os);
  os << "[";
  index -> prettyprint(os);
  os << " <- ";
  e -> prettyprint(os); 
  os << "]";
}

void W3ArrayUpdExpr::toSMTLib2(llvm::raw_ostream & os){
  os << "(";
  os << "store" << " ";
  name -> toSMTLib2(os);
  os << " ";
  index -> toSMTLib2(os);
  os << " ";
  e -> toSMTLib2(os);
  os << ")";
}

void W3ArrayExpr::prettyprint(llvm::raw_ostream &os){
  name -> prettyprint(os);
  os << "[";
  index -> prettyprint(os);
  os << "]";
}

void W3ArrayExpr::toSMTLib2(llvm::raw_ostream & os){
  os << "(";
  os << "select" << " ";
  name -> toSMTLib2(os);
  os << " ";
  index -> toSMTLib2(os);
  os << ")";
}

void W3LetExpr::prettyprint(llvm::raw_ostream &os){

}

void W3LetExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3MatchExpr::prettyprint(llvm::raw_ostream &os){

}

void W3MatchExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3FieldExpr::prettyprint(llvm::raw_ostream &os){

}

void W3FieldExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3RecordExpr::prettyprint(llvm::raw_ostream &os){

}

void W3RecordExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3RecordUpdateExpr::prettyprint(llvm::raw_ostream &os){

}

void W3RecordUpdateExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3CastExpr::prettyprint(llvm::raw_ostream &os){

}

void W3CastExpr::toSMTLib2(llvm::raw_ostream & os){
  
}

void W3LabeledExpr::prettyprint(llvm::raw_ostream &os){

}

void W3LabeledExpr::toSMTLib2(llvm::raw_ostream & os){
  
}