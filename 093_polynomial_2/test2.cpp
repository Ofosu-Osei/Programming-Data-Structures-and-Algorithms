#include <complex>
#include <cstdlib>

#include "poly.hpp"

int main(void) {
  Polynomial<int> p1;
  p1.addTerm(4, 4);
  p1.addTerm(2, 3);
  p1.addTerm(-7, 2);
  p1.addTerm(-9, 0);
  std::cout << "p1: " << p1 << "\n";
  std::cout << "p1': " << p1.derivative() << "\n";
  Polynomial<int> p2;
  p2.addTerm(6, 6);
  p2.addTerm(-3, 3);
  p2.addTerm(4, 0);
  std::cout << "p2: " << p2 << "\n";
  std::cout << "p2': " << p2.derivative() << "\n";
  std::cout << "p2'': " << p2.derivative().derivative() << "\n";
  Polynomial<int> p3;
  p3.addTerm(4, 0);
  p3.addTerm(5, 1);
  std::cout << "p3: " << p3 << "\n";
  std::cout << "p3': " << p3.derivative() << "\n";
  Polynomial<int> p4;
  p4.addTerm(3, 0);
  p4.addTerm(2, 1);
  std::cout << "p4: " << p4 << "\n";
  std::cout << "p4': " << p4.derivative() << "\n";
  std::cout << "p4'': " << p4.derivative().derivative() << "\n";
  for (int i = -5; i < 15; i += 3) {
    std::cout << "p1(" << i << ") = " << p1.eval(i) << "\n";
    std::cout << "p2(" << i << ") = " << p2.derivative()(i)
              << "\n";  //like p4.derivative().eval(i)
    std::cout << "p3'(" << i << ") = " << p3.derivative().eval(i) << "\n";
    std::cout << "p4'(" << i << ") = " << p4(i) << "\n";  //like p2.eval(i)
  }
  Polynomial<std::complex<double> > pcomplex;
  pcomplex.addTerm(std::complex<double>(2.3, 4.2), 4);
  pcomplex.addTerm(std::complex<double>(-3.9, 14.8), 2);
  pcomplex.addTerm(std::complex<double>(0.3, -9.2), 1);
  std::cout << "pcomplex.eval(4.2 - i) = " << pcomplex.eval(std::complex<double>(4.2, -1))
            << "\n";
  std::cout << "derivative of pcomplex is " << pcomplex.derivative() << "\n";
  return EXIT_SUCCESS;
}
