#pragma once

#include <utility>

#define _MY_BEGIN namespace my {
#define _MY_END }

#define _HIDDEN_BEGIN namespace hidden {
#define _HIDDEN_END }

#define _DEFAULT_BEGIN namespace Default {
#define _DEFAULT_END }

#define ___BEGIN_OF___(X)
#define ___END_OF___(X)

#define BEGIN_NAMESPACE (x)
#define END_NAMESPACE (x)

#define STRUCT(X)
#define CLASS(x)
#define VARIABLE(x)

#define ICS inline const static
#define ICSB ICS bool

#define _IMPLEMENTATION_BEGIN namespace implementation {
#define _IMPLEMENTATION_END }

template <class T>
void put (const T* const A, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
}

_MY_BEGIN
_HIDDEN_BEGIN
_IMPLEMENTATION_BEGIN

// A <- B
template <class T>
void Copy (T* const A, const T* const B, size_t N) {
  for (size_t i = 0; i < N; i++) {
    A[i] = B[i];
  }
}

template <typename T>
void Swap (T& var1, T& var2) {
  T var = var1;
  var1 = var2;
  var2 = var;
}
template <class T>
void Swap_array_elems (T* const A, T* const B, size_t N) {
  for (size_t i = 0; i < N; i++) {
    Swap(A[i], B[i]);
  }
}

template <class T> T Min(const T& a, const T& b) { return (a < b ? a : b); }
template <class T> T Max(const T& a, const T& b) { return (a > b ? a : b); }

template <class T>
size_t BinSearch (const T value, const T* const array, size_t left_bound, size_t right_bound) {
  if (value <= array[left_bound]) {
    return left_bound;
  }
  if (array[right_bound-1] <= value) {
    return right_bound;
  }
  if (right_bound - left_bound <= 2){
    return left_bound;
  }
  size_t mid = (right_bound + left_bound)/2;
  if (array[mid] > value) {
    return BinSearch(value, array, left_bound, mid);
  } else {
    return BinSearch(value, array, mid, right_bound);
  }
}


namespace sort
{
namespace InsertionSort
{
  template <class T>
  void InsertionSort(T* const array, size_t size) {
    int j = 0;
    for (size_t i = 1; i < size; i++) {
      j = i;
      while (j > 0 && array[j] < array[j-1]) {
        Swap (array[j - 1], array[j]);
        --j;
      }
    }
  }
}

namespace BubbleSort
{
  template <class T>
  void BubbleSort(T* const array, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
      for (size_t j = 0; j < size - 1 - i; ++j)
        if (array[j] > array[j+1])
          Swap (array[j], array[j+1]);
  }
}

namespace MergeSort
{
  template <class T>
  void Reverse(T* const A, size_t a) {
    for (size_t i = 0; i < a / 2; i++) {
      Swap(A[i], A[a - i]);
    }
  }

  template <class T>
  void Rotate(T* const A, size_t left, size_t right) {
    Reverse(A, left + right);
    Reverse(A, right);
    Reverse(A + right, left);
  }

  template <class T>
  void Merge (T* const A, size_t size_A, const T* const B, size_t size_B, T* const new_arr) {
    size_t ia, ib, ic;
    ia = ib = ic = 0;
    size_t new_size = size_A + size_B;
    while (ic < new_size) {
      if ((ia < size_A && A[ia] < B[ib]) || ib >= size_B) {
        new_arr[ic++] = A[ia++];
      } else {
        new_arr[ic++] = B[ib++];
      }
    }
  }

  template <class T> // O(n*log(n))
  void MergeSort(T* const array, size_t size) {
    T* const auxilary_array = new T[size];
    T* lsa = nullptr;
    T* rsa = nullptr;
    size_t rsas = 0;

    for (size_t lsas = 1; lsas < size; lsas *= 2) {
      for (size_t j = 0; j < size; j += (2 * lsas)) {
        lsa = array + j;
        rsa = lsa + lsas;
        if (j + 2*lsas > size) {
          rsas = size - j - lsas; // j + lsas + rsas = size
        } else {
          rsas = lsas;
        }
        Merge(lsa, lsas, rsa, rsas, auxilary_array);
        Copy(lsa, auxilary_array, lsas + rsas);
      }
    }

    delete[] auxilary_array;
  }

