/**
 * Why3Gen.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/04/20
 * @copyright : NII 2015
 */

#ifndef _WHY3GEN_H
#define _WHY3GEN_H

#include <vector>
// #include <algorithm>

#include "Why3.h"
#include "Expression.h"

#include "../Profile/ExpressionProfilling.h"

class Why3Gen{

private:
    unsigned counter;
    unsigned vcCounter;
    std::vector<std::string> int_vars;
    std::vector<std::string> bool_vars;
    std::vector<std::string> int_to_int_vars;

    W3Theory theory;

public:
    Why3Gen();
    ~Why3Gen();

    Profiling p;

    void init();
    void addToTheory(ExprPtr e);
    void addToTheory(const std::string &name, ExprPtr e);
    void addToTheory(const std::vector<ExprPtr> &es);
    const W3Theory &getTheory();

    W3ExprPtr encodeAsGoal(ExprPtr e);
    W3ExprPtr makeWhy3Expr(ExprPtr e);

    void prettyprintTheory(raw_ostream &os);
};

#endif