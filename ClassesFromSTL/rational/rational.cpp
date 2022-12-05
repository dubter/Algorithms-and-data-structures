#include <iostream>
#include "rational.h"
#include "gcd.h"

void Rational::Reduction() {
  int sign = 1;
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if ((numerator_ * denominator_ < 0)) {
    sign = -1;
  }
  int32_t gcd = Gcd(abs(numerator_), abs(denominator_));
  numerator_ = sign * abs(numerator_) / gcd;
  denominator_ = abs(denominator_) / gcd;
}

Rational::Rational() {
  numerator_ = 0;
  denominator_ = 1;
}

Rational::Rational(const int32_t &numerator) {
  numerator_ = numerator;
  denominator_ = 1;
}

Rational::Rational(int32_t numerator, int32_t denominator) {
  numerator_ = numerator;
  denominator_ = denominator;
  Reduction();
}

const int32_t &Rational::GetNumerator() const {
  return numerator_;
}

const int32_t &Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(const int32_t &numerator) {
  numerator_ = numerator;
  Reduction();
}

void Rational::SetDenominator(const int32_t &denominator) {
  denominator_ = denominator;
  Reduction();
}

Rational &Rational::operator+=(const Rational &second) {
  int32_t scm = denominator_ * second.denominator_ / Gcd(denominator_, second.denominator_);
  int32_t denominator1 = scm;
  int32_t numerator1 = numerator_ * (scm / denominator_) + second.numerator_ * (scm / second.denominator_);
  denominator_ = denominator1;
  numerator_ = numerator1;
  Reduction();
  return *this;
}

Rational &Rational::operator-=(const Rational &second) {
  int32_t scm = denominator_ * second.denominator_ / Gcd(denominator_, second.denominator_);
  int32_t denominator1 = scm;
  int32_t numerator1 = numerator_ * (scm / denominator_) - second.numerator_ * (scm / second.denominator_);
  denominator_ = denominator1;
  numerator_ = numerator1;
  Reduction();
  return *this;
}

Rational &Rational::operator*=(const Rational &second) {
  int32_t denominator1 = denominator_ * second.denominator_;
  int32_t numerator1 = numerator_ * second.numerator_;
  denominator_ = denominator1;
  numerator_ = numerator1;
  Reduction();
  return *this;
}

