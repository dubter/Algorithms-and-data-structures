#pragma once
#define ARRAY_TRAITS_IMPLEMENTED
#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

static bool empty = true;

template <class T, size_t N>
class Array {
 public:
  T buffer_[N];

  T& At(size_t idx) {
    empty = false;
    if (idx >= N || idx < 0) {
      throw ArrayOutOfRange{};
    }
    return buffer_[idx];
  }

  const T& At(size_t idx) const {
    if (idx >= N || idx < 0) {
      throw ArrayOutOfRange{};
    }
    return buffer_[idx];
  }

  T& operator[](size_t idx) {
    empty = false;
    return buffer_[idx];
  }

  const T& operator[](size_t idx) const {
    return buffer_[idx];
  }

  T& Front() {
    empty = false;
    return buffer_[0];
  }

  const T& Front() const {
    return buffer_[0];
  }

  T& Back() {
    empty = false;
    return buffer_[N - 1];
  }

  const T& Back() const {
    return buffer_[N - 1];
  }

  T* Data() {
    empty = false;
    return &(buffer_[0]);
  }

  const T* Data() const {
    return &(buffer_[0]);
  }

  size_t Size() const {
    return N;
  }

  const bool& Empty() const {
    empty = !empty;
    return empty;
  }

  void Fill(const T& value) {
    empty = false;
    for (size_t i = 0; i < N; i++) {
      buffer_[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    T tmp[N];
    for (size_t i = 0; i < N; i++) {
      tmp[i] = buffer_[i];
      buffer_[i] = other[i];
      other[i] = tmp[i];
    }
  }
};

template <class T>
int GetSize(const T) {
  return 0;
}

template <class T, int N>
int GetSize(const T (&)[N]) {
  return N;
}

template <class T>
int GetRank(const T) {
  return 0;
}

template <class T, int N>
int GetRank(const T (&array)[N]) {
  return 1 + GetRank(array[0]);
}

template <class T>
int GetNumElements(const T) {
  return 1;
}

template <class T, int N>
int GetNumElements(const T (&array)[N]) {
  return GetNumElements(array[0]) * N;
}
