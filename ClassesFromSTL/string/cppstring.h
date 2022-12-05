#pragma once
#include <stdexcept>
#include <iostream>
#include <sstream>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char *string_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(const size_t &size, const char &symbol);
  String(const char *string);  // NOLINT
  String(const char *string, const size_t &size);
  String(const String &other);
  ~String();
  String &operator=(const String &other);
  char &operator[](const size_t &index);
  const char &operator[](const size_t &index) const;
  char &At(const size_t &index);
  const char &At(const size_t &index) const;
  char &Front();
  char &Back();
  const char &Front() const;
  const char &Back() const;
  const char *CStr() const;
  const char *Data() const;
  char *CStr();
  char *Data();
  bool Empty() const;
  const size_t &Size() const;
  const size_t &Length() const;
  const size_t &Capacity() const;
  void Clear();
  void Swap(String &other);
  void PopBack();
  void PushBack(const char &symbol);
  String &operator+=(const String &string);
  void Resize(const size_t &new_size, const char &symbol);
  void Reserve(const size_t &new_capacity);
  void ShrinkToFit();
  bool operator>(const String &second) const;
  bool operator<(const String &second) const;
  bool operator>=(const String &second) const;
  bool operator<=(const String &second) const;
  bool operator==(const String &second) const;
  bool operator!=(const String &second) const;
  friend std::ostream &operator<<(std::ostream &os, const String &second);
  friend const String operator+(const String &first, const String &second);
};
const String operator+(const String &first, const String &second);
std::ostream &operator<<(std::ostream &os, const String &second);