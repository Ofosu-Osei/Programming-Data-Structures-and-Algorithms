#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream & operator<<(ostream & s, const vector<T> & v) {
  for (size_t i = 0; i < v.size(); i++) {
    if (i > 0) {
      s << "\n";
    }
    s << v[i];
  }
  return s;
}

vector<string> readInput(istream & in) {
  string line;
  vector<string> input;
  while (getline(in, line)) {
    input.push_back(line);
  }
  return input;
}

int main(int argc, char * argv[]) {
  vector<string> lines;
  if (argc < 2) {
    lines = readInput(cin);
    sort(lines.begin(), lines.end());
    cout << lines << endl;
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream file(argv[i]);
      if (file.is_open()) {
        lines = readInput(file);
        sort(lines.begin(), lines.end());
        cout << lines << endl;
      }
      else {
        cerr << "Input File Error: Could not open file: " << argv[i] << endl;
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
