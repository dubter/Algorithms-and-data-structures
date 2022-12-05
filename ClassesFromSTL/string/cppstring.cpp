#include "cppstring.h"
#include <cstring>
#include <iostream>

String::String() {
  string_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(const size_t &size, const char &symbol) {
  if (size != 0) {
    string_ = new char[size];
    size_ = size;
    capacity_ = size_;
    for (size_t i = 0; i < size_; i++) {
      string_[i] = symbol;
    }
  } else {
    string_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

String::String(const String &other) {
  if (other.capacity_ != 0) {
    string_ = new char[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    strncpy(string_, other.string_, size_);
  } else {
    string_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

String::String(const char *string) {
  size_ = strlen(string);
  if (size_ == 0) {
    string_ = nullptr;
    capacity_ = 0;
  } else {
    string_ = new char[size_];
    strncpy(string_, string, size_);
    capacity_ = size_;
  }
}

String::String(const char *string, const size_t &size) {
  size_ = size;
  if (size == 0) {
    string_ = nullptr;
  } else {
    auto *new_string = new char[size_];
    string_ = new_string;
    strncpy(string_, string, size);
  }
  capacity_ = size_;
}

String::~String() {
  if (capacity_ != 0) {
    delete[] string_;
  }
}

char &String::operator[](const size_t &index) {
  return string_[index];
}

const char &String::operator[](const size_t &index) const {
  return string_[index];
}

char &String::At(const size_t &index) {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return string_[index];
}

const char &String::At(const size_t &index) const {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return string_[index];
}

char &String::Front() {
  return string_[0];
}

char &String::Back() {
  return string_[size_ - 1];
}

const char &String::Front() const {
  return string_[0];
}

const char &String::Back() const {
  return string_[size_ - 1];
}

const char *String::CStr() const {
  return string_;
}

const char *String::Data() const {
  return string_;
}

char *String::CStr() {
  return string_;
}

char *String::Data() {
  return string_;
}

bool String::Empty() const {
  return size_ == 0;
}

const size_t &String::Size() const {
  return size_;
}

const size_t &String::Length() const {
  return size_;
}

const size_t &String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

String &String::operator=(const String &other) {
  if (this != &other) {
    if (other.capacity_ == 0) {
      if (capacity_ != 0) {
        delete[] string_;
      }
      size_ = other.size_;
      string_ = nullptr;
      capacity_ = size_;
    } else {
      if (other.size_ > capacity_) {
        delete[] string_;
        string_ = new char[other.size_];
        capacity_ = other.size_;
      }
      strncpy(string_, other.string_, other.size_);
      size_ = other.size_;
    }
  }
  return *this;
}

void String::Swap(String &other) {
  String tmp;
  tmp = *this;
  *this = other;
  other = tmp;
}

void String::PopBack() {
  if (!Empty()) {
    --size_;
  }
}

void String::PushBack(const char &symbol) {
  if (capacity_ == 0) {
    string_ = new char[1];
    string_[0] = symbol;
    size_++;
    capacity_++;
  } else {
    if (size_ >= capacity_) {
      auto *buffer = new char[2 * size_];
      strncpy(buffer, string_, size_);
      delete[] string_;
      string_ = buffer;
      capacity_ = 2 * size_;
    }
    string_[size_] = symbol;
    ++size_;
  }
}

String &String::operator+=(const String &string) {
  for (size_t i = 0; i < string.size_; i++) {
    PushBack(string.string_[i]);
  }
  return *this;
}

void String::Resize(const size_t &new_size, const char &symbol) {
  size_t tmp = size_;
  if (capacity_ == 0) {
    string_ = new char[new_size];
    capacity_ = new_size;
  } else {
    if (new_size > capacity_) {
      auto *new_string = new char[new_size];
      strncpy(new_string, string_, size_);
      delete[] string_;
      string_ = new_string;
      capacity_ = new_size;
    }
  }
  size_ = new_size;
  if (new_size > tmp) {
    for (size_t i = 0; i < new_size - tmp; i++) {
      string_[tmp + i] = symbol;
    }
  }
}

void String::Reserve(const size_t &new_capacity) {
  if (capacity_ == 0) {
    string_ = new char[new_capacity];
    capacity_ = new_capacity;
  } else if (new_capacity > capacity_) {
    auto *new_string = new char[new_capacity];
    strncpy(new_string, string_, size_);
    delete[] string_;
    string_ = new_string;
    capacity_ = new_capacity;
  }
}

void String::ShrinkToFit() {
  if (capacity_ != 0) {
    auto *new_string = new char[size_];
    strncpy(new_string, string_, size_);
    delete[] string_;
    string_ = new_string;
    capacity_ = size_;
  }
}

bool String::operator>(const String &second) const {
  for (size_t i = 0; i < std::min(size_, second.size_); i++) {
    if (string_[i] == second.string_[i]) {
      continue;
    }
    return string_[i] > second.string_[i];
  }
  return size_ > second.size_;
}

bool String::operator<(const String &second) const {
  for (size_t i = 0; i < std::min(size_, second.size_); i++) {
    if (string_[i] == second.string_[i]) {
      continue;
    }
    return string_[i] < second.string_[i];
  }
  return size_ < second.size_;
}

bool String::operator>=(const String &second) const {
  for (size_t i = 0; i < std::min(size_, second.size_); i++) {
    if (string_[i] == second.string_[i]) {
      continue;
    }
    return string_[i] > second.string_[i];
  }
  return size_ >= second.size_;
}

bool String::operator<=(const String &second) const {
  for (size_t i = 0; i < std::min(size_, second.size_); i++) {
    if (string_[i] == second.string_[i]) {
      continue;
    }
    return string_[i] < second.string_[i];
  }
  return size_ <= second.size_;
}

bool String::operator==(const String &second) const {
  if (size_ != second.size_) {
    return false;
  }
  for (size_t i = 0; i < size_; i++) {
    if (string_[i] == second.string_[i]) {
      continue;
    }
    return false;
  }
  return true;
}

bool String::operator!=(const String &second) const {
  return !(*this == second);
}

const String operator+(const String &first, const String &second) {
  if (first.size_ + second.size_ == 0) {
    return String("");
  }
  String obj;
  auto *new_string = new char[first.size_ + second.size_];
  if (second.size_ != 0 && first.size_ != 0) {
    strncpy(new_string, first.string_, first.size_);
    for (size_t i = first.size_; i < first.size_ + second.size_; i++) {
      new_string[i] = second.string_[i - first.size_];
    }
  } else if (second.size_ == 0) {
    strncpy(new_string, first.string_, first.size_);
  } else {
    strncpy(new_string, second.string_, second.size_);
  }
  obj.string_ = new_string;
  obj.size_ = first.size_ + second.size_;
  obj.capacity_ = obj.size_;
  return String(obj);
}

std::ostream &operator<<(std::ostream &os, const String &second) {
  for (size_t i = 0; i < second.size_; i++) {
    os << second.string_[i];
  }
  return os;
}