Rational &Rational::operator/=(const Rational &second) {
  int32_t denominator1 = denominator_ * second.numerator_;
  int32_t numerator1 = numerator_ * second.denominator_;
  if (denominator1 == 0 || second.denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = denominator1;
  numerator_ = numerator1;
  Reduction();
  return *this;
}

Rational Rational::operator+(const Rational &second) const {
  int32_t scm = denominator_ * second.denominator_ / Gcd(denominator_, second.denominator_);
  int32_t denominator1 = scm;
  int32_t numerator1 = numerator_ * (scm / denominator_) + second.numerator_ * (scm / second.denominator_);
  return Rational(numerator1, denominator1);
}

Rational Rational::operator-(const Rational &second) const {
  int32_t scm = denominator_ * second.denominator_ / Gcd(denominator_, second.denominator_);
  int32_t denominator1 = scm;
  int32_t numerator1 = numerator_ * (scm / denominator_) - second.numerator_ * (scm / second.denominator_);
  return Rational(numerator1, denominator1);
}

Rational Rational::operator*(const Rational &second) const {
  int32_t denominator1 = denominator_ * second.denominator_;
  int32_t numerator1 = numerator_ * second.numerator_;
  return Rational(numerator1, denominator1);
}

Rational Rational::operator/(const Rational &second) const {
  int32_t denominator1 = denominator_ * second.numerator_;
  int32_t numerator1 = numerator_ * second.denominator_;
  if (denominator1 == 0 || second.denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  return Rational(numerator1, denominator1);
}

Rational Rational::operator+() const {
  return Rational(numerator_, denominator_);
}

Rational Rational::operator-() const {
  return Rational(-numerator_, denominator_);
}

Rational &Rational::operator++() {
  numerator_ += denominator_;
  return *this;
}

Rational Rational::operator++(int) {
  auto old_value = *this;
  numerator_ += denominator_;
  return old_value;
}

Rational &Rational::operator--() {
  numerator_ -= denominator_;
  return *this;
}

Rational Rational::operator--(int) {
  auto old_value = *this;
  numerator_ -= denominator_;
  return old_value;
}

bool Rational::operator<(const Rational &second) const {
  return numerator_ * second.denominator_ < denominator_ * second.numerator_;
}

bool Rational::operator>(const Rational &second) const {
  return numerator_ * second.denominator_ > denominator_ * second.numerator_;
}

bool Rational::operator<=(const Rational &second) const {
  return numerator_ * second.denominator_ <= denominator_ * second.numerator_;
}

bool Rational::operator>=(const Rational &second) const {
  return numerator_ * second.denominator_ >= denominator_ * second.numerator_;
}

bool Rational::operator==(const Rational &second) const {
  int sign = 1;
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (numerator_ * denominator_ < 0) {
    sign = -1;
  }
  int32_t gcd = Gcd(abs(numerator_), abs(denominator_));
  int32_t numerator1 = sign * abs(numerator_) / gcd;
  int32_t denominator1 = abs(denominator_) / gcd;
  if (second.numerator_ * second.denominator_ <= 0) {
    sign = -1;
  } else {
    sign = 1;
  }
  gcd = Gcd(abs(second.numerator_), abs(second.denominator_));
  int32_t numerator2 = sign * abs(second.numerator_) / gcd;
  int32_t denominator2 = abs(second.denominator_) / gcd;
  return numerator1 == numerator2 && denominator1 == denominator2;
}

bool Rational::operator!=(const Rational &second) const {
  return !(second == *this);
}

std::ostream &operator<<(std::ostream &os, const Rational &second) {
  int sign = 1;
  if (second.numerator_ * second.denominator_ <= 0) {
    sign = -1;
  }
  int32_t gcd = Gcd(abs(second.numerator_), abs(second.denominator_));
  int32_t numerator1 = sign * abs(second.numerator_) / gcd;
  int32_t denominator1 = abs(second.denominator_) / gcd;
  if (denominator1 == 1) {
    os << numerator1;
  } else {
    os << numerator1 << '/' << denominator1;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Rational &second) {
  char symbol;
  is >> second.numerator_;
  if (is.peek() == '/') {
    is >> symbol >> second.denominator_;
  } else {
    second.denominator_ = 1;
  }
  second.Reduction();
  return is;
}

bool operator<(const int32_t &first, const Rational &second) {
  Rational obj = first;
  return obj < second;
}

bool operator>(const int &first, const Rational &second) {
  Rational obj = first;
  return obj > second;
}

bool operator>=(const int &first, const Rational &second) {
  Rational obj = first;
  return obj >= second;
}

bool operator<=(const int &first, const Rational &second) {
  Rational obj = first;
  return obj <= second;
}

bool operator==(const int &first, const Rational &second) {
  Rational obj = first;
  return obj == second;
}

bool operator!=(const int &first, const Rational &second) {
  Rational obj = first;
  return obj != second;
}

bool operator>(const Rational &first, const int &second) {
  Rational obj = second;
  return first > obj;
}

bool operator<(const Rational &first, const int &second) {
  Rational obj = second;
  return first < obj;
}

bool operator>=(const Rational &first, const int &second) {
  Rational obj = second;
  return first >= obj;
}

bool operator<=(const Rational &first, const int &second) {
  Rational obj = second;
  return first <= obj;
}

bool operator==(const Rational &first, const int &second) {
  Rational obj = second;
  return first == obj;
}

bool operator!=(const Rational &first, const int &second) {
  Rational obj = second;
  return first != obj;
}