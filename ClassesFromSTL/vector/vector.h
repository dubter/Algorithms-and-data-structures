#pragma once
#include <stdexcept>
#include <iostream>

#define VECTOR_MEMORY_IMPLEMENTED

template <typename T>
class Vector {
 private:
  void ToEmpty() {
    buffer_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

 public:
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using Iterator = T *;
  using iterator_ = T *;  // NOLINT
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : size_(0), capacity_(0), buffer_(nullptr) {
  }
  explicit Vector(const SizeType &size) : size_(size), capacity_(size) {
    buffer_ = static_cast<Pointer>(operator new(size_ * sizeof(T)));
    size_t i = 0;
    try {
      for (; i < size_; ++i) {
        new (buffer_ + i) T();
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (buffer_ + j)->~T();
      }
      operator delete(buffer_);
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  Vector(int size, const ValueType &value) {
    if (size > 0) {
      buffer_ = static_cast<Pointer>(operator new(size * sizeof(T)));
      size_ = 0;
      try {
        for (; size_ < static_cast<size_t>(size); ++size_) {
          new (buffer_ + size_) T(value);
        }
      } catch (...) {
        for (size_t i = 0; i < size_; ++i) {
          (buffer_ + i)->~T();
        }
        operator delete(buffer_);
        ToEmpty();
        throw;
      }
      capacity_ = static_cast<SizeType>(size);
    } else {
      ToEmpty();
    }
  }

  Vector(const std::initializer_list<ValueType> &init) {
    buffer_ = static_cast<Pointer>(operator new((init.end() - init.begin()) * sizeof(T)));
    capacity_ = static_cast<SizeType>(init.end() - init.begin());
    size_ = static_cast<SizeType>(init.end() - init.begin());
    size_t j = 0;
    try {
      for (auto i = init.begin(); i != init.end(); ++i) {
        new (buffer_ + j++) T(*i);
      }
    } catch (...) {
      for (size_t i = 0; i < j; ++i) {
        (buffer_ + i)->~T();
      }
      operator delete(buffer_);
      ToEmpty();
      throw;
    }
  }
  Vector(const Vector &other) {
    if (other.size_ > 0) {
      capacity_ = other.size_;
      size_ = other.size_;
      buffer_ = static_cast<Pointer>(operator new(size_ * sizeof(T)));
      size_t j = 0;
      try {
        for (auto i = other.begin(); i != other.end(); ++i) {
          new (buffer_ + j++) T(*i);
        }
      } catch (...) {
        for (size_t i = 0; i < j; ++i) {
          (buffer_ + i)->~T();
        }
        operator delete(buffer_);
        ToEmpty();
        throw;
      }
    } else {
      ToEmpty();
    }
  }
  Vector(Vector &&other) noexcept {
    buffer_ = other.buffer_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.ToEmpty();
  }

  template <typename InputIt>
  Vector(const InputIt &first, const InputIt &last) {
    size_ = static_cast<SizeType>(last - first);
    capacity_ = static_cast<SizeType>(last - first);
    if (size_ > 0) {
      buffer_ = static_cast<Pointer>(operator new(capacity_ * sizeof(T)));
      size_t j = 0;
      try {
        for (auto i = first; i != last; ++i) {
          new (buffer_ + j++) T(*i);
        }
      } catch (...) {
        for (size_t i = 0; i < j; ++i) {
          (buffer_ + i)->~T();
        }
        operator delete(buffer_);
        ToEmpty();
        throw;
      }
    } else {
      buffer_ = nullptr;
    }
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      Vector<T>(other).Swap(*this);
    }
    return *this;
  }
  Vector &operator=(Vector &&other) noexcept {
    Vector<ValueType>(std::move(other)).Swap(*this);
    return *this;
  }
  Vector &operator=(const std::initializer_list<ValueType> &init) {
    Clear();
    operator delete(buffer_);
    if (static_cast<SizeType>(init.end() - init.begin()) > 0) {
      buffer_ = static_cast<Pointer>(operator new((init.end() - init.begin()) * sizeof(T)));
      capacity_ = static_cast<SizeType>(init.end() - init.begin());
      size_ = static_cast<SizeType>(init.end() - init.begin());
      size_t j = 0;
      for (auto i = init.begin(); i != init.end(); ++i) {
        new (buffer_ + j++) T(std::move(*i));
      }
    } else {
      ToEmpty();
    }
    return *this;
  }

  SizeType Capacity() const {
    return capacity_;
  }
  SizeType Size() const {
    return size_;
  }
  bool Empty() const {
    return (size_ == 0);
  }

  Reference operator[](SizeType pos) {
    return buffer_[pos];
  }
  ConstReference operator[](SizeType pos) const {
    return buffer_[pos];
  }

  Reference At(SizeType pos) {
    if (pos > size_ - 1) {
      throw std::out_of_range("std::out_of_range");
    }
    return buffer_[pos];
  }
  ConstReference At(SizeType pos) const {
    if (pos > size_ - 1) {
      throw std::out_of_range("std::out_of_range");
    }
    return buffer_[pos];
  }

  Reference Back() {
    return buffer_[size_ - 1];
  };
  ConstReference Back() const {
    return buffer_[size_ - 1];
  };

  Reference Front() {
    return buffer_[0];
  }
  ConstReference Front() const {
    return buffer_[0];
  }

  Pointer Data() {
    return buffer_;
  }
  ConstPointer Data() const {
    return buffer_;
  }

  void Swap(Vector<ValueType> &other) {
    std::swap(buffer_, other.buffer_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(SizeType new_size) {
    if (new_size > capacity_) {
      auto temp = static_cast<Pointer>(operator new(new_size * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        new (temp + i) T(std::move_if_noexcept(buffer_[i]));
      }
      size_t i = size_;
      try {
        for (; i < new_size; ++i) {
          new (temp + i) T();
        }
      } catch (...) {
        for (size_t j = 0; j < size_; ++j) {
          new (buffer_ + j) T(std::move_if_noexcept(temp[j]));
        }

        for (size_t k = size_; k < i; ++k) {
          (temp + k)->~T();
        }
        operator delete(temp);
        throw;
      }
      Clear();
      operator delete(buffer_);
      buffer_ = temp;
      capacity_ = new_size;
      size_ = new_size;
      return;
    }
    if (new_size < size_) {
      for (size_t i = size_ - 1; i >= new_size; --i) {
        (buffer_ + i)->~T();
      }
    } else {
      for (size_t i = size_; i < new_size; ++i) {
        new (buffer_ + i) T();
      }
    }
    size_ = new_size;
  }
  void Resize(SizeType new_size, const ValueType &value) {
    if (new_size > capacity_) {
      auto temp = static_cast<Pointer>(operator new(new_size * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        new (temp + i) T(buffer_[i]);
      }
      size_t i = size_;
      try {
        for (; i < new_size; ++i) {
          new (temp + i) T(value);
        }
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          (temp + j)->~T();
        }
        operator delete(temp);
      }

      for (size_t j = 0; j < size_; ++j) {
        (buffer_ + j)->~T();
      }
      operator delete(buffer_);

      buffer_ = temp;
      size_ = new_size;
      capacity_ = new_size;
      return;
    }
    if (new_size < size_) {
      for (size_t i = size_ - 1; i >= new_size; --i) {
        (buffer_ + i)->~T();
      }
    } else {
      for (size_t i = size_; i < new_size; ++i) {
        new (buffer_ + i) T(value);
      }
    }
    size_ = new_size;
  }

  void Reserve(SizeType new_cap) {
    if (new_cap > capacity_) {
      auto temp = static_cast<Pointer>(operator new(new_cap * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        new (temp + i) T(std::move(buffer_[i]));
      }
      size_t old = size_;
      Clear();
      operator delete(buffer_);
      size_ = old;
      buffer_ = temp;
      capacity_ = new_cap;
    }
  }

  void ShrinkToFit() {
    if (size_ > 0) {
      auto temp = static_cast<Pointer>(operator new(size_ * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        new (temp + i) T(std::move(buffer_[i]));
      }
      size_t old = size_;
      Clear();
      operator delete(buffer_);
      size_ = old;
      buffer_ = temp;
      capacity_ = size_;
    } else {
      Clear();
      operator delete(buffer_);
      ToEmpty();
    }
  }

  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (buffer_ + i)->~T();
    }
    size_ = 0;
  }

  void PushBack(const ValueType &value) {
    if (size_ + 1 > capacity_) {
      SizeType new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
      auto temp = static_cast<Pointer>(operator new(new_cap * sizeof(T)));

      for (size_t i = 0; i < size_; ++i) {
        new (temp + i) T(std::move(buffer_[i]));
      }
      try {
        new (temp + size_) T(value);
      } catch (...) {
        for (size_t i = 0; i < size_; ++i) {
          new (buffer_ + i) T(std::move(temp[i]));
        }
        operator delete(temp);
        throw;
      }
      size_t old = size_;
      Clear();
      operator delete(buffer_);
      size_ = ++old;
      buffer_ = temp;
      capacity_ = new_cap;
    } else {
      new (buffer_ + size_++) T(value);
    }
  }
  void PushBack(ValueType &&value) {
    if (size_ + 1 > capacity_) {
      SizeType new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
      Reserve(new_cap);
    }
    new (buffer_ + size_++) T(std::move(value));
  }

  template <typename... Args>
  void EmplaceBack(Args &&... args) {
    if (size_ + 1 > capacity_) {
      SizeType new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
      Reserve(new_cap);
    }
    new (buffer_ + size_++) T(std::forward<Args>(args)...);
  }

  void PopBack() {
    (buffer_ + size_ - 1)->~T();
    --size_;
  }
  Iterator begin() {  // NOLINT
    return iterator_(buffer_);
  }
  Iterator end() {  // NOLINT
    return iterator_(buffer_ + size_);
  }

  ConstIterator begin() const {  // NOLINT
    return ConstIterator(buffer_);
  }
  ConstIterator end() const {  // NOLINT
    return ConstIterator(buffer_ + size_);
  }

  ConstIterator cbegin() const {  // NOLINT
    return begin();
  }
  ConstIterator cend() const {  // NOLINT
    return end();
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::make_reverse_iterator(buffer_ + size_);
  }
  ReverseIterator rend() {  // NOLINT
    return std::make_reverse_iterator(buffer_);
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_ + size_));
  }
  ConstReverseIterator rend() const {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_));
  }

  ConstReverseIterator crbegin() {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_ + size_));
  }
  ConstReverseIterator crend() {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_));
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_ + size_));
  }
  ConstReverseIterator crend() const {  // NOLINT
    return std::make_reverse_iterator(Iterator(buffer_));
  }

  ~Vector() {
    for (size_t i = 0; i < size_; ++i) {
      (buffer_ + i)->~T();
    }
    operator delete(buffer_);
  }

 private:
  SizeType size_;
  SizeType capacity_;
  ValueType *buffer_;
};

template <typename T>
bool operator<(const Vector<T> &first, const Vector<T> &second) {
  size_t i = 0;
  while (i < first.Size() && i < second.Size()) {
    if (first[i] != second[i]) {
      return static_cast<size_t>(first[i]) < static_cast<size_t>(second[i]);
    }
    ++i;
  }
  return (first.Size() < second.Size());
}
template <typename T>
bool operator==(const Vector<T> &first, const Vector<T> &second) {
  return !(first < second) && !(second < first);
}
template <typename T>
bool operator!=(const Vector<T> &first, const Vector<T> &second) {
  return ((first < second) || (second < first));
}
template <typename T>
bool operator>(const Vector<T> &first, const Vector<T> &second) {
  return (second < first);
}
template <typename T>
bool operator<=(const Vector<T> &first, const Vector<T> &second) {
  return (!(second < first));
}
template <typename T>
bool operator>=(const Vector<T> &first, const Vector<T> &second) {
  return (!(first < second));
}
