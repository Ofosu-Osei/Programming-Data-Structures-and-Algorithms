#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    this->rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    this->rows[i] = new IntArray(*rhs.rows[i]);
  }
}

IntMatrix::~IntMatrix() {
  if (rows != NULL) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** tempArray = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      tempArray[i] = new IntArray(*rhs.rows[i]);
    }
    if (rows != NULL) {
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
    }
    rows = tempArray;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this->numRows != rhs.getRows()) {
    return false;
  }
  if (this->numColumns != rhs.getColumns()) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.getRows() && this->numColumns == rhs.getColumns());
  IntMatrix ans(*this);
  for (int i = 0; i < ans.getRows(); i++) {
    for (int j = 0; j < ans.getColumns(); j++) {
      ans[i][j] = ans[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
