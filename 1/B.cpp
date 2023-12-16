#include <iostream>
#include "B3.h"

template <class T>
T f(T x) {
  return 2*x + 1;
}

template <class T>
void test (size_t n) {
  std::cout << "test: n = " << n << std::endl;

  auto A = new T [n];
  for (size_t i = 0; i < n; i++) {
    A[i] = f(i);
  }

  std::cout << "Array: ";
  for(size_t i = 0; i < n; i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;

  auto begin = A;
  auto end = A+n;

  for (size_t i = 0; i < f(n); i++) {
    auto value = i;
    std::cout << value << ": " 
    << BinarySearch<T>(begin, end, value) << " "
    << *LowerBound<T>(begin, end, value) << " "
    << *UpperBound<T>(begin, end, value) << " "
    << (LowerBound<T>(begin, end, value) == end) << " "
    << (UpperBound<T>(begin, end, value) == end) << " "
    << std::endl;
  }

  std::cout << std::endl;

  delete[] A;
}

int main() {
  test<int>(0);
  test<int>(1);
  test<int>(10);

  size_t n = 5;
  int A[5]{1, 2, 3, 3, 5};
  using T = int;

  auto begin = A;
  auto end = A+n;
}
