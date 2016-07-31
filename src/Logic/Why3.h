/**
 * Why3.h
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/04/20
 * @copyright : NII 2015
 */


#ifndef _WHY3_H
#define _WHY3_H

#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Why3;
class W3Theory;
class W3Decl;
class W3Goal;
class W3Use;
class W3Expr;
class W3LitExpr;
class W3AppExpr;
class W3ConnExpr;
class W3NotExpr;
class W3QuantExpr;
class W3IfExpr;
class W3ArrayExpr;
class W3ArrayUpdExpr;
class W3LetExpr;
class W3MatchExpr;
class W3FieldExpr;
class W3RecordExpr;
class W3RecordUpdateExpr;
class W3CastExpr;
class W3LabeledExpr;

typedef std::shared_ptr<W3Decl>           W3DeclPtr;
typedef std::shared_ptr<W3Use>            W3UsePtr;
typedef std::shared_ptr<W3Goal>           W3GoalPtr;        

typedef std::shared_ptr<W3Expr>           W3ExprPtr;
typedef std::shared_ptr<W3LitExpr>        W3LitExprPtr;
typedef std::shared_ptr<W3AppExpr>        W3AppExprPtr;
typedef std::shared_ptr<W3ConnExpr>       W3ConnExprPtr;
typedef std::shared_ptr<W3NotExpr>        W3NotExprPtr;
typedef std::shared_ptr<W3QuantExpr>      W3QuantExprPtr;
typedef std::shared_ptr<W3IfExpr>         W3IfExprPtr;
typedef std::shared_ptr<W3ArrayExpr>      W3ArrayExprPtr;
typedef std::shared_ptr<W3ArrayUpdExpr>   W3ArrayUpdExprPtr;

typedef std::string Name;

class Why3 {
public:
  Why3(){}
  virtual ~Why3() {};
  virtual void prettyprint(llvm::raw_ostream &os) = 0;
};

class W3Theory : public Why3{
private:
  std::string name;
  std::vector<W3DeclPtr> decls;
public:
  W3Theory(const std::string &_name, const std::vector<W3DeclPtr> &_decls)
    :name(_name),decls(_decls){}
  W3Theory(const std::string &_name)
    :name(_name){}
  virtual ~W3Theory(){};

  virtual void prettyprint(llvm::raw_ostream &os);

  void add(W3DeclPtr d);
};

class W3Decl : public Why3{
public:
  static const unsigned short W3UseOp   = 1;
  static const unsigned short W3GoalOp  = 2;
protected:
  W3Decl(){ }
  ~W3Decl() { }
public:
  static W3UsePtr  mkUseImport(const std::string &theory);
  static W3UsePtr  mkUseExport(const std::string &theory);
  static W3GoalPtr mkGoal(const std::string &name, W3ExprPtr e);

  virtual unsigned short getOpCode() = 0;
};

class W3Goal : public W3Decl{
private:
  std::string name;
  W3ExprPtr e;
public:
  W3Goal(const std::string &_name, W3ExprPtr _e):name(_name),e(_e){}
  ~W3Goal(){ }

  virtual unsigned short getOpCode(){return W3Decl::W3GoalOp;}
  virtual void prettyprint(llvm::raw_ostream &os);
};

class W3Use : public W3Decl{
public:
  enum W3ImpExp {W3Import, W3Export};
private:
  W3ImpExp op;
  std::string theory;
public:
  W3Use(W3ImpExp _op, const std::string &_theory):W3Decl(),op(_op),theory(_theory){}
  ~W3Use(){ }

  virtual unsigned short getOpCode(){return W3Decl::W3UseOp;}
  virtual void prettyprint(llvm::raw_ostream &os);
};


class W3Expr : public Why3{

public:
  static const unsigned short W3Lit           = 1;
  static const unsigned short W3App           = 2;
  static const unsigned short W3Conn          = 3;
  static const unsigned short W3Not           = 4;
  static const unsigned short W3Quant         = 5;
  static const unsigned short W3If            = 6;

  static const unsigned short W3Let           = 7;
  static const unsigned short W3Match         = 8;
  static const unsigned short W3Field         = 9;
  static const unsigned short W3Record        = 10;
  static const unsigned short W3RecordUpdate  = 11;
  static const unsigned short W3Cast          = 12;
  static const unsigned short W3Labeled       = 13;
  static const unsigned short W3ArrayUpdate   = 14;
  static const unsigned short W3ArrayAccess   = 15;

protected:
  W3Expr(){ }
  ~W3Expr(){ }

public:
  static W3LitExprPtr mkTrue();
  static W3LitExprPtr mkFalse();
  static W3LitExprPtr mkInt(int i);
  static W3LitExprPtr mkUInt(unsigned int i);

