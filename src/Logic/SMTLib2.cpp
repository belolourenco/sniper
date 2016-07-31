/**
 * SMTLib2.cpp
 *
 *
 *
 * @author    : Claudio Belo Lourenco
 * @contact   : belolourenco@di.uminho.pt
 * @date      : 2016/04/26
 * @copyright : NII 2015
 */


#include "SMTLib2.h"

SMTLib2Gen::SMTLib2Gen():int_vars(),bool_vars(),int_to_int_vars(){
  counter = 0;
  //this -> theory = new W3Theory("SNIPER");
}

SMTLib2Gen::~SMTLib2Gen(){
}

void SMTLib2Gen::init(){
  int_vars.clear();
  bool_vars.clear();
  int_to_int_vars.clear();
}

void SMTLib2Gen::encode(ExprPtr e){
  exprs.push_back(makeWhy3Expr(e));
}

void SMTLib2Gen::prettyprint(raw_ostream &os){
  os << "(set-logic QF_AUFLIA)" << "\n";
  for(std::string s : int_vars)   
    //os << "(declare-fun " << s << " () " << "Int" << ")" << "\n";
    os << "(declare-const " << s << " " << "Int" << ")" << "\n";
  for(std::string s : bool_vars)
    //os << "(declare-fun " << s << " () " << "Bool" << ")" << "\n";
    os << "(declare-const " << s << " " << "Bool" << ")" << "\n";
  for(std::string s : int_to_int_vars)
    //os << "(declare-fun " << s << " " << "(Int)" << " " << "Int" << ")" << "\n";
    os << "(declare-const " << s << " " << "(Array Int Int)" << ")" << "\n";

  for(W3ExprPtr e : exprs){
    os << "\n";  
    os << "(push 1)";
    os << "\n";
    os << "(assert ";
    e -> toSMTLib2(os);
    os << ")" << "\n";
    os << "\n";
    os << "(check-sat)";
    os << "\n";
    os << "(pop 1)";
    os << "\n";
  }
}

