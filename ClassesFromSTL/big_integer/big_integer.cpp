#include <iostream>
#include <cstring>

#include "big_integer.h"
#include "array.h"

void Array::Resize() {
  capacity_ *= 2;
  auto *new_data = new int64_t[capacity_];
  for (int i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
}

Array::Array() {
  size_ = 0;
  capacity_ = 1;
  data_ = new int64_t[1];
}

int64_t Array::GetSize() const {
  return size_;
}

void Array::PushBack(int64_t number) {
  if (size_ == capacity_) {
    Resize();
  }
  data_[size_++] = number;
}
void Array::Reserve(const int64_t &new_capacity, const int64_t &val) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
    auto *new_data = new int64_t[capacity_];
    for (int64_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    for (int64_t i = size_; i < new_capacity; ++i) {
      new_data[i] = val;
    }
    std::swap(data_, new_data);
    delete[] new_data;
  }
}

const int64_t &Array::Back() const {
  return data_[size_ - 1];
}
const int64_t &Array::Front() const {
  return data_[0];
}

int64_t &Array::operator[](int64_t pos) {
  return data_[pos];
}
const int64_t &Array::operator[](int64_t pos) const {
  return data_[pos];
}

int64_t *Array::Data() const {
  return data_;
}
void Array::Clear() {
  delete[] data_;
  capacity_ = 1;
  size_ = 0;
  data_ = new int64_t[1];
}
Array &Array::operator=(const Array &other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new int64_t[capacity_];
    for (int64_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

std::ostream &operator<<(std::ostream &stream, const Array &array) {
  for (int i = 0; i < array.size_; ++i) {
    stream << array.data_[i];
  }
  return stream;
}

Array::~Array() {
  size_ = 0;
  capacity_ = 0;
  delete[] data_;
}

void StraightTranslate(const char *str, const int64_t &len, int64_t &res_num, const int64_t &order) {
  res_num = 0;
  auto *copy = new char[order + 1];
  strncpy(copy, str + len - order, order);
  copy[order] = '\0';
  res_num = atoi(copy);
  delete[] copy;
}

void UpdateSize(BigInteger &num) {
  bool flag = false;
  int64_t new_size = 0;
  for (int64_t i = num.GetSize() - 1; i >= 0; --i) {
    if (flag) {
      ++new_size;
    }
    if (!flag && num[i] != 0) {
      flag = true;
      ++new_size;
    }
  }
  if (new_size == 0) {
    num.SetSize(1);
  } else {
    num.SetSize(new_size);
  }
}

BigInteger::BigInteger(int64_t val) {
  val < 0 ? sign_ = Sign::NEGATIVE : sign_ = Sign::POSITIVE;
  int64_t value = val;
  if (val < 0) {
    value = -val;
  }
  if (!value) {
    data_.PushBack(value);
    size_ = data_.GetSize();
  } else {
    while (value != 0) {
      int64_t temp_rem = value % static_cast<int64_t>(Base::BASE_VALUE);
      value /= static_cast<int64_t>(Base::BASE_VALUE);
      data_.PushBack(temp_rem);
    }
    size_ = data_.GetSize();
  }
}
BigInteger::BigInteger(int32_t val) {
  val < 0 ? sign_ = Sign::NEGATIVE : sign_ = Sign::POSITIVE;
  int64_t value = val;
  if (val < 0) {
    value = -val;
  }
  if (!value) {
    data_.PushBack(value);
    size_ = data_.GetSize();
  } else {
    while (value != 0) {
      int64_t temp_rem = value % static_cast<int64_t>(Base::BASE_VALUE);
      value /= static_cast<int64_t>(Base::BASE_VALUE);
      data_.PushBack(temp_rem);
    }
    size_ = data_.GetSize();
  }
}
BigInteger::BigInteger(const char *str) {
  auto len = static_cast<int64_t>(strlen(str));

  if (str[0] == '-') {
    sign_ = Sign::NEGATIVE;
    str = str + 1;
    --len;
  } else if (str[0] == '+') {
    sign_ = Sign::POSITIVE;
    str = str + 1;
    --len;
  } else {
    sign_ = Sign::POSITIVE;
  }

  while (len >= static_cast<int64_t>(Base::BASE_LEN)) {
    int64_t temp = 0;
    StraightTranslate(str, len, temp, static_cast<int64_t>(Base::BASE_LEN));
    data_.PushBack(temp);
    len -= static_cast<int64_t>(Base::BASE_LEN);
  }
  if (len != 0) {
    int64_t temp = 0;
    StraightTranslate(str, len, temp, len);
    data_.PushBack(temp);
  }
  size_ = data_.GetSize();
}
BigInteger::BigInteger(const BigInteger &other) {
  data_.Clear();
  data_ = other.data_;
  sign_ = other.sign_;
  size_ = other.GetSize();
}

int64_t BigInteger::GetSize() const {
  return size_;
}

void BigInteger::SetSize(int64_t val) {
  size_ = val;
}
void BigInteger::SetSign(BigInteger::Sign val) {
  if (val == Sign::POSITIVE) {
    sign_ = Sign::POSITIVE;
  } else {
    sign_ = Sign::NEGATIVE;
  }
}

int64_t &BigInteger::operator[](int64_t pos) {
  return data_[pos];
}
const int64_t &BigInteger::operator[](int64_t pos) const {
  return data_[pos];
}

bool BigInteger::IsNegative() const {
  return sign_ == Sign::NEGATIVE;
}

BigInteger &BigInteger::operator=(const BigInteger &other) {
  if (this != &other) {
    Array new_data;
    for (int64_t i = 0; i < other.GetSize(); ++i) {
      new_data.PushBack(other[i]);
    }
    sign_ = other.sign_;
    size_ = other.GetSize();
    data_.Clear();
    data_ = new_data;
  }
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger temp = *this;
  if (temp.IsNegative()) {
    temp.SetSign(Sign::POSITIVE);
  } else {
    temp.SetSign(Sign::NEGATIVE);
  }
  return temp;
}
BigInteger BigInteger::operator+() const {
  BigInteger temp = *this;
  return temp;
}

BigInteger &BigInteger::operator++() {
  *this += 1;
  return *this;
}
BigInteger &BigInteger::operator--() {
  *this -= 1;
  return *this;
}
BigInteger BigInteger::operator++(int) {
  BigInteger res = *this;
  *this += 1;
  return res;
}
BigInteger BigInteger::operator--(int) {
  BigInteger res = *this;
  *this -= 1;
  return res;
}

bool operator<(const BigInteger &num1, const BigInteger &num2) {
  if (num1.IsNegative() && !num2.IsNegative()) {
    return true;
  }
  if (!num1.IsNegative() && num2.IsNegative()) {
    return false;
  }

  if (!num1.IsNegative() && !num2.IsNegative()) {
    if (num1.GetSize() < num2.GetSize()) {
      return true;
    }
    if (num1.GetSize() > num2.GetSize()) {
      return false;
    }

    for (int64_t i = num1.GetSize() - 1; i >= 0; --i) {
      if (num1[i] < num2[i]) {
        return true;
      }
      if (num1[i] > num2[i]) {
        return false;
      }
    }
  }

  if (num1.IsNegative() && num2.IsNegative()) {
    if (num1.GetSize() < num2.GetSize()) {
      return false;
    }
    if (num1.GetSize() > num2.GetSize()) {
      return true;
    }

    for (int64_t i = num1.GetSize() - 1; i >= 0; --i) {
      if (num1[i] < num2[i]) {
        return false;
      }
      if (num1[i] > num2[i]) {
        return true;
      }
    }
  }
  return false;
}
bool operator==(const BigInteger &num1, const BigInteger &num2) {
  return (!(num1 < num2) && !(num2 < num1));
}
bool operator!=(const BigInteger &num1, const BigInteger &num2) {
  return ((num1 < num2) || (num2 < num1));
}
bool operator>(const BigInteger &num1, const BigInteger &num2) {
  return (num2 < num1);
}
bool operator<=(const BigInteger &num1, const BigInteger &num2) {
  return (!(num2 < num1));
}
bool operator>=(const BigInteger &num1, const BigInteger &num2) {
  return (!(num1 < num2));
}

BigInteger &operator+=(BigInteger &num1, const BigInteger &num2) {
  int64_t in_mind = 0;
  auto base = static_cast<int64_t>(BigInteger::Base::BASE_VALUE);
  if ((!num1.IsNegative() && !num2.IsNegative()) || (num1.IsNegative() && num2.IsNegative())) {
    if (num1.IsNegative() && num2.IsNegative()) {
      num1.SetSign(BigInteger::Sign::NEGATIVE);
    }

    int64_t min_size = std::min(num1.GetSize(), num2.GetSize());
    for (int64_t i = 0; i < min_size; ++i) {
      num1[i] += num2[i];
      num1[i] += in_mind;
      if (num1[i] >= base) {
        in_mind = num1[i] / base;
        num1[i] %= base;
      } else {
        in_mind = 0;
      }
    }

    int64_t i = min_size;

    if (num1.GetSize() > num2.GetSize()) {
      while (in_mind) {
        num1[i] += in_mind;
        if (num1[i] >= base) {
          in_mind = num1[i] / base;
          num1[i] %= base;
        } else {
          in_mind = 0;
        }
        ++i;
      }
    } else if (num1.GetSize() < num2.GetSize()) {
      for (i = min_size; i < num2.GetSize(); ++i) {
        num1.data_.PushBack(num2[i]);
        ++num1.size_;
        num1[i] += in_mind;
        if (num1[i] >= base) {
          in_mind = num1[i] / base;
          num1[i] %= base;
        } else {
          in_mind = 0;
        }
      }
      if (in_mind != 0) {
        num1[i] += in_mind;
      }
      if (num1[i] > base) {
        num1.data_.PushBack(num1[i] / base);
        num1[i] %= base;
      }
    } else {
      if (in_mind != 0) {
        num1.data_.PushBack(in_mind);
        ++num1.size_;
      }
    }
  } else {
    num1 -= -num2;
  }
  UpdateSize(num1);
  if (num1.IsNegative() && -num1 == 0) {
    num1.SetSign(BigInteger::Sign::POSITIVE);
  }
  return num1;
}
BigInteger &operator-=(BigInteger &num1, const BigInteger &num2) {
  auto base = static_cast<int64_t>(BigInteger::Base::BASE_VALUE);
  if (!num1.IsNegative() && num2.IsNegative()) {
    num1 += -num2;
    return num1;
  }
  if (num1.IsNegative() && !num2.IsNegative()) {
    num1.SetSign(BigInteger::BigInteger::Sign::POSITIVE);
    num1 += num2;
    num1.SetSign(BigInteger::Sign::NEGATIVE);
    return num1;
  }

  bool mod_comparison = true;
  if (num1.IsNegative() && num2.IsNegative()) {
    mod_comparison = -num1 >= -num2;
  } else if (!num1.IsNegative() && !num2.IsNegative()) {
    mod_comparison = num1 >= num2;
  }

  if (num1 >= num2) {
    num1.SetSign(BigInteger::Sign::POSITIVE);
  } else if (num2 > num1) {
    num1.SetSign(BigInteger::Sign::NEGATIVE);
  }

  if (mod_comparison) {
    bool loan = false;
    int64_t min_size = std::min(num1.GetSize(), num2.GetSize());
    for (int64_t i = 0; i < min_size; ++i) {
      if (loan && num1[i] == 0) {
        num1[i] += (base - 1);
      } else if (loan && num1[i] != 0) {
        num1[i] -= 1;
        loan = false;
      }
      if (num1[i] < num2[i]) {
        loan = true;
        num1[i] += base;
      }
      num1[i] -= num2[i];
    }
    if (min_size < num1.GetSize()) {
      for (int64_t i = min_size; i < num1.GetSize(); ++i) {
        if (loan && num1[i] == 0) {
          num1[i] += (base - 1);
        } else if (loan && num1[i] != 0) {
          num1[i] -= 1;
          loan = false;
        }
      }
    }
  } else {
    bool loan = false;
    int64_t min_size = std::min(num1.GetSize(), num2.GetSize());
    for (int64_t i = 0; i < min_size; ++i) {

      if (loan && num2[i] == 0) {
        num1[i] = base - 1 - num1[i];
      } else if (loan && num2[i] != 0) {
        num1[i] = num2[i] - 1 - num1[i];
        loan = false;
      } else {
        if (num2[i] < num1[i]) {
          loan = true;
          num1[i] = (num2[i] + base - num1[i]);
        } else {
          num1[i] = num2[i] - num1[i];
        }
      }
    }
    if (min_size < num2.GetSize()) {
      for (int64_t i = min_size; i < num2.GetSize(); ++i) {
        if (loan && num2[i] == 0) {
          num1.data_.PushBack(base - 1);
          ++num1.size_;
        } else if (loan && num2[i] != 0) {
          num1.data_.PushBack(num2[i] - 1);
          ++num1.size_;
          loan = false;
        } else {
          num1.data_.PushBack(num2[i]);
          ++num1.size_;
        }
      }
    }
  }
  UpdateSize(num1);
  if (num1.IsNegative() && -num1 == 0) {
    num1.SetSign(BigInteger::Sign::POSITIVE);
  }
  return num1;
}
BigInteger &operator*=(BigInteger &num1, const BigInteger &num2) {
  auto base = static_cast<int64_t>(BigInteger::Base::BASE_VALUE);
  int64_t res_len = (num1.GetSize()) + (num2.GetSize()) + 1;
  if (res_len * static_cast<int64_t>(BigInteger::Base::BASE_LEN) > 30000) {
    throw BigIntegerOverflow{};
  }
  num1.data_.Reserve(res_len + 1, 0);

  if (num1.IsNegative() && num2.IsNegative()) {
    num1.SetSign(BigInteger::BigInteger::Sign::POSITIVE);
  } else if (!num1.IsNegative() && num2.IsNegative()) {
    num1.SetSign(BigInteger::BigInteger::Sign::NEGATIVE);
  }

  for (int64_t i = res_len; i >= 0; --i) {
    int64_t temp = 0;
    for (int64_t j = num1.GetSize() - 1; j >= 0; --j) {
      int64_t k = i - j;
      if (k < num2.GetSize() && k >= 0) {
        temp += num1[j] * num2[k];
        int64_t it = i + 1;
        if (temp >= base) {
          num1[it] += (temp / base);
          temp %= base;
        }
        while (num1[it] >= base) {
          num1[it + 1] += num1[it] / base;
          num1[it] %= base;
          ++it;
        }
      }
    }
    num1[i] = temp;
  }
  num1.size_ = res_len + 1;
  UpdateSize(num1);
  if (num1.IsNegative() && -num1 == 0) {
    num1.SetSign(BigInteger::Sign::POSITIVE);
  }
  return num1;
}

BigInteger operator+(const BigInteger &num1, const BigInteger &num2) {
  BigInteger temp = num1;
  temp += num2;
  return temp;
}
BigInteger operator-(const BigInteger &num1, const BigInteger &num2) {
  BigInteger temp = num1;
  temp -= num2;
  return temp;
}
BigInteger operator*(const BigInteger &num1, const BigInteger &num2) {
  BigInteger res = num1;
  res *= num2;
  return res;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &num) {
  if (num.IsNegative()) {
    os << '-';
  }

  int64_t i = num.GetSize() - 1;
  while (num[i] == 0 && i > 0) {
    --i;
  }

  os << num[i];

  for (int64_t j = i - 1; j >= 0; --j) {
    int64_t val = num[j];
    int64_t len = 0;
    while (val > 0) {
      val /= 10;
      ++len;
    }
    for (int64_t k = 0; k < static_cast<int64_t>(BigInteger::Base::BASE_LEN) - len; ++k) {
      os << 0;
    }
    os << num[j];
  }

  return os;
}
std::istream &operator>>(std::istream &is, BigInteger &num) {
  char temp[10002];
  is >> temp;
  num = temp;
  return is;
}