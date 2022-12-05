#pragma once

template <class T>
class UniquePtr {
 private:
  T *ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T *ptr) : ptr_(ptr) {
  }

  UniquePtr(const UniquePtr &) = delete;
  UniquePtr &operator=(const UniquePtr &) = delete;

  UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  T *Release() {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

  void Reset(T *ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr<T> &ptr) {
    T *tmp = ptr_;
    ptr_ = ptr.ptr_;
    ptr.ptr_ = tmp;
  }

  T *Get() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};