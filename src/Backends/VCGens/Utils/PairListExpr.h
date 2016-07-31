/**
 * PairListExpr.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/23
 * @copyright : NII 2015
 */

#ifndef _PAIRLISTEXPR_H
#define _PAIRLISTEXPR_H
 
#include "ListExpr.h"


/*
Container for two set of expressions
*/
class PairListExpr{
  ListExpr enc;
  ListExpr prop;

public:
  PairListExpr();
  PairListExpr(const ListExpr &e);
  PairListExpr(const ListExpr &e, const ListExpr &p);
  ~PairListExpr();

  const ListExpr &getE() const;
  const ListExpr &getP() const;
  // Be aware that the it will be possible to change the
  // internal state of an instance with the returned reference
        ListExpr &getP();

  void addToE(const ExprPtr &e);
  void addToP(const ExprPtr &e);
  void addToE(const ListExpr &l);
  void addToP(const ListExpr &l);

  unsigned getSizeE() const;
  unsigned getSizeP() const;

  bool isEmpty() const;
  bool isEEmpty() const;
  bool isPEmpty() const;

  void andInAllE(const ExprPtr &e);
  void andInAllP(const ExprPtr &e);
  void implyInAllE(const ExprPtr &e);
  void ImplyInAllP(const ExprPtr &e);

  /*
  It adds the elements of p to E and P
  */
  void merge(const PairListExpr &pl);

  void print(raw_ostream &OS) const;
  void printInfo(raw_ostream &OS) const;
};

#endif