#include <complex>
#include <cstdlib>

#include "poly.hpp"
#define DERIV_TOLERANCE 0.000001

int main(void) {
  Polynomial<int> pint;
  pint.addTerm(3, 4);
  pint.addTerm(2, 5);
  Polynomial<double> pdouble = pint.convert<double>();
  pdouble *= 1.5;
  std::cout << "pdouble is now " << pdouble << "\n";
  std::cout << "or on complex" << pdouble.convert<std::complex<double> >() << "\n";
  Polynomial<double> p1;
  p1.addTerm(4, 4);
  p1.addTerm(2, 3);
  p1.addTerm(-7, 2);
  p1.addTerm(-9, 0);
  std::cout << "p1: " << p1 << "\n";
  double z1 = p1.findZero(-1.5, 5, 0.0001, DERIV_TOLERANCE);
  std::cout << "First zero: " << z1 << "\n";
  double z2 = p1.findZero(2, 10, 0.0001, DERIV_TOLERANCE);
  std::cout << "Second zero: " << z2 << "\n";
  try {
    double zbogus = p1.findZero(0, 20, 0.00001, DERIV_TOLERANCE);
    std::cout << "Should not have gotten: " << zbogus << "\n";
  }
  catch (convergence_failure<double> & cf) {
    std::cout << "Failed to converge. Last x was " << cf.value << "\n";
  }
  try {
    double zbogus = p1.findZero(0.0001, 20, 0.00001, DERIV_TOLERANCE);
    std::cout << "Should not have gotten: " << zbogus << "\n";
  }
  catch (convergence_failure<double> & cf) {
    std::cout << "Failed to converge. Last x was " << cf.value << "\n";
  }
  double z3 = p1.findZero(0.0001, 35, 0.00001, DERIV_TOLERANCE);
  std::cout << "But will converge to " << z3 << " with more steps\n";

  Polynomial<std::complex<double> > pc;
  pc.addTerm(std::complex<double>(-2.5, 1.0), 0);
  pc.addTerm(std::complex<double>(2.0, 1.5), 1);
  std::cout << "pc is " << pc << "\n";  //pc is (2+1.5i)* x + (-2.5 + i)
  std::cout << "zero of pc is "
            << pc.findZero(std::complex<double>(), 20, 0.0001, DERIV_TOLERANCE) << "\n";
  return EXIT_SUCCESS;
}
