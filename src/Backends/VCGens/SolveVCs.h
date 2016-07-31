/**
 * SolveVCs.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/23
 * @copyright : NII 2015
 */

#ifndef _SOLVEVCS_H
#define _SOLVEVCS_H

#include <iostream>
#include <chrono>

#include "../../Logic/YicesSolver.h"
#include "../../Logic/Why3.h"
#include "../../Logic/Why3Gen.h"
#include "../../Logic/SMTLib2.h"
#include "Utils/ListExpr.h"

class SolveVCs{
  ListExpr *exprs;
  YicesSolver *solver;
  unsigned long valid;
  unsigned long invalid;
  unsigned long undef;
  std::string model;
  double duration;

public:
  SolveVCs(ListExpr *exps);
  ~SolveVCs();

  unsigned long getValid();
  unsigned long getInvalid();
  unsigned long getUndef();
  Profiling getProfiling();
  double getDuration();

  void checkVCValidity();

  void checkInWhy3();
  void generateSMTLib2();

  void toFile();

  void printInfo(raw_ostream &OS);
};

#endif