W3ExprPtr SMTLib2Gen::makeWhy3Expr(ExprPtr e){
  switch (e->getOpCode()) {
    case Expression::True:{
        p.true_exps++;
        return W3Expr::mkTrue();
    }
    case Expression::False:{
        p.false_exps++;
        return W3Expr::mkFalse();
    }
    case Expression::UInt32Num: {
        UInt32NumExprPtr ne = std::static_pointer_cast<UInt32NumExpression>(e);
        p.num_exps++;
        return W3Expr::mkUInt(ne -> getValue());
    }
    case Expression::SInt32Num: {
        SInt32NumExprPtr ne = std::static_pointer_cast<SInt32NumExpression>(e);
        p.num_exps++;
        return W3Expr::mkInt(ne -> getValue());;
    }
    case Expression::BoolVar: {
        BoolVarExprPtr be = std::static_pointer_cast<BoolVarExpression>(e);
        std::string s;
        if(be -> getName() == ""){
            s = "undef" + std::to_string(counter++);
        }else{
            s = be->getName();
            replace(s.begin(), s.end(), '.', '_' );
        }
        p.bool_vars++;
        if(std::find(bool_vars.begin(), bool_vars.end(), s) == bool_vars.end())
          bool_vars.push_back(s);
        return W3Expr::mkBoolVar(s);
    }
    case Expression::IntVar: {
        IntVarExprPtr ie = std::static_pointer_cast<IntVarExpression>(e);
        std::string s;
        if(ie -> getName() == ""){
            s = "undef" + std::to_string(counter++);
        }else{
            s = (ie -> getName() == "div")?"div_aux":ie -> getName();
            replace(s.begin(), s.end(), '.', '_' );
        }
        p.int_vars++;
        if(std::find(int_vars.begin(), int_vars.end(), s) == int_vars.end())
          int_vars.push_back(s);
        return W3Expr::mkIntVar(s);
    }
    case Expression::IntToIntVar: {
      IntToIntVarExprPtr ie = std::static_pointer_cast<IntToIntVarExpression>(e);
      std::string s;
      if(ie -> getName() == ""){
          s = "undef" + std::to_string(counter++);
      }else{
          s = (ie -> getName() == "div")?"?div":ie -> getName();
          replace(s.begin(), s.end(), '.', '_' );
      }
      // UPDATE THIS IN PROFILLING FILE - ADD ARRAYS
      p.int_vars++;
      if(std::find(int_to_int_vars.begin(), int_to_int_vars.end(), s) == int_to_int_vars.end())
        int_to_int_vars.push_back(s);
      return W3Expr::mkIntArrayVar(s);
    }
    // case Expression::ToParse: {
    //     ToParseExprPtr te = std::static_pointer_cast<ToParseExpression>(e);
    //     p.parse_exps ++;
    //     return yices_parse_expression(ctx, te->getString().c_str());
    // }
    case Expression::Gt: {
        GtExprPtr gt = std::static_pointer_cast<GtExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(gt->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(gt->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkGt(e1,e2); 
    }
    case Expression::Ge: {
        GeExprPtr ge = std::static_pointer_cast<GeExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(ge->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(ge->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkGe(e1, e2);    
    }
    case Expression::Le: {
        LeExprPtr le = std::static_pointer_cast<LeExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(le->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(le->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkLe(e1, e2);    
    }
    case Expression::Lt: {
        LtExprPtr lt = std::static_pointer_cast<LtExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(lt->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(lt->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkLt(e1, e2);    
    }
    case Expression::Diseq: {
        DiseqExprPtr de = std::static_pointer_cast<DiseqExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(de->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(de->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkNot(W3Expr::mkEq(e1, e2));  
    }
    case Expression::Eq: {
        EqExprPtr ee = std::static_pointer_cast<EqExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(ee->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(ee->getExpr2());
        p.comparison_ops++;
        return W3Expr::mkEq(e1, e2);    
    }
    case Expression::Not: {
        NotExprPtr ne = std::static_pointer_cast<NotExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(ne->get());
        p.not_ops++;
        return W3Expr::mkNot(e1);
    }
    case Expression::And: {
        AndExprPtr ae = std::static_pointer_cast<AndExpression>(e);
        std::vector<ExprPtr> es = ae -> getExprs();
        if (es.size() == 0) {
            std::cout << "error: and expression.\n";
            exit(1);
        } else
            if (es.size() == 1) {
                return makeWhy3Expr(es.back());
            }
        std::vector<W3ExprPtr> args;
        for(ExprPtr e:es) {
            args.push_back(makeWhy3Expr(e)); 
        }   
        p.and_ops++;
        return W3Expr::mkAnd(args);   
    }
    case Expression::Or: {
        OrExprPtr oe = std::static_pointer_cast<OrExpression>(e);
        std::vector<ExprPtr> es = oe -> getExprs();
        if (es.size() == 0) {
            std::cout << "error: and expression.\n";
            exit(1);
        } else
            if (es.size() == 1) {
                return makeWhy3Expr(es.back());
            }
        std::vector<W3ExprPtr> args;
        for(ExprPtr e:es) {
            args.push_back(makeWhy3Expr(e)); 
        }
        p.or_ops++;
        return W3Expr::mkOr(args);   
    }
    case Expression::Xor: {
      assert(0 && "Xor not yet supported in Why3Gen.cpp");
    //     XorExprPtr xe = std::static_pointer_cast<XorExpression>(e);
    //     std::vector<ExprPtr> es = xe->getExprs();
    //     unsigned n = es.size();
    //     if (n==1) {
    //         return makeYicesExpression(es.back());
    //     }
    //     else if (n==2) {
    //         ExprPtr orExpr = Expression::mkOr(es[0], es[1]);
    //         ExprPtr andExpr = Expression::mkAnd(es[0], es[1]);
    //         ExprPtr notExpr = Expression::mkNot(andExpr);
    //         ExprPtr xorExpr = Expression::mkAnd(orExpr, notExpr);
    //         return makeYicesExpression(xorExpr);
    //     } else 
    //         if (n==3) {                
    //             ExprPtr e1= es[0];
    //             ExprPtr e2= es[1];
    //             ExprPtr e3= es[2];
    //             ExprPtr not_e1= Expression::mkNot(es[0]);
    //             ExprPtr not_e2= Expression::mkNot(es[1]);
    //             ExprPtr not_e3= Expression::mkNot(es[2]);
    //             // (and e1' e2' e3)
    //             std::vector<ExprPtr> v1;
    //             v1.push_back(not_e1);
    //             v1.push_back(not_e2);
    //             v1.push_back(e3);
    //             ExprPtr and1 = Expression::mkAnd(v1);
    //             // (and e1' e2 e3')
    //             std::vector<ExprPtr> v2;
    //             v2.push_back(not_e1);
    //             v2.push_back(e2);
    //             v2.push_back(not_e3);
    //             ExprPtr and2 = Expression::mkAnd(v2);
    //             // (and e1 e2' e3')
    //             std::vector<ExprPtr> v3;
    //             v3.push_back(e1);
    //             v3.push_back(not_e2);
    //             v3.push_back(not_e3);
    //             ExprPtr and3 = Expression::mkAnd(v3);
    //             // (and e1 e2 e3)
    //             std::vector<ExprPtr> v4;
    //             v4.push_back(e1);
    //             v4.push_back(e2);
    //             v4.push_back(e3);
    //             ExprPtr and4 = Expression::mkAnd(v4);
    //             // (or and1 and2 and3 and4)
    //             std::vector<ExprPtr> v5;
    //             v5.push_back(and1);
    //             v5.push_back(and2);
    //             v5.push_back(and3);
    //             v5.push_back(and4);
    //             ExprPtr xorExpr = Expression::mkOr(v5);
    //             return makeYicesExpression(xorExpr);
    //         } else {
    //             std::cout << "error: xor expression.\n";
    //             exit(1);
    //         }  
    }
    case Expression::Sum: {
        SumExprPtr se = std::static_pointer_cast<SumExpression>(e);
        std::vector<ExprPtr> es = se -> getExprs();
        if (es.size() == 0) {
            std::cout << "error: sum expression.\n";
            exit(1);
        } else
            if (es.size() == 1) {
                return makeWhy3Expr(es.back());
            }
        std::vector<W3ExprPtr> args;
        for(ExprPtr e:es) {
            args.push_back(makeWhy3Expr(e)); 
        }
        p.sum_ops++;
        return W3Expr::mkSum(args);   
    }   
    case Expression::Sub:  {
        SubExprPtr se = std::static_pointer_cast<SubExpression>(e);
        std::vector<ExprPtr> es = se -> getExprs();
        if (es.size() == 0) {
            std::cout << "error: sum expression.\n";
            exit(1);
        } else
            if (es.size() == 1) {
                return makeWhy3Expr(es.back());
            }
        std::vector<W3ExprPtr> args;
        for(ExprPtr e:es) {
            args.push_back(makeWhy3Expr(e)); 
        }
        p.sub_ops++;
        return W3Expr::mkSub(args);   
    }   
    case Expression::Mul: {
        MulExprPtr me = std::static_pointer_cast<MulExpression>(e);
        std::vector<ExprPtr> es = me -> getExprs();
        if (es.size() == 0) {
            std::cout << "error: sum expression.\n";
            exit(1);
        } else
            if (es.size() == 1) {
                return makeWhy3Expr(es.back());
            }
        std::vector<W3ExprPtr> args;
        for(ExprPtr e:es) {
            args.push_back(makeWhy3Expr(e)); 
        } 
        p.mul_ops++;
        return W3Expr::mkMul(args);   
    }               
    case Expression::Ite: {
        IteExprPtr ie = std::static_pointer_cast<IteExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(ie->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(ie->getExpr2());
        W3ExprPtr e3 = makeWhy3Expr(ie->getExpr3());
        p.ite_ops++;
        return W3Expr::mkIte(e1, e2, e3);
    }
    case Expression::App: {
      AppExprPtr ae = std::static_pointer_cast<AppExpression>(e);
      
      W3ExprPtr name = makeWhy3Expr(ae -> getExpr1());
      W3ExprPtr index = makeWhy3Expr(ae -> getExpr2());
      p.app_ops++;
      
      return W3Expr::mkArrayAccess(name,index); 
    }
    case Expression::Update: {
      UpdateExprPtr u = std::static_pointer_cast<UpdateExpression>(e);
      
      W3ExprPtr name  = makeWhy3Expr(u -> getExpr1());
      W3ExprPtr index = makeWhy3Expr(u -> getExpr2());
      W3ExprPtr value = makeWhy3Expr(u -> getExpr3());
      p.update_ops++;

      return W3Expr::mkArrayUpdate(name,index,value);
    }
    case Expression::Div: {
        DivExprPtr de = std::static_pointer_cast<DivExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(de->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(de->getExpr2());
        p.div_ops++;
        return W3Expr::mkDiv(e1,e2);
    }
    case Expression::Mod: {
        ModExprPtr de = std::static_pointer_cast<ModExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(de->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(de->getExpr2());
        p.mod_ops++;
        return W3Expr::mkMod(e1,e2);
    }
    case Expression::Impl: {
        ImplExprPtr impl = std::static_pointer_cast<ImplExpression>(e);
        W3ExprPtr e1 = makeWhy3Expr(impl->getExpr1());
        W3ExprPtr e2 = makeWhy3Expr(impl->getExpr2());
        p.impl_ops++;
        return W3Expr::mkImpl(e1,e2);
    }
    default:
        std::cerr << "error: wrong expression op code!\n";
        exit(1);
        break;
  }

  return W3Expr::mkTrue();
 }
