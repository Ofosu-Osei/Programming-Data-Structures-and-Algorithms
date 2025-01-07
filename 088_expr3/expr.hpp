#ifndef __EXPR_H__
#define __EXPR_H__

#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;  // Abstract method
  virtual long evaluate() const = 0;
  virtual ~Expression() {}  // Virtual destructor
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

  virtual long evaluate() const { return number; }
};

// Abstract class for operator expressions (+, -, *, /)
class OperatorExpression : public Expression {
 protected:
  Expression * lhs;
  Expression * rhs;

  virtual std::string getOperatorSymbol() const = 0;  // Pure virtual member function

 public:
  OperatorExpression(Expression * left_expr, Expression * right_expr) :
      lhs(left_expr), rhs(right_expr) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " " << getOperatorSymbol() << " " << rhs->toString()
       << ")";
    return ss.str();
  }

  ~OperatorExpression() {
    delete lhs;
    delete rhs;
  }
};

// Class for addition expressions
class PlusExpression : public OperatorExpression {
 public:
  PlusExpression(Expression * left_expr, Expression * right_expr) :
      OperatorExpression(left_expr, right_expr) {}

 protected:
  virtual std::string getOperatorSymbol() const { return "+"; }

 public:
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

// Class for subtraction expressions
class MinusExpression : public OperatorExpression {
 public:
  MinusExpression(Expression * left_expr, Expression * right_expr) :
      OperatorExpression(left_expr, right_expr) {}

 protected:
  virtual std::string getOperatorSymbol() const { return "-"; }

 public:
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

// Class for multiplication expressions
class TimesExpression : public OperatorExpression {
 public:
  TimesExpression(Expression * left_expr, Expression * right_expr) :
      OperatorExpression(left_expr, right_expr) {}

 protected:
  virtual std::string getOperatorSymbol() const { return "*"; }

 public:
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

// Class for division expressions
class DivExpression : public OperatorExpression {
 public:
  DivExpression(Expression * left_expr, Expression * right_expr) :
      OperatorExpression(left_expr, right_expr) {}

 protected:
  virtual std::string getOperatorSymbol() const { return "/"; }

  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};

#endif
