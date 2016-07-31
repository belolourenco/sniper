/**
 * ExprUtils.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/30
 * @copyright : NII 2015
 */

#include "ExprUtils.h"

ExprPtr ExprUtils::mkAnd(ExprPtr e1, ExprPtr e2){
  if(ignore_simplifications)
    return Expression::mkAnd(e1,e2);

  if(e1 -> getOpCode() == Expression::False)
    return e1;
  if(e2 -> getOpCode() == Expression::False)
    return e2;
  if(e1 -> getOpCode() == Expression::True)
    return e2;
  if(e2 -> getOpCode() == Expression::True)
    return e1;
  return Expression::mkAnd(e1,e2);
}

ExprPtr ExprUtils::mkOr(ExprPtr e1, ExprPtr e2){
  if(ignore_simplifications)
    return Expression::mkOr(e1,e2);

  if(e1 -> getOpCode() == Expression::True)
    return e1;
  if(e2 -> getOpCode() == Expression::True)
    return e2;
  if(e1 -> getOpCode() == Expression::False)
    return e2;
  if(e2 -> getOpCode() == Expression::False)
    return e1;

  if(e1 -> getOpCode() == Expression::Not){
    NotExprPtr ne = std::static_pointer_cast<NotExpression>(e1);
    if(ne -> get() == e2)
      return Expression::mkTrue();
  }

  if(e2 -> getOpCode() == Expression::Not){
    NotExprPtr ne = std::static_pointer_cast<NotExpression>(e2);
    if(ne -> get() == e1)
      return Expression::mkTrue();
  }

  return Expression::mkOr(e1,e2);
}

ExprPtr ExprUtils::mkImpl(ExprPtr e1, ExprPtr e2){
  if(ignore_simplifications)
    return Expression::mkImpl(e1,e2);

  if(e2 -> getOpCode() == Expression::True)
    return e2;
  if(e1 -> getOpCode() == Expression::False)
    return Expression::mkTrue();
  if(e1 -> getOpCode() == Expression::True)
    return e2;
  return Expression::mkImpl(e1,e2);
}

ExprPtr ExprUtils::mkNeg(ExprPtr e){
  if(ignore_simplifications)
    return Expression::mkNot(e);
  
  if(e -> getOpCode() == Expression::Not){
    NotExprPtr e1 = std::static_pointer_cast<NotExpression>(e);
    return e1 -> get();
  }

  return Expression::mkNot(e);
}
