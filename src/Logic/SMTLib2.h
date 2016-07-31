/**
 * SMTLib2.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/04/26
 * @copyright : NII 2015
 */

#ifndef _SMTLIB2_H
#define _SMTLIB2_H

#include <iostream>
#include <vector>
// #include <algorithm>

#include "Why3.h"
#include "Expression.h"

#include "../Profile/ExpressionProfilling.h"

class SMTLib2Gen{

private:
    unsigned counter;
    std::vector<std::string> int_vars;
    std::vector<std::string> bool_vars;
    std::vector<std::string> int_to_int_vars;

    std::vector<W3ExprPtr> exprs;

public:
    SMTLib2Gen();
    ~SMTLib2Gen();

    Profiling p;

    void init();
    void encode(ExprPtr e);

    void prettyprint(raw_ostream &os);

    W3ExprPtr makeWhy3Expr(ExprPtr e);
};

#endif