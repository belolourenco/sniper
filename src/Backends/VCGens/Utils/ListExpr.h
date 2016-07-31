/**
 * ListExpr.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/22
 * @copyright : NII 2015
 */

#ifndef _LISTEXPR_H
#define _LISTEXPR_H

#include <vector>

#include "../../../Logic/Expression.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

/*
Container for a list of expressions. Useful methods such as the andInAll, implInAll
and negateAll
*/
class ListExpr{
  std::vector<ExprPtr> exprs;

public:
  ListExpr();
  ListExpr(const ExprPtr &e);
  ListExpr(const std::vector<ExprPtr> &v);
  ListExpr(const ListExpr &l);
  ~ListExpr();

  const std::vector<ExprPtr> &getExprs() const;
        std::vector<ExprPtr> getExprs();

  void add(const ExprPtr &e);
  void add(const std::vector<ExprPtr> &v);
  void add(const ListExpr &l);

  void addBefore(const ExprPtr &e);
  void addBefore(const std::vector<ExprPtr> &v);
  void addBefore(const ListExpr &l);

  unsigned size() const;

  /*
  Iterates through the vector of expressions and it makes the conjunction
  of the current expression with \e
  */
  void andInAll(const ExprPtr &e);
  /*
  Iterates through the vector of expressions and it makes the implication
  of the current expression with \e
  */
  void implInAll(const ExprPtr &e);
  /*
  Iterates through the vector of expressions negating each expression
  */
  void negateAll();
  
  ExprPtr conjunction() const;

  void print(raw_ostream &OS) const;
  void printInfo(raw_ostream &OS) const;
};

#endif