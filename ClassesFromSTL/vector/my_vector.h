#pragma once
#define VECTOR_MEMORY_IMPLEMENTED
#include <iostream>
#include <exception>
#include <iterator>
#include <memory>
// possible mistakes:
// 1) нельзя delete[] или new[] - только вручную управлять памятью
// 2) возможно перепутал классf Vector и vector[]

template <class T>
class Vector {
 private:
  T *vector_;
  size_t size_;
  size_t capacity_;

 public:
  ~Vector() {
    if (vector_ != nullptr) {
      for (size_t i = 0; i < size_; ++i) {
        (vector_ + i)->~T();
      }
      operator delete(vector_);
    }
  }

  class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    friend class Vector<T>;

   protected:
    T *node_;
    const Vector<T> *vector_;

   public:
    Iterator() : node_(nullptr), vector_(nullptr) {
    }
    Iterator(const Iterator &it) : node_(it.node_), vector_(it.vector_) {
    }
    Iterator(T *node, const Vector<T> *vector) : node_(node), vector_(vector) {
    }
    const T &operator*() const {
      return *node_;
    }
    T &operator*() {
      return *node_;
    }
    T &operator->() const {
      return node_;
    }
    bool operator==(const Iterator &iterator) const {
      return vector_ == iterator.vector_ && node_ == iterator.node_;
    }
    bool operator!=(const Iterator &iterator) const {
      return !(*this == iterator);
    }
    Iterator &operator++() {
      if (node_ != nullptr) {
        ++node_;
      }
      return *this;
    }
    Iterator &operator--() {
      if (node_ != nullptr) {
        --node_;
      }
      return *this;
    }
    size_t operator-(const Iterator &iterator) const {
      return node_ - iterator.node_;
    }
    Iterator operator+(const size_t &num) const {
      return Iterator(node_ + num, vector_);
    }
    Iterator operator-(const size_t &num) const {
      return Iterator(node_ - num, vector_);
    }
  };

  class ConstIterator : public std::iterator<std::random_access_iterator_tag, T> {
    friend class Vector<T>;

   protected:
    T *node_;
    const Vector<T> *const vector_;

   public:
    ConstIterator() : node_(nullptr), vector_(nullptr) {
    }
    ConstIterator(T *node, const Vector<T> *vector) : node_(node), vector_(vector) {
    }
    ConstIterator(const ConstIterator &it) : node_(it.node_), vector_(it.vector_) {
    }
    const T &operator*() const {
      return *node_;
    }
    T &operator->() const {
      return node_;
    }
    T &operator*() {
      return *node_;
    }
    bool operator==(const ConstIterator &iterator) const {
      return vector_ == iterator.vector_ && node_ == iterator.node_;
    }
    bool operator!=(const ConstIterator &iterator) const {
      return !(*this == iterator);
    }
    ConstIterator &operator++() {
      if (node_ != nullptr) {
        ++node_;
      }
      return *this;
    }
    ConstIterator &operator--() {
      if (node_ != nullptr) {
        --node_;
      }
      return *this;
    }
    size_t operator-(const ConstIterator &iterator) const {
      return node_ - iterator.node_;
    }
    ConstIterator operator+(const size_t &num) const {
      return ConstIterator(node_ + num, vector_);
    }
    ConstIterator operator-(const size_t &num) const {
      return ConstIterator(node_ - num, vector_);
    }
  };

  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using Iterator = Iterator;
  using ConstIterator = ConstIterator;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Iterator begin() {  //  NOLINT
    return Iterator(vector_, this);
  }
  Iterator end() {  //  NOLINT
    return Iterator(vector_ + size_, this);
  }
  ConstIterator begin() const {  //  NOLINT
    return ConstIterator(vector_, this);
  }
  ConstIterator end() const {  //  NOLINT
    return ConstIterator(vector_ + size_, this);
  }
  ReverseIterator rbegin() {  //  NOLINT
    return std::make_reverse_iterator(end());
  }
  ReverseIterator rend() {  //  NOLINT
    return std::make_reverse_iterator(begin());
  }
  ConstReverseIterator rbegin() const {  //  NOLINT
    return std::make_reverse_iterator(cend());
  }
  ConstReverseIterator rend() const {  //  NOLINT
    return std::make_reverse_iterator(cbegin());
  }
  ConstIterator cbegin() {  //  NOLINT
    return ConstIterator(vector_, this);
  }
  ConstIterator cend() {  //  NOLINT
    return ConstIterator(vector_ + size_, this);
  }
  ConstIterator cbegin() const {  //  NOLINT
    return ConstIterator(vector_, this);
  }
  ConstIterator cend() const {  //  NOLINT
    return ConstIterator(vector_ + size_, this);
  }
  ConstReverseIterator crbegin() {  //  NOLINT
    return std::make_reverse_iterator(cend());
  }
  ConstReverseIterator crend() {  //  NOLINT
    return std::make_reverse_iterator(cbegin());
  }
  ConstReverseIterator crbegin() const {  //  NOLINT
    return std::make_reverse_iterator(cend());
  }
  ConstReverseIterator crend() const {  //  NOLINT
    return std::make_reverse_iterator(cbegin());
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
      std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first_it, Iterator second_it) {
    if (second_it - first_it != 0) {
      auto new_buffer = static_cast<T *>(operator new(sizeof(T) * (second_it - first_it)));
      int64_t index = 0;
      try {
        for (; index < second_it - first_it; ++index) {
          new (new_buffer + index) T;
          new_buffer[index] = *(first_it + index);
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_buffer + index)->~T();
        }
        operator delete(new_buffer);
        throw;
      }
      vector_ = new_buffer;
      size_ = second_it - first_it;
      capacity_ = size_;
    } else {
      vector_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }

  Vector() : vector_(nullptr), size_(0), capacity_(0) {
  }
  explicit Vector(const size_t &size) {
    if (size != 0) {
      auto new_buffer = static_cast<T *>(operator new(sizeof(T) * size));
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(size); ++index) {
          new (new_buffer + index) T;
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_buffer + index)->~T();
        }
        operator delete(new_buffer);
        throw;
      }
      vector_ = new_buffer;
      size_ = size;
      capacity_ = size_;
    } else {
      vector_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector(const size_t &size, const T &value) {
    if (size != 0) {
      auto new_buffer = static_cast<T *>(operator new(sizeof(T) * size));
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(size); ++index) {
          new (new_buffer + index) T;
          new_buffer[index] = value;
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_buffer + index)->~T();
        }
        operator delete(new_buffer);
        throw;
      }
      vector_ = new_buffer;
      size_ = size;
      capacity_ = size_;
    } else {
      vector_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector(const std::initializer_list<T> &args_list) {
    if (args_list.size() != 0) {
      auto new_buffer = static_cast<T *>(operator new(sizeof(T) * args_list.size()));
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(args_list.size()); ++index) {
          new (new_buffer + index) T;
          new_buffer[index] = *(args_list.begin() + index);
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_buffer + index)->~T();
        }
        operator delete(new_buffer);
        throw;
      }
      vector_ = new_buffer;
      size_ = args_list.size();
      capacity_ = size_;
    } else {
      vector_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  Vector(const Vector<T> &vector) {
    if (vector.capacity_ != 0) {
      auto new_buffer = static_cast<T *>(operator new(sizeof(T) * vector.capacity_));
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(vector.size_); ++index) {
          new (new_buffer + index) T;
          new_buffer[index] = vector.vector_[index];
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_buffer + index)->~T();
        }
        operator delete(new_buffer);
        throw;
      }
      vector_ = new_buffer;
      size_ = vector.size_;
      capacity_ = vector.capacity_;
    } else {
      vector_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }

  Vector(Vector<T> &&vector) noexcept : vector_(vector.vector_), size_(vector.size_), capacity_(vector.capacity_) {
    vector.vector_ = nullptr;
    vector.size_ = 0;
    vector.capacity_ = 0;
  }

  void Swap(Vector<T> &vector) {
    std::swap(size_, vector.size_);
    std::swap(capacity_, vector.capacity_);
    std::swap(vector_, vector.vector_);
  }

  Vector &operator=(const Vector<T> &vector) {
    if (&vector != this) {
      Vector<T>(vector).Swap(*this);
    }
    return *this;
  }

  Vector &operator=(Vector<T> &&vector) noexcept {
    if (&vector != this) {
      Vector<T>(std::move(vector)).Swap(*this);
    }
    return *this;
  }

  const T &operator[](const size_t &index) const {
    return vector_[index];
  }
  T &operator[](const size_t &index) {
    return vector_[index];
  }
  bool operator<(const Vector<T> &vector) const {
    int result = true;
    bool equal = true;
    for (size_t i = 0; i < std::min(size_, vector.size_); ++i) {
      if (vector_[i] != vector.vector_[i]) {
        equal = false;
      }
      if (vector_[i] < vector.vector_[i]) {
        result = true;
        break;
      }
      if (vector_[i] > vector.vector_[i]) {
        result = false;
        break;
      }
    }
    if (equal) {
      return size_ < vector.size_;
    }
    return result;
  }

  bool operator>(const Vector<T> &vector) const {
    int result = true;
    bool equal = true;
    for (size_t i = 0; i < std::min(size_, vector.size_); ++i) {
      if (vector_[i] != vector.vector_[i]) {
        equal = false;
      }
      if (vector_[i] > vector.vector_[i]) {
        result = true;
        break;
      }
      if (vector_[i] < vector.vector_[i]) {
        result = false;
        break;
      }
    }
    if (equal) {
      return size_ > vector.size_;
    }
    return result;
  }
  bool operator<=(const Vector<T> &vector) const {
    int result = true;
    bool equal = true;
    for (size_t i = 0; i < std::min(size_, vector.size_); ++i) {
      if (vector_[i] != vector.vector_[i]) {
        equal = false;
      }
      if (vector_[i] < vector.vector_[i]) {
        result = true;
        break;
      }
      if (vector_[i] > vector.vector_[i]) {
        result = false;
        break;
      }
    }
    if (equal) {
      return size_ <= vector.size_;
    }
    return result;
  }
  bool operator>=(const Vector<T> &vector) const {
    int result = true;
    bool equal = true;
    for (size_t i = 0; i < std::min(size_, vector.size_); ++i) {
      if (vector_[i] != vector.vector_[i]) {
        equal = false;
      }
      if (vector_[i] > vector.vector_[i]) {
        result = true;
        break;
      }
      if (vector_[i] < vector.vector_[i]) {
        result = false;
        break;
      }
    }
    if (equal) {
      return size_ >= vector.size_;
    }
    return result;
  }
  bool operator==(const Vector<T> &vector) const {
    bool equal = true;
    for (size_t i = 0; i < std::min(size_, vector.size_); ++i) {
      if (vector_[i] != vector.vector_[i]) {
        equal = false;
      }
    }
    return equal && size_ == vector.size_;
  }
  bool operator!=(const Vector<T> &vector) const {
    return !(*this == vector);
  }

  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }
  bool Empty() const {
    return size_ == 0;
  }
  const T &At(const size_t &index) const {
    if (index >= size_) {
      throw std::out_of_range("Out of range");
    }
    return vector_[index];
  }
  T &At(const size_t &index) {
    if (index >= size_) {
      throw std::out_of_range("Out of range");
    }
    return vector_[index];
  }
  const T &Front() const {
    return vector_[0];
  }
  T &Front() {
    return vector_[0];
  }
  const T &Back() const {
    return vector_[size_ - 1];
  }
  T &Back() {
    return vector_[size_ - 1];
  }
  const T *Data() const {
    return vector_;
  }
  T *Data() {
    return vector_;
  }
  void Resize(const size_t &new_size) {
    if (new_size > capacity_) {
      T *new_vector = nullptr;
      if (new_size != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * new_size));
      }
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(new_size); ++index) {
          new (new_vector + index) T;
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_vector + index)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      index = 0;
      try {
        for (; index < static_cast<int64_t>(size_); ++index) {
          new_vector[index] = std::move(vector_[index]);
        }
      } catch (...) {
        for (; index >= 0; --index) {
          vector_[index] = std::move(new_vector[index]);
        }
        for (size_t i = 0; i < new_size; ++i) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      capacity_ = new_size;
    } else if (new_size > size_) {
      size_t index = size_;
      try {
        for (; index < new_size; ++index) {
          new (vector_ + index) T;
        }
      } catch (...) {
        for (size_t i = size_; i < index; ++i) {
          (vector_ + i)->~T();
        }
        throw;
      }
    } else {
      for (size_t i = new_size; i < size_; ++i) {
        (vector_ + i)->~T();
      }
    }
    size_ = new_size;
  }
  void Resize(const size_t &new_size, const T &value) {
    if (new_size > capacity_) {
      T *new_vector = nullptr;
      if (new_size != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * new_size));
      }
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(new_size); ++index) {
          new (new_vector + index) T;
        }
      } catch (...) {
        for (; index >= 0; --index) {
          (new_vector + index)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      index = 0;
      try {
        for (; index < static_cast<int64_t>(size_); ++index) {
          new_vector[index] = std::move(vector_[index]);
        }
      } catch (...) {
        for (; index >= 0; --index) {
          vector_[index] = std::move(new_vector[index]);
        }
        for (size_t i = 0; i < new_size; ++i) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      try {
        for (size_t i = size_; i < new_size; ++i) {
          new_vector[i] = value;
        }
      } catch (...) {
        for (size_t i = 0; i < new_size; ++i) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      capacity_ = new_size;
    } else if (new_size > size_) {
      size_t index = size_;
      try {
        for (; index < new_size; ++index) {
          new (vector_ + index) T;
          vector_[index] = value;
        }
      } catch (...) {
        for (size_t i = size_; i < index; ++i) {
          (vector_ + i)->~T();
        }
        throw;
      }
    } else {
      for (size_t i = new_size; i < size_; ++i) {
        (vector_ + i)->~T();
      }
    }
    size_ = new_size;
  }
  void Reserve(const size_t &new_cap) {
    if (new_cap > capacity_) {
      T *new_vector = nullptr;
      if (new_cap != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * new_cap));
      }
      for (size_t i = 0; i < size_; ++i) {
        new (new_vector + i) T;
      }
      for (size_t i = 0; i < size_; ++i) {
        new_vector[i] = std::move(vector_[i]);
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      capacity_ = new_cap;
    }
  }
  void ShrinkToFit() {
    T *new_vector = nullptr;
    if (size_ != 0) {
      new_vector = static_cast<T *>(operator new(sizeof(T) * size_));
    }
    int64_t index = 0;
    try {
      for (; index < static_cast<int64_t>(size_); ++index) {
        new (new_vector + index) T;
      }
    } catch (...) {
      for (; index >= 0; --index) {
        (new_vector + index)->~T();
      }
      operator delete(new_vector);
      throw;
    }
    index = 0;
    try {
      for (; index < static_cast<int64_t>(size_); ++index) {
        new_vector[index] = std::move(vector_[index]);
      }
    } catch (...) {
      for (; index >= 0; --index) {
        vector_[index] = std::move(new_vector[index]);
      }
      for (size_t i = 0; i < size_; i++) {
        (new_vector + i)->~T();
      }
      operator delete(new_vector);
      throw;
    }
    if (vector_ != nullptr) {
      for (size_t i = 0; i < size_; ++i) {
        (vector_ + i)->~T();
      }
      operator delete(vector_);
    }
    vector_ = new_vector;
    capacity_ = size_;
  }
  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (vector_ + i)->~T();
    }
    size_ = 0;
  }
  void PushBack(const T &elem) {
    if (size_ + 1 > capacity_) {
      T *new_vector = nullptr;
      if (capacity_ != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * 2 * capacity_));
      } else {
        new_vector = static_cast<T *>(operator new(sizeof(T)));
      }
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(size_); ++index) {
          new (new_vector + index) T(std::move(vector_[index]));
        }
      } catch (...) {
        for (; index >= 0; --index) {
          vector_[index] = std::move(new_vector[index]);
          (new_vector + index)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      try {
        new (new_vector + size_) T(elem);
      } catch (...) {
        for (size_t i = 0; i <= size_; i++) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      if (capacity_ == 0) {
        capacity_ = 1;
      } else {
        capacity_ *= 2;
      }
      size_ += 1;
    } else {
      try {
        new (vector_ + size_) T(elem);
      } catch (...) {
        (vector_ + size_)->~T();
        throw;
      }
      size_ += 1;
    }
  }
  void PushBack(T &&elem) {
    if (size_ + 1 > capacity_) {
      T *new_vector = nullptr;
      if (capacity_ != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * 2 * capacity_));
      } else {
        new_vector = static_cast<T *>(operator new(sizeof(T)));
      }
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(size_); ++index) {
          new (new_vector + index) T(std::move(vector_[index]));
        }
      } catch (...) {
        for (; index >= 0; --index) {
          vector_[index] = std::move(new_vector[index]);
          (new_vector + index)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      try {
        new (new_vector + size_) T(std::move(elem));
      } catch (...) {
        for (size_t i = 0; i <= size_; i++) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      if (capacity_ == 0) {
        capacity_ = 1;
      } else {
        capacity_ *= 2;
      }
      size_ += 1;
    } else {
      try {
        new (vector_ + size_) T(std::move(elem));
      } catch (...) {
        (vector_ + size_)->~T();
        throw;
      }
      size_ += 1;
    }
  }
  template <class... Args>
  void EmplaceBack(Args &&... args) {
    if (size_ + 1 > capacity_) {
      T *new_vector = nullptr;
      if (capacity_ != 0) {
        new_vector = static_cast<T *>(operator new(sizeof(T) * 2 * capacity_));
      } else {
        new_vector = static_cast<T *>(operator new(sizeof(T)));
      }
      int64_t index = 0;
      try {
        for (; index < static_cast<int64_t>(size_); ++index) {
          new (new_vector + index) T(std::move(vector_[index]));
        }
      } catch (...) {
        for (; index >= 0; --index) {
          vector_[index] = std::move(new_vector[index]);
          (new_vector + index)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      try {
        new (new_vector + size_) T(std::forward<Args>(args)...);
      } catch (...) {
        for (size_t i = 0; i <= size_; i++) {
          (new_vector + i)->~T();
        }
        operator delete(new_vector);
        throw;
      }
      if (vector_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
          (vector_ + i)->~T();
        }
        operator delete(vector_);
      }
      vector_ = new_vector;
      if (capacity_ == 0) {
        capacity_ = 1;
      } else {
        capacity_ *= 2;
      }
      size_ += 1;
    } else {
      try {
        new (vector_ + size_) T(std::forward<Args>(args)...);
      } catch (...) {
        (vector_ + size_)->~T();
        throw;
      }
      size_ += 1;
    }
  }
  void PopBack() {
    (vector_ + size_ - 1)->~T();
    size_ -= 1;
  }
};