  template <class T>
  void InplaceMerge(T* const array, size_t left_sub_array_size, size_t right_sub_array_size) {
    if (left_sub_array_size == 0 || right_sub_array_size == 0) {
      return;
    }
    if (left_sub_array_size == 1 && right_sub_array_size == 1) {
      if (array[0] > array[1]) {
        Swap(array[0], array[1]);
      }
      return;
    }
    T* const left_sub_array = array;
    T* const right_sub_array = array + left_sub_array_size;
    const size_t mid_left = left_sub_array_size / 2;
    const T pivot_value = array[mid_left];
    const size_t median = BinSearch (pivot_value, right_sub_array, 0, right_sub_array_size);
    Rotate(left_sub_array + mid_left, left_sub_array_size - mid_left, median);
    InplaceMerge(left_sub_array, mid_left, median);
    InplaceMerge(array + mid_left + median, left_sub_array_size - mid_left, right_sub_array_size - median);
  }

  template <class T>
  void InplaceMergeSort(T* const array, size_t size) {
    for (size_t i = 1; i < size; i *= 2)
      for (size_t j = 0; j < size - 2 * i; j += 2 * i)
        InplaceMerge(array + j, i, (j + 2 * i < size ? j + 2 * i : size - j - i));
  }
  
  template <class T>
  void InplaceMergeSort_recursive(T* const array, size_t size) {
    size_t mid = size/2;
    InplaceMergeSort_recursive(array, mid);
    InplaceMergeSort_recursive(array + mid, size - mid);
    InplaceMerge(array, mid, size-mid);
  }
}

namespace QuickSort
{
  namespace Partitions
  {
    template <class T>
    size_t Lomuto(T* const A, size_t left_bound, size_t right_bound) {
      size_t pivot_ptr = left_bound;
      const T pivot_val = A[pivot_ptr];
      for (size_t i = left_bound; i < right_bound; i++) {
        if (A[i] < pivot_val){
          Swap(A[++pivot_ptr], A[i]);
        }
      }
      Swap(A[left_bound], A[pivot_ptr]);
      return pivot_ptr;
    }

    template <class T>
    size_t Hoare (T* const A, size_t left_bound, size_t right_bound) {
      const T pivot_val = A[(right_bound+left_bound)/2];
      size_t i = left_bound;
      size_t j = right_bound-1;
      while(i <= j){
        while (A[i] < pivot_val)
          i++;
        while (A[j] > pivot_val)
          j--;
        if (i >= j)
          break;
        Swap(A[i++], A[j--]);
      }
      return j;
    }

    template <class T> size_t ThreeParts() {return 0;} //?
  }

  template <class T, class... Args>
  void QuickSort (T* const array, size_t left_bound, size_t right_bound, size_t (&partition_function)(T*, size_t, size_t) = Partitions::Lomuto<T>) {
    size_t size = right_bound - left_bound;
    if (size <= 1) return;  
    size_t pivot_ptr = partition_function(array, left_bound, right_bound);
    QuickSort(array, left_bound, pivot_ptr, partition_function);
    QuickSort(array, pivot_ptr+1, right_bound, partition_function);
  }

  void QuickSortLomuto(int* array, size_t left, size_t right) {
    if (right - left <= 1) {
      return;
    }

    int pivot = array[right - 1];

    size_t index = left;
    for (size_t i = left; i < right - 1; ++i) {
      if (array[i] < pivot) {
        Swap(array[i], array[index]);
        ++index;
      }
    }
    Swap(array[index], array[right - 1]);

    QuickSortLomuto(array, left, index);
    QuickSortLomuto(array, index + 1, right);
  }
}

namespace HeapSort
{
  template <class T = size_t>
  T Parent (const T i) {return (i-1)/2;}
  template <class T = size_t>
  T LeftChild (const T i) {return 2*i+1;}
  template <class T = size_t>
  T RightChild (const T i) {return 2*i+1;}
  
  template <class T>
  void SiftDown (T* const array, size_t i, size_t size) {
    size_t left = LeftChild(i);
    size_t right = RightChild(i);
    size_t largest = i;
    if (left < size && array[left] > array[largest]) {
      largest = left;
    } if (right < size && array[right] > array[largest]) {
      largest = right;
    }
    if (largest != i) {
      Swap(array[i], array[largest]);
      SwiftDown (array, largest, size);
    }
  }
  template <class T>
  void SiftUp (T* const array, size_t i) {
    size_t parent = Parent(i);
    if (i > 0 && array[parent] < array[i]) {
      Swap(array[i], array[parent]);
      SwiftUp (array, parent);
    }
  }

  template <class T>
  void BuildHeap (T* const A, size_t size) {
    for (size_t i = (size-1)/2; i >= 0; i--)
      SiftDown (A, i, size);
  }

  template <class T>
  void HeapSort (const T* const array, size_t size) {
    
  }
}
}

_IMPLEMENTATION_END
_HIDDEN_END
_MY_END

template <class T>
void Sort(T* const begin, T* const end) {
  my::hidden::implementation::sort::MergeSort::MergeSort(begin, end - begin);
}