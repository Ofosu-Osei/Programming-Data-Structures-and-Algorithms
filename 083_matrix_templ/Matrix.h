#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c)) {}

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  Matrix & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      rows = rhs.rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (this->numRows != rhs.getRows()) {
      return false;
    }
    if (this->numColumns != rhs.getColumns()) {
      return false;
    }
    if (this->rows != rhs.rows) {
      return false;
    }

    return true;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(this->numRows == rhs.getRows() && this->numColumns == rhs.getColumns());
    Matrix ans(*this);
    for (int i = 0; i < ans.getRows(); i++) {
      for (int j = 0; j < ans.getColumns(); j++) {
        ans[i][j] = ans[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & v) {
  s << "{";
  for (size_t i = 0; i < v.size(); i++) {
    if (i > 0) {
      s << ", ";
    }
    s << v[i];
  }
  s << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
#endif
