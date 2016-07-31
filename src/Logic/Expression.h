/**
 * \file Expression.h
 *
 * ----------------------------------------------------------------------
 *                SNIPER : Automatic Fault Localization 
 *
 * Copyright (C) 2016 Si-Mohamed LAMRAOUI
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program (see LICENSE.TXT).  
 * If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------
 *
 * \author Si-Mohamed Lamraoui
 * \date   26 January 2015
 */


#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/DebugInfo.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

class Expression;
class SingleExpression;
class TrueExpression;
class FalseExpression;
class UInt32NumExpression;
class SInt32NumExpression;
class BoolVarExpression;
class IntVarExpression;
class IntToIntVarExpression;
class ToParseExpression;
class BinaryExpression;
class TrinaryExpression;
class UnaryExpression;
class GtExpression;
class GeExpression;
class LeExpression;
class LtExpression;
class DiseqExpression;
class EqExpression;
class NotExpression;
class AndExpression;
class OrExpression;
class ImplExpression;
class SumExpression;
class SubExpression;
class MulExpression;
class IteExpression;
class AppExpression;
class UpdateExpression;
class DivExpression;
class ModExpression;
class XorExpression;

typedef std::shared_ptr<Expression>             ExprPtr;
typedef std::shared_ptr<SingleExpression>       SingleExprPtr;
typedef std::shared_ptr<TrueExpression>         TrueExprPtr;
typedef std::shared_ptr<FalseExpression>        FalseExprPtr;
typedef std::shared_ptr<UInt32NumExpression>    UInt32NumExprPtr;
typedef std::shared_ptr<SInt32NumExpression>    SInt32NumExprPtr;
typedef std::shared_ptr<BoolVarExpression>      BoolVarExprPtr;
typedef std::shared_ptr<IntVarExpression>       IntVarExprPtr;
typedef std::shared_ptr<IntToIntVarExpression>  IntToIntVarExprPtr;
typedef std::shared_ptr<ToParseExpression>      ToParseExprPtr;
typedef std::shared_ptr<BinaryExpression>       BinaryExprPtr;
typedef std::shared_ptr<TrinaryExpression>      TrinaryExprPtr;
typedef std::shared_ptr<UnaryExpression>        UnaryExprPtr;
typedef std::shared_ptr<GtExpression>           GtExprPtr;
typedef std::shared_ptr<GeExpression>           GeExprPtr;
typedef std::shared_ptr<LeExpression>           LeExprPtr;
typedef std::shared_ptr<LtExpression>           LtExprPtr;
typedef std::shared_ptr<DiseqExpression>        DiseqExprPtr;
typedef std::shared_ptr<EqExpression>           EqExprPtr;
typedef std::shared_ptr<NotExpression>          NotExprPtr;
typedef std::shared_ptr<AndExpression>          AndExprPtr;
typedef std::shared_ptr<OrExpression>           OrExprPtr;
typedef std::shared_ptr<ImplExpression>         ImplExprPtr;
typedef std::shared_ptr<SumExpression>          SumExprPtr;
typedef std::shared_ptr<SubExpression>          SubExprPtr;
typedef std::shared_ptr<MulExpression>          MulExprPtr;
typedef std::shared_ptr<IteExpression>          IteExprPtr;
typedef std::shared_ptr<AppExpression>          AppExprPtr;
typedef std::shared_ptr<UpdateExpression>       UpdateExprPtr;
typedef std::shared_ptr<DivExpression>          DivExprPtr;
typedef std::shared_ptr<ModExpression>          ModExprPtr;
typedef std::shared_ptr<XorExpression>          XorExprPtr;

/**
 * Pretty printer for expressions.
 */
std::ostream& operator<<(std::ostream& os, const ExprPtr e);

/**
 * \class Expression
 *
 * \brief Parent class for expressions.
 * 
 * An expression, also called clause or constraint, is 
 * representated by an abstract syntax tree.
 */