  static W3AppExprPtr mkApp(const std::string &name, W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkIntVar(const std::string &n);
  static W3AppExprPtr mkBoolVar(const std::string &n);
  static W3AppExprPtr mkIntArrayVar(const std::string &n);
  static W3AppExprPtr mkEq(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkDiseq(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkLt(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkLe(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkGt(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkGe(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkSum(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkSum(const std::vector<W3ExprPtr> &es);
  static W3AppExprPtr mkSub(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkSub(const std::vector<W3ExprPtr> &es);
  static W3AppExprPtr mkMul(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkMul(const std::vector<W3ExprPtr> &es);
  static W3AppExprPtr mkDiv(W3ExprPtr e1, W3ExprPtr e2);
  static W3AppExprPtr mkMod(W3ExprPtr e1, W3ExprPtr e2);

  static W3ConnExprPtr mkAnd(W3ExprPtr e1, W3ExprPtr e2);
  static W3ConnExprPtr mkAnd(const std::vector<W3ExprPtr> &es);
  static W3ConnExprPtr mkOr(W3ExprPtr e1, W3ExprPtr e2);
  static W3ConnExprPtr mkOr(const std::vector<W3ExprPtr> &es);
  static W3ConnExprPtr mkImpl(W3ExprPtr e1, W3ExprPtr e2);

  static W3NotExprPtr mkNot(W3ExprPtr e);

  static W3QuantExprPtr mkUQuant(const std::vector<std::string> &_int_vars, 
                                 const std::vector<std::string> &_bool_vars,
                                 W3ExprPtr _e);
  static W3QuantExprPtr mkUQuant(const std::vector<std::string> &_int_vars, 
                                 const std::vector<std::string> &_bool_vars,
                                 const std::vector<std::string> &_int_to_int_vars,
                                 W3ExprPtr _e);
  static W3QuantExprPtr mkEQuant(const std::vector<std::string> &_int_vars, 
                                 const std::vector<std::string> &_bool_vars,
                                 W3ExprPtr _e);

  static W3IfExprPtr mkIte(W3ExprPtr cond, W3ExprPtr e1, W3ExprPtr e2);

  static W3ArrayExprPtr    mkArrayAccess(W3ExprPtr name, W3ExprPtr index);
  static W3ArrayUpdExprPtr mkArrayUpdate(W3ExprPtr name, W3ExprPtr index, W3ExprPtr value);

  virtual unsigned short getOpCode() = 0;
  virtual void prettyprint(llvm::raw_ostream &os) = 0;
  virtual void toSMTLib2(llvm::raw_ostream & os) = 0;

};

class W3LitExpr : public W3Expr{
private:
  
  static const unsigned short W3Int  = 1;
  static const unsigned short W3UInt  = 2;
  static const unsigned short W3Real = 3;
  static const unsigned short W3Bool = 4;

  union W3Literal{
    int         W3Int;
    unsigned int W3UInt;
    std::string W3Real;
    bool        W3Bool;
    W3Literal(int i):W3Int(i){}
    W3Literal(unsigned int i):W3UInt(i){}
    W3Literal(const std::string &r):W3Real(r){}
    W3Literal(bool b):W3Bool(b){}
    ~W3Literal(){}
  } value;

  unsigned short type;

public:

  W3LitExpr(int i):value(i),type(1){ }
  W3LitExpr(unsigned int i):value(i),type(2){ }
  W3LitExpr(const std::string &s):value(s),type(3){ }
  W3LitExpr(bool b):value(b),type(4){ }
  ~W3LitExpr(){ };

  virtual unsigned short getOpCode(){ return W3Expr::W3Lit;}

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);

  bool        isInt()   {return type == 1;}
  bool        isReal()  {return type == 2;}
  bool        isBool()  {return type == 3;}
  int         getInt()  {return value.W3Int;}
  std::string getReal() {return value.W3Real;}
  bool        getBool() {return value.W3Bool;}

};

class W3AppExpr : public W3Expr{
private:
  std::vector<W3ExprPtr> exprs;
  Name name;
public:
  
  W3AppExpr(const Name &_name):name(_name){ }

  W3AppExpr(const Name &_name, const std::vector<W3ExprPtr> &_exprs)
    :exprs(_exprs),name(_name){}
  
  W3AppExpr(const Name &_name, W3ExprPtr e1, W3ExprPtr e2):name(_name){
    exprs.push_back(e1);
    exprs.push_back(e2);
  }
  
  ~W3AppExpr(){}

  virtual unsigned short getOpCode(){
    return W3Expr::W3App;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};


class W3ConnExpr : public W3Expr{

public:
  enum W3Conn{
    W3And,
    W3AsymAnd,
    W3Or,
    W3AsymOr,
    W3Implies,
    W3Iff
  };

private:
  W3Conn conn;
  std::vector<W3ExprPtr> exprs;

public:

  W3ConnExpr(W3Conn _conn, const std::vector<W3ExprPtr> &_exprs)
    :conn(_conn),exprs(_exprs){}
  W3ConnExpr(W3Conn _conn, W3ExprPtr e1, W3ExprPtr e2):conn(_conn){
    exprs.push_back(e1);
    exprs.push_back(e2);
  }
  ~W3ConnExpr() {}


  std::string connToString();
  std::string connToStringSMTLib();

  virtual unsigned short getOpCode(){
    return W3Expr::W3Conn;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};


class W3NotExpr : public W3Expr{
private:
  W3ExprPtr expr;
public:
  W3NotExpr(W3ExprPtr _expr):expr(_expr){}
  ~W3NotExpr(){ }

  virtual unsigned short getOpCode(){
    return W3Expr::W3Not;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};


class W3QuantExpr : public W3Expr{
public:
  enum W3Quant {W3ForAll, W3Exists};
private:
  std::vector<std::string> int_vars;
  std::vector<std::string> bool_vars;
  std::vector<std::string> int_to_int_vars;
  W3ExprPtr e;
  W3Quant quant;
public:
  W3QuantExpr(const std::vector<std::string> &_int_vars,
              const std::vector<std::string> &_bool_vars,
              W3ExprPtr _e, 
              W3Quant _quant)
    :int_vars(_int_vars),bool_vars(_bool_vars),e(_e),quant(_quant){}
  W3QuantExpr(const std::vector<std::string> &_int_vars,
              const std::vector<std::string> &_bool_vars,
              const std::vector<std::string> &_int_to_int_vars,
              W3ExprPtr _e,
              W3Quant _quant)
    :int_vars(_int_vars),bool_vars(_bool_vars),
     int_to_int_vars(_int_to_int_vars),e(_e),quant(_quant){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Quant;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3IfExpr : public W3Expr{
private:
  W3ExprPtr cond;
  W3ExprPtr e1;
  W3ExprPtr e2;
public:
  W3IfExpr(W3ExprPtr _cond, W3ExprPtr _e1, W3ExprPtr _e2)
    :cond(_cond),e1(_e1),e2(_e2){}
  ~W3IfExpr(){ }
  virtual unsigned short getOpCode(){
    return W3Expr::W3If;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3ArrayUpdExpr : public W3Expr{
private:
  W3ExprPtr name;
  W3ExprPtr index;
  W3ExprPtr e;
public:
  W3ArrayUpdExpr(W3ExprPtr _name, W3ExprPtr _index, W3ExprPtr _e)
    :name(_name),index(_index),e(_e){}
  ~W3ArrayUpdExpr(){ };
  virtual unsigned short getOpCode(){
    return W3Expr::W3ArrayUpdate;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3ArrayExpr : public W3Expr{
private:
  W3ExprPtr name;
  W3ExprPtr index;
public:
  W3ArrayExpr(W3ExprPtr _name, W3ExprPtr _index)
    :name(_name),index(_index){ }
  ~W3ArrayExpr(){ };
  virtual unsigned short getOpCode(){
    return W3Expr::W3ArrayAccess;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

// -----------------------------------------

class W3LetExpr : public W3Expr{
public:
  ~W3LetExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Let;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3MatchExpr : public W3Expr{
public:
  ~W3MatchExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Match;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3FieldExpr : public W3Expr{
public:
  ~W3FieldExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Field;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3RecordExpr : public W3Expr{
public:
  ~W3RecordExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Record;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3RecordUpdateExpr : public W3Expr{
public:
  ~W3RecordUpdateExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3RecordUpdate;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3CastExpr : public W3Expr{
public:
  ~W3CastExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Cast;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};

class W3LabeledExpr : public W3Expr{
public:
  ~W3LabeledExpr(){}
  virtual unsigned short getOpCode(){
    return W3Expr::W3Labeled;
  }

  virtual void prettyprint(llvm::raw_ostream &os);
  virtual void toSMTLib2(llvm::raw_ostream & os);
};



#endif