#pragma once
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int64_t numerator_;
  int64_t denominator_;
  void Normalize();

 public:
  Rational();
  Rational(int64_t val);  // NOLINT
  Rational(int64_t x, int64_t y);
  Rational(const Rational &other);

  int64_t GetNumerator() const;
  int64_t GetDenominator() const;

  void SetNumerator(int64_t x);
  void SetDenominator(int64_t y);

  Rational &operator=(const Rational &other);

  friend bool operator==(const Rational &num1, const Rational &num2);
  friend bool operator<(const Rational &num1, const Rational &num2);
  friend bool operator>(const Rational &num1, const Rational &num2);
  friend bool operator!=(const Rational &num1, const Rational &num2);
  friend bool operator<=(const Rational &num1, const Rational &num2);
  friend bool operator>=(const Rational &num1, const Rational &num2);

  friend Rational operator+(const Rational &num1, const Rational &num2);
  friend Rational operator-(const Rational &num1, const Rational &num2);
  friend Rational operator*(const Rational &num1, const Rational &num2);
  friend Rational operator/(const Rational &num1, const Rational &num2);
  friend Rational &operator+=(Rational &num1, const Rational &num2);
  friend Rational &operator-=(Rational &num1, const Rational &num2);
  friend Rational &operator*=(Rational &num1, const Rational &num2);
  friend Rational &operator/=(Rational &num1, const Rational &num2);
  friend Rational operator+(const Rational &num1);
  friend Rational operator-(const Rational &num1);
  friend Rational &operator++(Rational &num1);
  friend Rational &operator--(Rational &num1);
  friend Rational operator++(Rational &num1, int);
  friend Rational operator--(Rational &num1, int);

  friend std::ostream &operator<<(std::ostream &os, const Rational &value);
  friend std::istream &operator>>(std::istream &is, Rational &value);
};