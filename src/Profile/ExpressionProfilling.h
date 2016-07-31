/**
 * Profiling.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/06/02
 * @copyright : NII 2015
 */

#ifndef _PROFILING_H
#define _PROFILING_H

class Profiling {
public:
  long true_exps;
  long false_exps;
  long num_exps;
  long int_var_exps;
  long bool_var_exps;
  long bool_vars;
  long int_vars;
  long comparison_ops;
  long not_ops;
  long and_ops;
  long or_ops;
  long impl_ops;
  long xor_ops;
  long sum_ops;
  long sub_ops;
  long mul_ops;
  long ite_ops;
  long app_ops;
  long update_ops;
  long div_ops;
  long mod_ops;
  long parse_exps;

  Profiling();
};

#endif