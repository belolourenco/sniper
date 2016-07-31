/**
 * Profiling.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/06/02
 * @copyright : NII 2015
 */

#include "ExpressionProfilling.h"

Profiling::Profiling(){
  true_exps = 0;
  false_exps = 0;
  num_exps = 0;
  int_var_exps = 0;
  bool_var_exps = 0;
  bool_vars = 0;
  int_vars = 0;
  comparison_ops = 0;
  not_ops = 0;
  and_ops = 0;
  or_ops = 0;
  xor_ops = 0;
  sum_ops = 0;
  sub_ops = 0;
  mul_ops = 0;
  ite_ops = 0;
  app_ops = 0;
  update_ops = 0;
  div_ops = 0;
  mod_ops = 0;
  parse_exps = 0;
}


