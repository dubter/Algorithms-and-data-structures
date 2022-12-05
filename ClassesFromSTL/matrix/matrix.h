#pragma once
#include <stdexcept>
#include <iostream>
#include <sstream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t M, size_t N>
class Matrix {
 public:
  T matrix[M][N];

  size_t RowsNumber() const {
    return M;
  }

  size_t ColumnsNumber() const {
    return N;
  }

  const T &operator()(const size_t &first, const size_t &second) const {
    return matrix[first][second];
  }

  T &operator()(const size_t &first, const size_t &second) {
    return matrix[first][second];
  }

  const T &At(const size_t &first, const size_t &second) const {
    if (first >= M || second >= N) {
      throw MatrixOutOfRange{};
    }
    return matrix[first][second];
  }

  T &At(const size_t &first, const size_t &second) {
    if (first >= M || second >= N) {
      throw MatrixOutOfRange{};
    }
    return matrix[first][second];
  }

  Matrix<T, M, N> operator+(const Matrix<T, M, N> &matrix1) const {
    if (M != matrix1.RowsNumber() || N != matrix1.ColumnsNumber()) {
      throw MatrixIsDegenerateError{};
    }
    Matrix<T, M, N> matrix2;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix2.matrix[i][j] = matrix[i][j] + matrix1.matrix[i][j];
      }
    }
    return matrix2;
  }

  Matrix<T, M, N> operator-(const Matrix<T, M, N> &matrix1) const {
    if (M != matrix1.RowsNumber() || N != matrix1.ColumnsNumber()) {
      throw MatrixIsDegenerateError{};
    }
    Matrix<T, M, N> matrix2;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix2.matrix[i][j] = matrix[i][j] - matrix1.matrix[i][j];
      }
    }
    return matrix2;
  }

  Matrix<T, M, N> &operator+=(const Matrix<T, M, N> &matrix1) {
    if (M != matrix1.RowsNumber() || N != matrix1.ColumnsNumber()) {
      throw MatrixIsDegenerateError{};
    }
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix[i][j] += matrix1.matrix[i][j];
      }
    }
    return *this;
  }

  Matrix &operator-=(const Matrix &matrix1) {
    if (M != matrix1.RowsNumber() || N != matrix1.ColumnsNumber()) {
      throw MatrixIsDegenerateError{};
    }
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix[i][j] -= matrix1.matrix[i][j];
      }
    }
    return *this;
  }

  Matrix operator*(const T &num) const {
    Matrix matrix1;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix1.matrix[i][j] = matrix[i][j] * num;
      }
    }
    return matrix1;
  }

  Matrix operator/(const T &num) const {
    Matrix matrix1;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix1.matrix[i][j] = matrix[i][j] / num;
      }
    }
    return matrix1;
  }

  Matrix &operator*=(const T &num) {
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix[i][j] *= num;
      }
    }
    return *this;
  }

  Matrix &operator/=(const T &num) {
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        matrix[i][j] /= num;
      }
    }
    return *this;
  }

  bool operator==(const Matrix &matrix1) const {
    if (N != matrix1.ColumnsNumber() || M != matrix1.RowsNumber()) {
      throw MatrixIsDegenerateError{};
    }
    bool result = true;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        if (matrix1.matrix[i][j] != matrix[i][j]) {
          result = false;
          break;
        }
      }
    }
    return result;
  }

  bool operator!=(const Matrix &matrix1) const {
    return !(*this == matrix1);
  }
};

template <class T, size_t M, size_t N>
Matrix<T, N, M> GetTransposed(const Matrix<T, M, N> &matrix1) {
  Matrix<T, N, M> matrix2;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix2.matrix[i][j] = matrix1.matrix[j][i];
    }
  }
  return matrix2;
}

template <class G, class T, size_t M, size_t N>
Matrix<T, M, N> operator*(const G &num, const Matrix<T, M, N> &matrix1) {
  Matrix<T, M, N> matrix2;
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix2.matrix[i][j] = num * matrix1.matrix[i][j];
    }
  }
  return matrix2;
}

template <class T, size_t M, size_t N>
Matrix<T, M, N> operator/(const T &num, const Matrix<T, M, N> &matrix1) {
  Matrix<T, M, N> matrix2;
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix2.matrix[i][j] = matrix1.matrix[i][j] * num;
    }
  }
  return matrix2;
}

template <class T, size_t M, size_t N>
std::ostream &operator<<(std::ostream &os, const Matrix<T, M, N> &matrix1) {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      os << matrix1.matrix[i][j];
      if (j != N - 1) {
        os << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

template <class T, size_t M, size_t N>
std::istream &operator>>(std::istream &is, Matrix<T, M, N> &matrix1) {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      is >> matrix1.matrix[i][j];
    }
  }
  return is;
}

template <class T, size_t M, size_t N, size_t K>
Matrix<T, M, K> operator*(const Matrix<T, M, N> &matrix, const Matrix<T, N, K> &matrix1) {
  if (N != matrix1.RowsNumber()) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, M, K> matrix2;
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      for (size_t k = 0; k < N; k++) {
        matrix2.matrix[i][j] += matrix.matrix[i][k] * matrix1.matrix[k][j];
      }
    }
  }
  return matrix2;
}

template <class T, size_t M, size_t N, size_t K>
Matrix<T, M, K> &operator*=(Matrix<T, M, N> &matrix1, const Matrix<T, N, K> &matrix2) {
  if (N != matrix2.RowsNumber()) {
    throw MatrixIsDegenerateError{};
  }
  T tmp[M][K] = {};
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      for (size_t k = 0; k < N; k++) {
        tmp[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
      }
    }
  }
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      matrix1.matrix[i][j] = tmp[i][j];
    }
  }
  return matrix1;
}