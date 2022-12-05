#pragma once
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 private:
  const char *string_;
  size_t size_;

 public:
  StringView();
  StringView(const char *string);  // NOLINT
  StringView(const char *string, size_t size);
  char operator[](const size_t &index) const;
  char At(const size_t &index) const;
  char Front() const;
  char Back() const;
  const char *Data() const;
  bool Empty() const;
  const size_t &Size() const;
  const size_t &Length() const;
  void Swap(StringView &other);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1);
};