#pragma once

class Array {
  int64_t size_;
  int64_t capacity_;
  int64_t *data_;

  void Resize();

 public:
  Array();

  int64_t GetSize() const;
  void PushBack(int64_t number);
  void Reserve(const int64_t &new_capacity, const int64_t &val);

  const int64_t &Back() const;
  const int64_t &Front() const;

  int64_t &operator[](int64_t pos);
  const int64_t &operator[](int64_t pos) const;

  int64_t *Data() const;
  void Clear();
  Array &operator=(const Array &other);

  friend std::ostream &operator<<(std::ostream &stream, const Array &array);

  ~Array();
};