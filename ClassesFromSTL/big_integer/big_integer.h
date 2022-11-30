#pragma once

#include "array.h"

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigInteger {
 private:
  Array data_;
  int64_t size_;
  enum class Sign { NEGATIVE, POSITIVE } sign_;
  enum class Base { BASE_LEN = 9, BASE_VALUE = 1000000000 };

 public:
  BigInteger() = default;
  BigInteger(int64_t val);      // NOLINT
  BigInteger(int32_t val);      // NOLINT
  BigInteger(const char *str);  // NOLINT
  BigInteger(const BigInteger &other);

  int64_t GetSize() const;

  void SetSize(int64_t val);
  void SetSign(BigInteger::Sign val);

  int64_t &operator[](int64_t pos);
  const int64_t &operator[](int64_t pos) const;

  bool IsNegative() const;

  BigInteger &operator=(const BigInteger &other);

  BigInteger operator-() const;
  BigInteger operator+() const;

  BigInteger &operator++();
  BigInteger &operator--();
  BigInteger operator++(int);
  BigInteger operator--(int);

  friend bool operator<(const BigInteger &num1, const BigInteger &num2);
  friend bool operator==(const BigInteger &num1, const BigInteger &num2);
  friend bool operator>(const BigInteger &num1, const BigInteger &num2);
  friend bool operator!=(const BigInteger &num1, const BigInteger &num2);
  friend bool operator<=(const BigInteger &num1, const BigInteger &num2);
  friend bool operator>=(const BigInteger &num1, const BigInteger &num2);

  friend BigInteger &operator+=(BigInteger &num1, const BigInteger &num2);
  friend BigInteger &operator-=(BigInteger &num1, const BigInteger &num2);
  friend BigInteger &operator*=(BigInteger &num1, const BigInteger &num2);

  friend BigInteger operator+(const BigInteger &num1, const BigInteger &num2);
  friend BigInteger operator-(const BigInteger &num1, const BigInteger &num2);
  friend BigInteger operator*(const BigInteger &num1, const BigInteger &num2);

  friend std::ostream &operator<<(std::ostream &os, const BigInteger &num);
  friend std::istream &operator>>(std::istream &is, BigInteger &num);
};