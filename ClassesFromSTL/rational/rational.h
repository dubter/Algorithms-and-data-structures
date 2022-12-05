#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int32_t numerator_;
  int32_t denominator_;

 public:
  Rational();
  Rational(const int32_t &numerator);  // NOLINT
  Rational(int32_t numerator, int32_t denominator);
  const int32_t &GetNumerator() const;
  const int32_t &GetDenominator() const;
  void SetNumerator(const int32_t &numerator);
  void SetDenominator(const int32_t &denominator);
  void SetNumeratorWithOutUpdate(const int32_t &numerator);
  void SetDenominatorWithOutUpdate(const int32_t &denominator);
  Rational operator+(const Rational &second) const;
  Rational operator-(const Rational &second) const;
  Rational operator*(const Rational &second) const;
  Rational operator/(const Rational &second) const;
  Rational &operator+=(const Rational &second);
  Rational &operator-=(const Rational &second);
  Rational &operator*=(const Rational &second);
  Rational &operator/=(const Rational &second);
  Rational operator+() const;
  Rational operator-() const;
  Rational &operator++();
  Rational operator++(int);
  Rational &operator--();
  Rational operator--(int);
  bool operator>(const Rational &second) const;
  bool operator<(const Rational &second) const;
  bool operator>=(const Rational &second) const;
  bool operator<=(const Rational &second) const;
  bool operator==(const Rational &second) const;
  bool operator!=(const Rational &second) const;
  void Reduction();
  friend std::ostream &operator<<(std::ostream &os, const Rational &second);
  friend std::istream &operator>>(std::istream &is, Rational &second);
};

std::ostream &operator<<(std::ostream &os, const Rational &second);
std::istream &operator>>(std::istream &is, const Rational &second);
bool operator>(const int &first, const Rational &second);
bool operator<(const int &first, const Rational &second);
bool operator>=(const int &first, const Rational &second);
bool operator<=(const int &first, const Rational &second);
bool operator==(const int &first, const Rational &second);
bool operator!=(const int &first, const Rational &second);
bool operator>(const Rational &first, const int &second);
bool operator<(const Rational &first, const int &second);
bool operator>=(const Rational &first, const int &second);
bool operator<=(const Rational &first, const int &second);
bool operator==(const Rational &first, const int &second);
bool operator!=(const Rational &first, const int &second);