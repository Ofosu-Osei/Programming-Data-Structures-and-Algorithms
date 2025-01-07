#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * frequencies = new uint64_t[257]();

  std::ifstream file(fname, std::istream::in);
  if (!file.is_open()) {
    std::cerr << "Could not open file.\n";
    exit(EXIT_FAILURE);
  }

  char c;
  while (file.get(c)) {
    frequencies[static_cast<unsigned char>(c)]++;
  }

  frequencies[256] = 1;

  file.close();

  return frequencies;
}
