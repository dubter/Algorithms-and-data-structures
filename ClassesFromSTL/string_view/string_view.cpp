#include "string_view.h"
#include <cstring>

StringView::StringView() {
  string_ = nullptr;
  size_ = 0;
}

StringView::StringView(const char* string) {
  size_ = strlen(string);
  string_ = string;
}

StringView::StringView(const char* string, size_t size) {
  size_ = size;
  string_ = string;
}

char StringView::operator[](const size_t& index) const {
  return string_[index];
}

char StringView::At(const size_t& index) const {
  if (index >= size_) {
    throw StringViewOutOfRange{};
  }
  return string_[index];
}

char StringView::Front() const {
  return string_[0];
}

char StringView::Back() const {
  return string_[size_ - 1];
}

const char* StringView::Data() const {
  return string_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

const size_t& StringView::Size() const {
  return size_;
}

const size_t& StringView::Length() const {
  return size_;
}

void StringView::Swap(StringView& other) {
  auto tmp = other.string_;
  other.string_ = string_;
  string_ = tmp;
  size_t buffer = size_;
  size_ = other.size_;
  other.size_ = buffer;
}

void StringView::RemovePrefix(size_t prefix_size) {
  string_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  StringView obj(string_);
  if (pos >= size_) {
    throw StringViewOutOfRange{};
  }
  count = std::min(count, obj.Size() - pos);
  obj.RemovePrefix(pos);
  obj.RemoveSuffix(obj.size_ - count);
  return obj;
}