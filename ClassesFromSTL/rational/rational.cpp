#include <iostream>
#include "rational.h"

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int64_t val) : numerator_(val), denominator_(1) {  // NOLINT
}

Rational::Rational(const Rational &other) = default;

Rational::Rational(int64_t x, int64_t y) : numerator_(x), denominator_(y) {
  if (y == 0) {
    throw RationalDivisionByZero{};
  }
  Normalize();
}

int64_t Rational::GetDenominator() const {
  return denominator_;
}

int64_t Rational::GetNumerator() const {
  return numerator_;
}

void Rational::SetDenominator(int64_t y) {
  if (y == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = y;
  Normalize();
}

void Rational::SetNumerator(int64_t x) {
  numerator_ = x;
  Normalize();
}

int64_t Gcd(Rational &num) {
  int64_t x = num.GetNumerator();
  int64_t y = num.GetDenominator();
  if (x < 0) {
    x *= -1;
  }
  if (y < 0) {
    y *= -1;
  }
  while (x != 0 && y != 0) {
    if (x > y) {
      x = x % y;
    } else {
      y = y % x;
    }
  }
  return x + y;
}

int64_t Lcm(const Rational &num1, const Rational &num2) {
  int64_t x = num1.GetDenominator();
  int64_t y = num2.GetDenominator();
  Rational temp(x, y);
  return (x * y) / Gcd(temp);
}

void Rational::Normalize() {
  if (denominator_ < 0) {
    denominator_ *= -1;
    numerator_ *= -1;
  }
  int64_t gcd = Gcd(*this);
  numerator_ /= gcd;
  denominator_ /= gcd;
}

Rational &Rational::operator=(const Rational &other) {
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
  Normalize();
  return *this;
}

bool operator<(const Rational &num1, const Rational &num2) {
  int64_t lcm = Lcm(num1, num2);
  int64_t temp1 = lcm / num1.denominator_;
  int64_t temp2 = lcm / num2.denominator_;
  return (num1.numerator_ * temp1 < num2.numerator_ * temp2);
}

bool operator==(const Rational &num1, const Rational &num2) {
  return (!(num1 < num2) && !(num2 < num1));
}

bool operator!=(const Rational &num1, const Rational &num2) {
  return ((num1 < num2) || (num2 < num1));
}

bool operator>(const Rational &num1, const Rational &num2) {
  return (num2 < num1);
}

bool operator<=(const Rational &num1, const Rational &num2) {
  return (!(num2 < num1));
}

bool operator>=(const Rational &num1, const Rational &num2) {
  return (!(num1 < num2));
}

Rational &operator+=(Rational &num1, const Rational &num2) {
  int64_t lcm = Lcm(num1, num2);
  int64_t temp1 = lcm / num1.denominator_;
  int64_t temp2 = lcm / num2.denominator_;
  num1.denominator_ = lcm;
  num1.numerator_ *= temp1;
  num1.numerator_ += num2.numerator_ * temp2;
  num1.Normalize();
  return num1;
}

Rational &operator-=(Rational &num1, const Rational &num2) {
  num1 += (-num2);
  return num1;
}

Rational &operator*=(Rational &num1, const Rational &num2) {
  num1.numerator_ *= num2.numerator_;
  num1.denominator_ *= num2.denominator_;
  num1.Normalize();
  return num1;
}

Rational &operator/=(Rational &num1, const Rational &num2) {
  if (num2.GetDenominator() == 0) {
    throw RationalDivisionByZero{};
  }
  Rational temp(num2.GetDenominator(), num2.GetNumerator());
  num1 *= temp;
  num1.Normalize();
  return num1;
}

Rational operator+(const Rational &num1, const Rational &num2) {
  Rational res_num = num1;
  res_num += num2;
  res_num.Normalize();
  return res_num;
}

Rational operator-(const Rational &num1, const Rational &num2) {
  Rational res_num = num1;
  res_num -= num2;
  res_num.Normalize();
  return res_num;
}

Rational operator*(const Rational &num1, const Rational &num2) {
  Rational res_num = num1;
  res_num *= num2;
  res_num.Normalize();
  return res_num;
}

Rational operator/(const Rational &num1, const Rational &num2) {
  if (num2.GetNumerator() == 0) {
    throw RationalDivisionByZero{};
  }
  Rational res_num = num1;
  res_num /= num2;
  res_num.Normalize();
  return res_num;
}

Rational operator+(const Rational &num1) {
  Rational temp = num1;
  return temp;
}

Rational operator-(const Rational &num1) {
  Rational temp = num1;
  temp.numerator_ = -temp.numerator_;
  return temp;
}

Rational &operator++(Rational &num1) {
  num1 += 1;
  num1.Normalize();
  return num1;
}

Rational &operator--(Rational &num1) {
  Rational temp = 1;
  num1 -= temp;
  num1.Normalize();
  return num1;
}

Rational operator++(Rational &num1, int) {
  Rational old = num1;
  num1 += 1;
  num1.Normalize();
  return old;
}

Rational operator--(Rational &num1, int) {
  Rational old = num1;
  num1 -= 1;
  num1.Normalize();
  return old;
}

std::ostream &operator<<(std::ostream &os, const Rational &value) {
  Rational temp = value;
  if (value.denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  temp.Normalize();
  if (temp.denominator_ != 1) {
    os << temp.numerator_ << '/' << temp.denominator_;
  } else {
    os << temp.numerator_;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Rational &value) {
  char a = '/';
  int64_t temp_n = 0;
  int64_t temp_d = 1;
  Rational temp = 0;
  is >> temp_n;
  if (a == is.peek()) {
    is >> a >> temp_d;
    if (temp_d == 0) {
      throw RationalDivisionByZero{};
    }
    temp.SetNumerator(temp_n);
    temp.SetDenominator(temp_d);
  } else {
    temp.SetNumerator(temp_n);
    temp.denominator_ = 1;
  }
  value = temp;
  return is;
}