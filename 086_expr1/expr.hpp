#ifndef __EXPR_H__
#define __EXPR_H__
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;  //abstract method
  virtual ~Expression() {}                   //virtual destructor
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long num) : number(num) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * left_exp, Expression * right_exp) :
      lhs(left_exp), rhs(right_exp) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }

  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
