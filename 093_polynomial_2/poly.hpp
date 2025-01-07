#ifndef __POLY_H__
#define __POLY_H__

#include <algorithm>
#include <cmath>
#include <complex>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>

// Exception class to handle convergence failure
template<typename NumT>
class convergence_failure : public std::exception {
 public:
  const NumT value;

  convergence_failure(const NumT & val) : value(val) {}

  virtual const char * what() const throw() { return "Convergence failure"; }
};

template<typename NumT>
class Polynomial {
 private:
  std::vector<NumT> coefficients;

  void trim() {
    while (!coefficients.empty() && coefficients.back() == NumT()) {
      coefficients.pop_back();
    }
    if (coefficients.empty()) {
      coefficients.push_back(NumT());
    }
  }

 public:
  Polynomial() : coefficients(1, NumT()) {}

  // Add a term
  void addTerm(const NumT & c, unsigned p) {
    if (p >= coefficients.size()) {
      coefficients.resize(p + 1, NumT());
    }
    coefficients[p] += c;
    trim();
  }

  // Addition operator
  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial result;
    result.coefficients.resize(std::max(coefficients.size(), rhs.coefficients.size()),
                               NumT());
    for (size_t i = 0; i < coefficients.size(); ++i) {
      result.coefficients[i] += coefficients[i];
    }
    for (size_t i = 0; i < rhs.coefficients.size(); ++i) {
      result.coefficients[i] += rhs.coefficients[i];
    }
    result.trim();
    return result;
  }

  // Subtraction operator
  Polynomial operator-(const Polynomial & rhs) const {
    Polynomial result;
    result.coefficients.resize(std::max(coefficients.size(), rhs.coefficients.size()),
                               NumT());
    for (size_t i = 0; i < coefficients.size(); ++i) {
      result.coefficients[i] += coefficients[i];
    }
    for (size_t i = 0; i < rhs.coefficients.size(); ++i) {
      result.coefficients[i] -= rhs.coefficients[i];
    }
    result.trim();
    return result;
  }

  // Multiplication operato
  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial result;
    result.coefficients.resize(coefficients.size() + rhs.coefficients.size() - 1, NumT());
    for (size_t i = 0; i < coefficients.size(); ++i) {
      for (size_t j = 0; j < rhs.coefficients.size(); ++j) {
        result.coefficients[i + j] += coefficients[i] * rhs.coefficients[j];
      }
    }
    result.trim();
    return result;
  }

  // Multiplication operator (polynomial * scalar)
  Polynomial operator*(const NumT & scalar) const {
    Polynomial result(*this);
    for (size_t i = 0; i < result.coefficients.size(); ++i) {
      result.coefficients[i] *= scalar;
    }
    result.trim();
    return result;
  }

  // Negation operator
  Polynomial operator-() const {
    Polynomial result(*this);
    for (size_t i = 0; i < result.coefficients.size(); ++i) {
      result.coefficients[i] = -result.coefficients[i];
    }
    return result;
  }

  // Equality operator
  bool operator==(const Polynomial & rhs) const {
    return coefficients == rhs.coefficients;
  }

  // Inequality operator
  bool operator!=(const Polynomial & rhs) const { return !(*this == rhs); }

  // Compound addition assignment operator
  Polynomial & operator+=(const Polynomial & rhs) {
    *this = *this + rhs;
    return *this;
  }

  // Compound subtraction assignment operator
  Polynomial & operator-=(const Polynomial & rhs) {
    *this = *this - rhs;
    return *this;
  }

  // Compound multiplication assignment operator
  Polynomial & operator*=(const Polynomial & rhs) {
    *this = *this * rhs;
    return *this;
  }

  // Compound multiplication assignment operator(polynomial * scalar)
  Polynomial & operator*=(const NumT & scalar) {
    *this = *this * scalar;
    return *this;
  }

  // Evaluates the polynomial at a given value of x and returns result
  NumT eval(const NumT & x) const {
    NumT result = NumT();
    NumT power_of_x = NumT(1);
    for (size_t i = 0; i < coefficients.size(); ++i) {
      result += coefficients[i] * power_of_x;
      power_of_x *= x;
    }
    return result;
  }

  // Overload operator() for polynomial evaluations
  NumT operator()(const NumT & x) const { return eval(x); }

  // Method to compute the derivative of the polynomial
  Polynomial derivative() const {
    Polynomial result;
    for (size_t i = 1; i < coefficients.size(); ++i) {
      result.addTerm(NumT(i) * coefficients[i], i - 1);
    }
    return result;
  }

  //Templated method to converts this polynomial intto one  with
  // another  coefficient type, but equivalent coefficients
  template<typename OtherNumT>
  Polynomial<OtherNumT> convert() const {
    Polynomial<OtherNumT> result;
    for (size_t i = 0; i < coefficients.size(); ++i) {
      if (coefficients[i] != NumT()) {
        result.addTerm(OtherNumT(coefficients[i]), i);
      }
    }
    return result;
  }

  // Finds zero using Newton-Raphson method
  template<typename ToleranceT>
  NumT findZero(NumT x,
                int maxSteps,
                const ToleranceT & tolerance,
                const ToleranceT & deriv_tolerance) const {
    Polynomial<NumT> deriv = derivative();
    int stepsLeft = maxSteps;
    NumT y, dy;

    do {
      y = eval(x);
      dy = deriv.eval(x);
      /*
      std::cout << stepsLeft << " step remaining x= " << x << ", f(x) = " << y
                << ", f'(x) = " << deriv.eval(x) << "\n";
      */
      if (std::abs(y) <= tolerance) {
        return x;  // Converged successfully
      }
      if (std::abs(dy) < deriv_tolerance) {
        throw convergence_failure<NumT>(x);  // Derivative is too small
      }
      // next iteration
      if (--stepsLeft >= 0) {
        x = x - y / dy;  // Newton-Raphson Method
      }
    } while (stepsLeft >= 0);

    throw convergence_failure<NumT>(x);  // Failed to converge within maxSteps
  }

  // Friend function to overload << operator for outputs
  template<typename N>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

// Overload << operator for outputs
template<typename NumT>
std::ostream & operator<<(std::ostream & os, const Polynomial<NumT> & p) {
  bool firstTerm = true;
  for (size_t i = p.coefficients.size(); i-- > 0;) {
    if (p.coefficients[i] != NumT()) {
      if (!firstTerm) {
        os << " + ";
      }
      os << p.coefficients[i] << "*x^" << i;
      firstTerm = false;
    }
  }
  if (firstTerm) {
    os << "0";
  }
  return os;
}

#endif