class Expression {
    
public:
     /**@{
      * Op codes */
    static const unsigned True          = 1;
    static const unsigned False         = 2;
    static const unsigned UInt32Num     = 3;
    static const unsigned SInt32Num     = 4;
    static const unsigned BoolVar       = 5;
    static const unsigned IntVar        = 6;
    static const unsigned IntToIntVar   = 7;
    static const unsigned ToParse       = 8;
    static const unsigned Gt            = 9;
    static const unsigned Ge            = 10;
    static const unsigned Le            = 11;
    static const unsigned Lt            = 12;
    static const unsigned Diseq         = 13;
    static const unsigned Eq            = 14;
    static const unsigned Not           = 15;
    static const unsigned And           = 16;
    static const unsigned Or            = 17;
    static const unsigned Sum           = 18;
    static const unsigned Sub           = 19;
    static const unsigned Mul           = 20;
    static const unsigned Ite           = 21;
    static const unsigned App           = 22;
    static const unsigned Update        = 23;
    static const unsigned Div           = 24;
    static const unsigned Mod           = 25;
    static const unsigned Xor           = 26;
    static const unsigned Impl          = 27;
    static const unsigned Binary        = 28;
    static const unsigned Trinary       = 29;
    /**@}*/

private:
    /**
     * Unique ID number to be assigned to each expression.
     */
    static unsigned ID;
    const unsigned currentID;
    /**
     * True if the expresssion is soft (retractable).
     */
    bool soft;
    /**
     * LLVM instruction from which the expression was encoded.
     * In some cases, this variable can be null.
     */
    llvm::Instruction *instruction;
    /**
     * Line number in the original source code of the LLVM expression 
     * from which the expression was encoded.
     */
    unsigned line;
protected:
    /**
     * Number of integer variables created.
     */
    static unsigned NbIntVariables;
    /**
     * Number of Boolean variables created.
     */
    static unsigned NbBoolVariables;
protected:
    /**
     * Default constructor.
     */
    Expression()
    : currentID(ID++), soft(true), instruction(NULL), line(0) { }
    /**
     * Destructor.
     */
    virtual ~Expression() { }
    
public:
    /**
     * Return an expression representing \a true.
     */
    static TrueExprPtr mkTrue();
    /**
     * Return an expression representing \a false.
     */
    static FalseExprPtr mkFalse();
    /**
     * Return an expression representing the given unsigned integer.
     */
    static UInt32NumExprPtr mkUInt32Num(unsigned value);
    /**
     * Return an expression representing the given signed integer.
     */
    static SInt32NumExprPtr mkSInt32Num(int value);
    /**
     * Return a new boolean variable expression (instance).
     */
    static BoolVarExprPtr mkBoolVar(std::string name);
    /**
     * Return a new integer variable expression (instance).
     */
    static IntVarExprPtr mkIntVar(std::string name);
    /**
     * Return a new function variable expression (instance).
     */
    static IntToIntVarExprPtr mkIntToIntVar(std::string name);
    /**
     * Not implemented.
     */
    static ToParseExprPtr parseExpression(std::string s);
    /**
     * Return an expression representing \a (not e1).
     */
    static NotExprPtr mkNot(ExprPtr e1);
    /**
     * Return an expression representing \a e1 = e2.
     */
    static EqExprPtr mkEq(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 != e2.
     */
    static DiseqExprPtr mkDiseq(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 < e2.
     */
    static LtExprPtr mkLt(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 <= e2.
     */
    static LeExprPtr mkLe(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 > e2.
     */
    static GtExprPtr mkGt(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 >= e2.
     */
    static GeExprPtr mkGe(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 and e2.
     */
    static AndExprPtr mkAnd(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a es_0 and es_1 ... and es_n-1.
     */
    static AndExprPtr mkAnd(std::vector<ExprPtr> es);
    /**
     * Return an expression representing \a e1 or e2.
     */
    static OrExprPtr mkOr(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a es_0 or es_1 ... or es_n-1.
     */
    static OrExprPtr mkOr(std::vector<ExprPtr> es);
    /**
     * Return an expression representing \a e1 xor e2.
     */
    static XorExprPtr mkXor(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a es_0 xor es_1 ... xor es_n-1.
     */
    static XorExprPtr mkXor(std::vector<ExprPtr> es);
    /**
     * Return an expression representing \a es_1 impl es_2.
     */
    static ImplExprPtr     mkImpl(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing (IF econd ethen eelse).
     */
    static IteExprPtr mkIte(ExprPtr econd, ExprPtr ethen, ExprPtr eelse);
    /**
     * Return an expression representing \a e1 + e2.
     */
    static SumExprPtr mkSum(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 + e2 (signed).
     *
     * Signed addition with overlow. 
     * Bound: -2^(\a nbBit-1) <= x <= 2^(\a nbBit-1).
     */
    static ExprPtr mkSSum(ExprPtr e1, ExprPtr e2, unsigned nbBit);
    /**
     * Return an expression representing \a e1 + e2 (unsigned).
     *
     * Unsigned addition with overlow.
     * Bound: 0 <= u <= 2^(nbBit).
     */
    static ExprPtr mkUSum(ExprPtr e1, ExprPtr e2, unsigned nbBit);
    /**
     * Return an expression representing \a e1 - e2.
     */
    static SubExprPtr mkSub(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 * e2.
     */
    static MulExprPtr mkMul(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 / e2.
     */
    static DivExprPtr mkDiv(ExprPtr e1, ExprPtr e2);
    /**
     * Return an expression representing \a e1 % e2.
     */
    static ModExprPtr mkMod(ExprPtr e1, ExprPtr e2);
    /**
     * Return a function application term \a (e1 e2).
     */
    static AppExprPtr mkApp(ExprPtr e1, ExprPtr e2);
    /**
     * Build a function update term \a (update f (arg) v).
     */
    static UpdateExprPtr mkFunctionUpdate(ExprPtr f, ExprPtr arg, ExprPtr v);
    /**
     * Return an expression representing \a left op right.
     */
    static ExprPtr mkOp(ExprPtr left, ExprPtr right, llvm::CmpInst::Predicate op);
    /**
     * Return an expression representing \a left i.op right.
     */
    static ExprPtr mkOp(ExprPtr left, ExprPtr right, llvm::Instruction *i);
    
    static BinaryExprPtr   mkBinExpr(ExprPtr e1, ExprPtr e2);
    static TrinaryExprPtr  mkTrinExpr(ExprPtr e1, ExprPtr e2, ExprPtr e3);

    /**
     * Return true if \a e1 is equal to \a e2, false otherwise.
     */
    friend bool operator== (ExprPtr e1, ExprPtr e2);
    /**
     * Return true if \a e1 is not equal to \a e2, false otherwise.
     */
    friend bool operator!= (ExprPtr e1, ExprPtr e2);
    
    /**
     * Return the opposite opperator of \a op.
     */
    static llvm::CmpInst::Predicate negateOp(llvm::CmpInst::Predicate op);
    /**
     * Return an expression representing the LLVM value \a v.
     */
    static ExprPtr getExprFromValue(llvm::Value *v);
    
    /**
     * Return the number of integer variables created.
     */
    static unsigned getNbIntVariables() {
        return NbIntVariables;
    }
    /**
     * Return the number of boolean variables created.
     */
    static unsigned getNbBoolVariables() {
        return NbBoolVariables;
    }
    /**
     * Return \a true if the expresseion is soft (retractable), 
     * false otherwise.
     */
    bool isSoft() {
        return soft;
    }
    /**
     * Return \a true if the expresseion is hard (not retractable), 
     * false otherwise.
     */
    bool isHard() {
        return !soft;
    }
    /**
     * Assign a line number (source code) to this expression.
     */
    void setLine(unsigned l) {
        line = l;
    }
    /**
     * Set this expression as hard (not retractable).
     */
    void setHard() {
        soft = false;
    }
    /**
     * Set this expression as soft (retractable).
     */
    void setSoft() {
        unsigned l = 0;
        Instruction *I = getInstruction();
        if (I) {
            if (MDNode *N = I->getMetadata("dbg")) {
                DILocation Loc(N);
                l = Loc.getLineNumber();
                setLine(l);
            }
        }
        setLine(l);
        soft = true;
    }
    /**
     * Return the line number in the original source code of the 
     * LLVM expression from which the expression was encoded.
     */
    unsigned getLine() {
        return line;
    }
    /**
     * Return the LLVM instruction from which the expression was encoded.
     * If no instruction was assigned to this expression,
     * the function returns null.
     */
    llvm::Instruction* getInstruction() {
        return instruction;
    }
    /**
     * Set the LLVM instruction from which the expression was encoded.
     */
    void setInstruction(llvm::Instruction *i) {
        instruction = i;
    }
    /**
     * Return the LLVM basicblock of the LLVM instruction from which 
     * the expression was encoded.
     * If no instruction was assigned to this expression, 
     * the function returns null.
     */
    llvm::BasicBlock* getBB() {
        if (instruction==NULL) {
            //std::cout << "warning: no instruction for <";
            //this->dump();
            //std::cout << ">" << std::endl;
            return NULL;
        }
        return instruction->getParent();
    }
    /**
     * Return the unique ID number of this expression.
     */
    unsigned getID() {
        return currentID;   
    }
    /**
     * Return the op code of this expression (see above).
     */
    virtual unsigned getOpCode() = 0;
    /**
     * Dump to the standard ouput a textual representation 
     * of this expression.
     */
    virtual void dump() = 0;
    virtual void print(raw_ostream &OS) = 0;
    
};

/**
 * \class SingleExpression
 *
 * \brief A class representing a leaf expression such as a variable.
 */
class SingleExpression : public Expression {
protected:
    std::string name;
    /**
     * Default constructor.
     *
     * \param _name The name of the expression (for 
     * example the name of a variable).
     */
    SingleExpression(std::string _name) 
    : name(_name) { }
public:
    /**
     * Return the name of the variable.
     */
    std::string getName() {
        return name;
    }
};

/**
 * \class BinaryExpression
 * 
 * \brief A class representing an expression with two arguments.
 */
class BinaryExpression : public Expression {
protected:
    ExprPtr e1;
    ExprPtr e2;
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression. 
     * \param _e2 Right-hand side expression.
     */
    BinaryExpression(ExprPtr _e1, ExprPtr _e2) 
    : e1(_e1),e2(_e2) { }
    /**
     * Return the left-hand side expression.
     */
    ExprPtr getExpr1() {
        return e1;
    }
    /**
     * Return the right-hand side expression.
     */
    ExprPtr getExpr2() {
        return e2;
    }
    virtual unsigned getOpCode() {
        return Expression::Binary;
    }
    virtual void dump() {
        std::cout << "(";
        e1->dump();
        std::cout << ",";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << ",";
        e2->print(OS);
        OS << ")";
    }
};

/**
 * \class TrinaryExpression
 *
 * \brief A class representing an expression with three arguments.
 */
class TrinaryExpression : public Expression {
protected:
    ExprPtr e1;
    ExprPtr e2;
    ExprPtr e3;
public:
    /**
     * Default constructor.
     *
     * \param _e1 First expression.
     * \param _e2 Second expression.
     * \param _e3 Third expression.
     */
    TrinaryExpression(ExprPtr _e1, ExprPtr _e2, ExprPtr _e3)
    : e1(_e1),e2(_e2),e3(_e3) { }
    /**
     * Return the first expression.
     */
    ExprPtr getExpr1() {
        return e1;
    }
    /**
     * Return the second expression.
     */
    ExprPtr getExpr2() {
        return e2;
    }
    /**
     * Return the third expression.
     */
    ExprPtr getExpr3() {
        return e3;
    }    
    virtual unsigned getOpCode() {
        return Expression::Trinary;
    }
    virtual void dump() {
        std::cout << "(";
        e1->dump();
        std::cout << ",";
        e2->dump();
        std::cout << ",";
        e3->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << ",";
        e2->print(OS);
        OS << ",";
        e3->print(OS);
        OS << ")";
    }
};

/**
 * \class UnaryExpression
 *
 * \brief A class representing an expression with \a n arguments.
 */
class UnaryExpression : public Expression {
protected:
    std::vector<ExprPtr> exprs;
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    UnaryExpression(std::vector<ExprPtr> es) 
    : exprs(es) { }
    /**
     * Constructor.
     *
     * \param _e1 First expression.
     * \param _e2 Second expression.
     */
    UnaryExpression(ExprPtr _e1, ExprPtr _e2) {
        exprs.push_back(_e1);
        exprs.push_back(_e2);
    }
    virtual ~UnaryExpression() {
        exprs.clear();
    }
public:
    /**
     * Return all the expressions.
     */
    std::vector<ExprPtr> getExprs() {
        return exprs;
    }
};

/**
 * \class TrueExpression
 *
 * \brief An expression representing \a true.
 */
class TrueExpression : public Expression {
public:    
    /**
     * Default constructor.
     */
    TrueExpression() { }
    virtual unsigned getOpCode() {
        return Expression::True;
    }
    virtual void dump() {
        std::cout << "true";
    }
    virtual void print(raw_ostream &OS){
        OS << "true";
    }
};

/**
 * \class FalseExpression
 *
 * \brief An expression representing \a false.
 */
class FalseExpression : public Expression {
public:
    /**
     * Default constructor.
     */
    FalseExpression() { }
    virtual unsigned getOpCode() {
        return Expression::False;
    }
    virtual void dump() {
        std::cout << "false";
    }
    virtual void print(raw_ostream &OS){
        OS << "false";
    }
};

/**
 * \class UInt32NumExpression
 *
 * \brief An expression representing an unsigned integer value.
 */
class UInt32NumExpression : public Expression {
protected:
    unsigned num;
public:
    /**
     * Default constructor.
     *
     * \param n An unsigned 32 bit number to represent.
     */
    UInt32NumExpression(unsigned n) : num(n) { }
    /**
     * Return the value.
     */
    unsigned getValue() {
        return num;
    }
    virtual unsigned getOpCode() {
        return Expression::UInt32Num;
    }
    virtual void dump() {
        std::cout << num;
    }
    virtual void print(raw_ostream &OS){
        OS << num;
    }
};

/**
 * \class SInt32NumExpression
 *
 * \brief An expression representing a signed integer value.
 */
class SInt32NumExpression : public Expression {
protected:
    int num;
public:
    /**
     * Default constructor.
     *
     * \param n An signed 32 bit number to represent.
     */
    SInt32NumExpression(int n) : num(n) { }
    /**
     * Return the value.
     */
    int getValue() {
        return num;
    }
    virtual unsigned getOpCode() {
        return Expression::SInt32Num;
    }
    virtual void dump() {
        std::cout << num;
    }
    virtual void print(raw_ostream &OS){
        OS << num;
    }
};

/**
 * \class BoolVarExpression
 *
 * \brief An expression representing a Boolean variable.
 */
class BoolVarExpression : public SingleExpression {
public:
    /**
     * Default constructor.
     *
     * \param _name The name of the Boolean variable to 
     * represent. 
     */
    BoolVarExpression(std::string _name) 
    : SingleExpression(_name) { 
         NbBoolVariables++;
    }
    virtual unsigned getOpCode() {
        return Expression::BoolVar;
    }
    virtual void dump() {
        std::cout << name;
    }
    virtual void print(raw_ostream &OS){
        OS << name;
    }
};

/**
 * \class IntVarExpression
 *
 * \brief An expression representing an integer variable.
 */
class IntVarExpression : public SingleExpression {
public:
    /**
     * Default constructor.
     *
     * \param _name The name of the variable to represent.
     */
    IntVarExpression(std::string _name) 
    : SingleExpression(_name) { 
        NbIntVariables++;
    }
    virtual unsigned getOpCode() {
        return Expression::IntVar;
    }
    virtual void dump() {
        std::cout << name;
    }
    virtual void print(raw_ostream &OS){
        OS << name;
    }
};

/**
 * \class IntToIntVarExpression
 *
 * \brief An expression representing a function (int->int) variable.
 */
class IntToIntVarExpression : public SingleExpression {
public:
    /**
     * Default constructor.
     *
     * \param _name The name of variable to represent.
     */
    IntToIntVarExpression(std::string _name) 
    : SingleExpression(_name) { }
    virtual unsigned getOpCode() {
        return Expression::IntToIntVar;
    }
    virtual void dump() {
        std::cout << name;
    }
    virtual void print(raw_ostream &OS){
        OS << name;
    }
};

/**
 * \class ToParseExpression
 * 
 * \brief An expression representing a parsed expression.
 */
class ToParseExpression : public Expression {
private:
    std::string str;
public:
    /**
     * Default constructor.
     *
     * \param s A string to parse into an expression.
     */
    ToParseExpression(std::string s);
    /**
     * Return the parsed string.
     */
    std::string getString() {
        return str;
    }
    virtual unsigned getOpCode() {
        return Expression::ToParse;
    }
    virtual void dump() {
        std::cout << str;
    }
    virtual void print(raw_ostream &OS){
        OS << str;
    }
};

/**
 * \class GeExpression
 * 
 * \brief An expression representing \a e1 >= e2.
 */
class GeExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    GeExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Ge;
    }
    virtual void dump() {
        std::cout << "(>= ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " >= ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class GtExpression
 * 
 * \brief An expression representing \a e1 > e2.
 */
class GtExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    GtExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Gt;
    }
    virtual void dump() {
        std::cout << "(> ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " > ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class LeExpression
 *
 * \brief An expression representing \a e1 <= e2.
 */
class LeExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    LeExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Le;
    }
    virtual void dump() {
        std::cout << "(<= ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " <= ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class LtExpression 
 * 
 * \brief An expression representing \a e1 < e2.
 */
class LtExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    LtExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Lt;
    }
    virtual void dump() {
        std::cout << "(< ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " < ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class DiseqExpression
 *
 * \brief An expression representing \a e1 != e2.
 */
class DiseqExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    DiseqExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Diseq;
    }
    virtual void dump() {
        std::cout << "(!= ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " != ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class EqExpression
 *
 * \brief An expression representing \a e1 = e2.
 */
class EqExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    EqExpression(ExprPtr _e1, ExprPtr _e2) 
    : BinaryExpression(_e1, _e2) { }
    virtual unsigned getOpCode() {
        return Expression::Eq;
    }
    virtual void dump() {
        std::cout << "(= ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " = ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class NotExpression
 *
 * \brief An expression representing \a (not e).
 */
class NotExpression : public Expression {
protected:
    ExprPtr e;
public:
    /**
     * Default constructor.
     *
     * \param _e An expression.
     */
    NotExpression(ExprPtr _e) : e(_e) { }
    /**
     * Return the expression not negated.
     */
    ExprPtr get() { 
        return e;
    }
    virtual unsigned getOpCode() {
        return Expression::Not;
    }
    virtual void dump() {
        std::cout << "(not ";
        e->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(not ";
        e -> print(OS);
        OS << ")";
    }
};

/**
 * \class AndExpression
 *
 * \brief An expression representing \a e1 and e2.
 */
class AndExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    AndExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    AndExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::And;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(and ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " && ";
        }
    }
};

/**
 * \class OrExpression
 * 
 * \brief An expression representing \a e1 or e2.
 */
class OrExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    OrExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    OrExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::Or;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(or ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " || ";
        }
    }
};

/**
 * \class XorExpression
 *
 * \brief An expression representing \a e1 xor e2.
 */
class XorExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    XorExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    XorExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::Xor;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(xor ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " ^ ";
        }
    }
};

/**
 * \class ImplExpression
 *
 * \brief An expression representing \a e1 -> e2.
 */
class ImplExpression : public BinaryExpression {
public:
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    ImplExpression(ExprPtr e1, ExprPtr e2)
    : BinaryExpression(e1, e2) {}
    virtual unsigned getOpCode() {
        return Expression::Impl;
    }
    virtual void dump() {
        std::cout << "(impl ";
        std::vector<ExprPtr>::iterator it;
        e1 -> dump();
        std::cout << " ";
        e2 -> dump();      
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1 -> print(OS);
        OS << " -> ";
        e2 -> print(OS);
        OS << ")";
    }
};

/**
 * \class SumExpression
 *
 * \brief An expression representing \a e1 + e2.
 */
class SumExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    SumExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    SumExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::Sum;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(+ ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " + ";
        }
    }
};

/**
 * \class SubExpression
 *
 * \brief An expression representing \a e1 - e2.
 */
class SubExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    SubExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    SubExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::Sub;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(- ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " - ";
        }
    }
};

/**
 * \class MulExpression
 *
 * \brief An expression representing \a e1 * e2.
 */
class MulExpression : public UnaryExpression {
public:
    /**
     * Constructor.
     *
     * \param es A vector of expressions.
     */
    MulExpression(std::vector<ExprPtr> es) 
    : UnaryExpression(es) { }
    /**
     * Constructor.
     *
     * \param _e1 Left-hand side expression.
     * \param _e2 Right-hand side expression.
     */
    MulExpression(ExprPtr _e1, ExprPtr _e2) 
    : UnaryExpression(_e1, _e2) {}
    virtual unsigned getOpCode() {
        return Expression::Mul;
    }
    virtual void dump() {
        if (exprs.size()==1) {
            ExprPtr e = exprs.back();
            e->dump();
        } else {
            std::cout << "(* ";
            std::vector<ExprPtr>::iterator it;
            for(it = exprs.begin(); it != exprs.end(); ++it) {
                ExprPtr e = *it;
                e->dump();
                if (it+1!=exprs.end()) {
                    std::cout << " ";
                }
            }
            std::cout << ")";
        }
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        std::vector<ExprPtr>::iterator it;
        for(it = exprs.begin(); it != exprs.end(); ++it) {
            ExprPtr e = *it;
            e->print(OS);
            if(it + 1 == exprs.end())            
                OS << ")";
            else
                OS << " * ";
        }
    }
};

/**
 * \class DivExpression
 *
 * \brief An expression representing \a e1 / e2.
 */
class DivExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param e1 Left-hand side expression.
     * \param e2 Right-hand side expression.
     */
    DivExpression(ExprPtr e1, ExprPtr e2) 
    :  BinaryExpression(e1, e2) {}
    virtual unsigned getOpCode() {
        return Expression::Div;
    }
    virtual void dump() {
        std::cout << "(div ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << " / ";
        e2->print(OS);
        OS << ")";
    }
};

/**
 * \class ModExpression
 *
 * \brief An expression representing \a e1 % e2.
 */
class ModExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param e1 Left-hand side expression.
     * \param e2 Right-hand side expression.
     */
    ModExpression(ExprPtr e1, ExprPtr e2) 
    :  BinaryExpression(e1, e2) {}
    virtual unsigned getOpCode() {
        return Expression::Mod;
    }
    virtual void dump() {
        std::cout << "(mod ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << " %% ";
        e2->print(OS);
        OS << ")";
    }
};

/**
 * \class IteExpression
 *
 * \brief An expression representing \a (IF cond then eelse).
 */
class IteExpression : public TrinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param cond A condition expression (comparison).
     * \param then An expression to satisfy if \p cond is 
     * \a true.
     * \param eelse An expression to satisfy if \p cond is 
     * \a false.
     */
    IteExpression(ExprPtr cond, ExprPtr then, ExprPtr eelse)
    : TrinaryExpression(cond, then, eelse) {}
    virtual unsigned getOpCode() {
        return Expression::Ite;
    }
    virtual void dump() {
        std::cout << "(ite ";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << " ";
        e3->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << " ? ";
        e2->print(OS);
        OS << " : ";
        e3->print(OS);
        OS << ")";
    }
};

/**
 * \class AppExpression
 *
 * \brief An expression representing the function 
 * application term \a (e1 e2).
 */
class AppExpression : public BinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param f An uninterpreted function expression.
     * \param arg An argument expression (for exmample a Boolean variable).
     */
    AppExpression(ExprPtr f, ExprPtr arg) 
    :  BinaryExpression(f, arg) {}
    virtual unsigned getOpCode() {
        return Expression::App;
    }
    virtual void dump() {
        std::cout << "(";
        e1->dump();
        std::cout << " ";
        e2->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << " ";
        e2->print(OS);
        OS << ")";
    }
};

/**
 * \class UpdateExpression
 *
 * \brief An expression representing a function 
 * update term \a (update f (arg) v).
 */
class UpdateExpression : public TrinaryExpression {
public:
    /**
     * Default constructor.
     *
     * \param f An uninterpreted function expression.
     * \param arg An argument expression (for exmample a Boolean variable).
     * \param v A the expression to use to update the returned value of \a (f arg).
     */
    UpdateExpression(ExprPtr f, ExprPtr arg, ExprPtr v) 
    :  TrinaryExpression(f, arg, v) {}
    virtual unsigned getOpCode() {
        return Expression::Update;
    }
    virtual void dump() {
        std::cout << "(update ";
        e1->dump();
        std::cout << " (";
        e2->dump();
        std::cout << ") ";
        e3->dump();
        std::cout << ")";
    }
    virtual void print(raw_ostream &OS){
        OS << "(";
        e1->print(OS);
        OS << "[";
        e2->print(OS);
        OS << "] =";
        e3->print(OS);
        OS << ")";
    }
};

#endif // _EXPRESSION_H