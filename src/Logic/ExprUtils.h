/**
 * ExprUtils.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/12/30
 * @copyright : NII 2015
 */

#ifndef EXPRUTILS
#define EXPRUTILS

#include "Expression.h"

class ExprUtils {
  static const bool ignore_simplifications = false;
public:
  static ExprPtr mkAnd(ExprPtr e1, ExprPtr e2);
  static ExprPtr mkOr(ExprPtr e1, ExprPtr e2);
  static ExprPtr mkImpl(ExprPtr e1, ExprPtr e2);
  static ExprPtr mkNeg(ExprPtr e);

};

#endif