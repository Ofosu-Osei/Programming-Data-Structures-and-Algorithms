#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}

IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]), numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    this->data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  if (data != NULL) {
    delete[] data;
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] this->data;
    this->numElements = rhs.numElements;
    this->data = new int[this->numElements];
    for (int i = 0; i < this->numElements; i++) {
      this->data[i] = rhs.data[i];
    }
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < this->numElements; i++) {
    if (this->data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & stream, const IntArray & rhs) {
  stream.write("{", 1);
  for (int i = 0; i < rhs.size(); i++) {
    stream << rhs[i];
    if (i != rhs.size() - 1) {
      stream.write(", ", 2);
    }
  }
  stream.write("}", 1);
  return stream;
}
