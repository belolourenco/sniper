/**
 * PairListExpr.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2015/04/23
 * @copyright : NII 2015
 */

#include "PairListExpr.h"

PairListExpr::PairListExpr()
  :enc(),prop(){}

PairListExpr::PairListExpr(const ListExpr &e)
  :enc(e),prop(){}

PairListExpr::PairListExpr(const ListExpr &e, const ListExpr &p)
  :enc(e), prop(p){}

PairListExpr::~PairListExpr(){}

const ListExpr &PairListExpr::getE() const{
  return enc;
}

const ListExpr &PairListExpr::getP() const{
  return prop;
}

ListExpr &PairListExpr::getP(){
  return prop;
}

void PairListExpr::addToE(const ExprPtr &e){
  enc.add(e);
}

void PairListExpr::addToP(const ExprPtr &e){
  prop.add(e);
}


void PairListExpr::addToE(const ListExpr &l){
  enc.add(l);
}

void PairListExpr::addToP(const ListExpr &l){
  prop.add(l);
}

unsigned PairListExpr::getSizeE() const{
  return enc.size();
}

unsigned PairListExpr::getSizeP() const{
  return prop.size();
}

bool PairListExpr::isEmpty() const{
  return (!getSizeE() && !getSizeP());
} 

bool PairListExpr::isEEmpty() const{
  return (!getSizeE());
}


bool PairListExpr::isPEmpty() const{
  return (!getSizeP());
}

void PairListExpr::andInAllE(const ExprPtr &e){
  enc.andInAll(e);
}

void PairListExpr::andInAllP(const ExprPtr &e){
  prop.andInAll(e);
}

void PairListExpr::implyInAllE(const ExprPtr &e){
  enc.implInAll(e);
}

void PairListExpr::ImplyInAllP(const ExprPtr &e){
  prop.implInAll(e);
}


void PairListExpr::merge(const PairListExpr &pl){
  enc.add(pl.getE());
  prop.add(pl.getP());
}

void PairListExpr::print(raw_ostream &OS) const{
  OS << "\n###################\n";
  OS << "Program Encoding:\n";
  enc.print(OS);
  OS << "\nProgram Properties\n";
  prop.print(OS);
  OS << "\n###################\n";
}

void PairListExpr::printInfo(raw_ostream &OS) const{
  OS << "\n###################\n";
  OS << "Program Encoding";
  enc.printInfo(OS);
  OS << "\nProgram Properties";
  prop.printInfo(OS);
  OS << "\n###################\n";
}