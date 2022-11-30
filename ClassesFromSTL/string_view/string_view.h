#pragma once
#include <utility>
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 private:
  size_t size_;
  const char* string_;

  size_t Strlen(const char* str) {  // NOLINT
    size_t size = 0;
    while (str[size] != '\0' && str[size] != '\n') {
      ++size;
    }
    return size;
  };

 public:
  StringView() {
    size_ = 0;
    string_ = nullptr;
  }

  StringView(const char* other) {  // NOLINT
    size_ = Strlen(other);
    string_ = other;
  }

  StringView(const char* other, size_t len) {
    size_ = len;
    string_ = other;
  }

  StringView(const StringView& other) = default;

  ~StringView() = default;

  StringView& operator=(const StringView& other) {
    if (this != &other) {
      string_ = other.string_;
      size_ = other.size_;
    }
    return *this;
  }

  const char& operator[](size_t index) const {
    return string_[index];
  }
  const char& operator[](size_t index) {
    return string_[index];
  }

  const char& At(size_t index) const {
    if (index < size_) {
      return string_[index];
    }
    throw StringViewOutOfRange{};
  }
  const char& At(size_t index) {
    if (index < size_) {
      return string_[index];
    }
    throw StringViewOutOfRange{};
  }

  const char& Front() const {
    return string_[0];
  }
  const char& Front() {
    return string_[0];
  }

  const char& Back() const {
    return string_[size_ - 1];
  }
  const char& Back() {
    return string_[size_ - 1];
  }

  size_t Size() const {
    return size_;
  }
  size_t Length() const {
    return size_;
  }

  bool Empty() const {
    return (size_ == 0);
  }

  const char* Data() const {
    return string_;
  }

  void Swap(StringView& other) {
    auto swapper = size_;
    size_ = other.size_;
    other.size_ = swapper;

    auto pointer_swapper = string_;
    string_ = other.string_;
    other.string_ = pointer_swapper;
  }

  void RemovePrefix(size_t prefix_size) {
    size_ -= prefix_size;
    string_ += prefix_size;
  }

  void RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
  }

  StringView Substr(size_t pos, size_t count = -1) {
    if (pos >= size_) {
      throw StringViewOutOfRange{};
    }
    StringView result = StringView{string_ + pos, std::min<size_t>(count, Size() - pos)};
    return result;
  }
};
