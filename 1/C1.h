#pragma once

#include <cstdint>

template <class T>
void Copy(T* A, const T* B, uint64_t N) {
  for (uint64_t i = 0; i < N; i++) {
    A[i] = B[i];
  }
}

template <class T>
void Merge(const T* A, uint64_t size_A, const T* B, uint64_t size_B, T* new_arr) {
  uint64_t ia, ib, ic;
  ia = ib = ic = 0;
  uint64_t new_size = size_A + size_B;
  while (ic < new_size) {
    if (ia < size_A) {
      if (ib < size_B) {
        if (A[ia] < B[ib]) {
          new_arr[ic] = A[ia++];
        } else {
          new_arr[ic] = B[ib++];
        }
      } else {
        new_arr[ic] = A[ia++];
      }
    } else {
      if (ib < size_B) {
        new_arr[ic] = B[ib++];
      } else {
        break;
      }
    }
    ++ic;
  }
}

template <class T>  // O(n*log(n))
void MergeSort(T* array, uint64_t size) {
  T* const auxilary_array = new T[size];
  T* left = nullptr;
  T* right = nullptr;
  uint64_t rs = 0;

  for (uint64_t ls = 1; ls < size; ls *= 2) {
    for (uint64_t step = 0; step < size - ls; step += (2 * ls)) {
      left = array + step;
      right = left + ls;
      if (step + 2 * ls > size) {
        rs = size - step - ls;  // j + lsas + rsas = size
      } else {
        rs = ls;
      }
      Merge(left, ls, right, rs, auxilary_array);
      Copy(left, auxilary_array, ls + rs);
    }
  }

  delete[] auxilary_array;
}

template <class T>
void Sort(T* begin, T* end) {
  MergeSort(begin, end - begin);
}