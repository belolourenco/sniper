/**
 * ListExpr.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/22
 * @copyright : NII 2015
 */

#include "ListExpr.h"

ListExpr::ListExpr()
  :exprs(){}

ListExpr::ListExpr(const ExprPtr &e)
  :exprs(1,e){}

ListExpr::ListExpr(const std::vector<ExprPtr> &v)
  :exprs(v){}


ListExpr::ListExpr(const ListExpr &l){
  for(ExprPtr e : l.getExprs())
    exprs.push_back(e);
}

ListExpr::~ListExpr(){}

const std::vector<ExprPtr> &ListExpr::getExprs() const{
  return exprs;
}

std::vector<ExprPtr> ListExpr::getExprs(){
  return exprs;
}

void ListExpr::add(const ExprPtr &e){
  exprs.push_back(e);
}

void ListExpr::add(const std::vector<ExprPtr> &v){
  exprs.insert(exprs.end(),v.begin(),v.end());
}

void ListExpr::add(const ListExpr &l){
  std::vector<ExprPtr> v = l.getExprs();
  exprs.insert(exprs.end(),v.begin(),v.end());
}

void ListExpr::addBefore(const ExprPtr &e){
  exprs.insert(exprs.begin(), e);
}

void ListExpr::addBefore(const std::vector<ExprPtr> &v){
  exprs.insert(exprs.begin(), v.begin(), v.end());
}

void ListExpr::addBefore(const ListExpr &l){
  std::vector<ExprPtr> v = l.getExprs();
  exprs.insert(exprs.begin(),v.begin(),v.end());
}

unsigned ListExpr::size() const{
  return exprs.size();
}

void ListExpr::andInAll(const ExprPtr &e){
  if(exprs.size() == 0){
    exprs.push_back(e);
  }else{
    std::vector<ExprPtr>::iterator it = exprs.begin();
    for(; it != exprs.end(); ++it){
      *it = Expression::mkAnd(*it,e);
    }
  }
}

void ListExpr::implInAll(const ExprPtr &e){
  std::vector<ExprPtr>::iterator it = exprs.begin();
  for(; it != exprs.end(); ++it){
    *it = Expression::mkImpl(*it,e);
  }
}

void ListExpr::negateAll(){
  std::vector<ExprPtr>::iterator it = exprs.begin();
  for(; it != exprs.end(); ++it){
    *it = Expression::mkNot(*it);
  }
}

ExprPtr ListExpr::conjunction() const{
  if(exprs.size() == 0)
    return Expression::mkTrue();
  else
    return Expression::mkAnd(exprs);
}

void ListExpr::print(raw_ostream &OS) const{
  OS << "\n";
  for(ExprPtr e : exprs){
    e -> print(OS);
    OS << "\n";
  }
}

void ListExpr::printInfo(raw_ostream &OS) const{
  OS << "\n\t Number of Expressions: " << exprs.size();
}