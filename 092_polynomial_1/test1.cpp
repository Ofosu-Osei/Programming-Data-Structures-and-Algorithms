#include <complex>
#include <cstdlib>

#include "poly.hpp"

int main(void) {
  Polynomial<int> p0;
  std::cout << "default poly (p0): " << p0 << "\n";
  Polynomial<int> p1;
  p1.addTerm(4, 4);
  p1.addTerm(2, 3);
  p1.addTerm(-7, 2);
  p1.addTerm(-9, 0);
  std::cout << "p1: " << p1 << "\n";
  std::cout << "-p1: " << -p1 << "\n";
  Polynomial<int> p2;
  p2.addTerm(6, 6);
  p2.addTerm(-3, 3);
  p2.addTerm(4, 0);
  std::cout << "p2: " << p2 << "\n";
  std::cout << "p1 + p2: " << p1 + p2 << "\n";
  std::cout << "p1 * p2: " << p1 * p2 << "\n";
  std::cout << "p1 - p2: " << p1 - p2 << "\n";
  Polynomial<int> p3;
  p3.addTerm(4, 0);
  p3.addTerm(5, 1);
  std::cout << "p3: " << p3 << "\n";
  Polynomial<int> temp(p1);
  std::cout << "temp is " << temp << "\n";
  temp = p3;
  std::cout << "after assignment, temp is " << temp << "\n";
  Polynomial<int> p4;
  p4.addTerm(3, 0);
  p4.addTerm(2, 1);
  std::cout << "p4: " << p4 << "\n";
  std::cout << "p3 * p4: " << p3 * p4 << "\n";
  p3 += p4;
  std::cout << "p3v2: " << p3 << "\n";
  p3 *= p4;
  std::cout << "p3v3: " << p3 << "\n";
  p3 -= p4;
  std::cout << "p3v4: " << p3 << "\n";
  p4 *= 3;
  std::cout << "p4v2: " << p4 << "\n";
  Polynomial<int> p5;
  p5.addTerm(6, 1);
  p5.addTerm(9, 0);
  std::cout << "p5: " << p5 << "\n";
  std::cout << "(p5-p4) * (p3+p2) + p1 = " << (p5 - p4) * (p3 + p2) + p1 << "\n";
  std::vector<Polynomial<int> > polys;
  polys.push_back(p0);
  polys.push_back(p1);
  polys.push_back(p2);
  polys.push_back(p3);
  polys.push_back(p4);
  polys.push_back(p5);
  Polynomial<int> p6;
  p6.addTerm(6, 6);
  p6.addTerm(-3, 3);
  p6.addTerm(6, 1);
  p6.addTerm(13, 0);
  polys.push_back(p6);
  polys[6] -= p2;  //note that polys[6] now should == p5
  std::cout << "polys[6] = " << polys[6] << "\n";

  for (size_t i = 0; i < polys.size(); i++) {
    for (size_t j = 0; j < polys.size(); j++) {
      std::cout << "polys[" << i << "] == polys[" << j << "] ? " << (polys[i] == polys[j])
                << "  [" << polys[i] << " == " << polys[j] << " ]\n";
      std::cout << "polys[" << i << "] != polys[" << j << "] ? " << (polys[i] != polys[j])
                << "  [" << polys[i] << " != " << polys[j] << " ]\n";
    }
    std::cout << "polys[" << i << "] - polys[" << i << "] == p0 ? "
              << ((polys[i] - polys[i]) == p0) << "\n";
    std::cout << "polys[" << i << "] - polys[" << i << "] != p0 ? "
              << ((polys[i] - polys[i]) != p0) << "\n";
  }
  Polynomial<double> pd1;
  pd1.addTerm(6.3, 2);
  pd1.addTerm(7.4, 4);
  std::cout << "pd1 is " << pd1 << "\n";
  pd1 *= 4.2;
  std::cout << "pd1 is now " << pd1 << "\n";
  std::cout << "pd1 * 3.1 is " << pd1 * 3.1 << "\n";
  Polynomial<std::complex<double> > pc1;
  pc1.addTerm(std::complex<double>(2.2, 3.1), 3);
  std::cout << "pc1 is " << pc1 << "\n";
  return EXIT_SUCCESS;
}
