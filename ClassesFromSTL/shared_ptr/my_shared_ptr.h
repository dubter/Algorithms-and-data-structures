#pragma once
#include <iostream>

template <class T>
class SharedPtr {
 private:
  T *ptr_;
  int *count_;

 public:
  SharedPtr() : ptr_(nullptr) {
  }

  SharedPtr(T *ptr) : ptr_(ptr) {  //  NOLINT
    if (ptr != nullptr) {
      count_ = new int(1);
    }
  }

  SharedPtr(const SharedPtr &shared_ptr) {
    ptr_ = shared_ptr.ptr_;
    if (shared_ptr.ptr_ != nullptr) {
      count_ = shared_ptr.count_;
      (*count_)++;
    }
  }

  SharedPtr &operator=(const SharedPtr &shared_ptr) {
    if (this != &shared_ptr) {
      if (ptr_ != nullptr) {
        --(*count_);
        if (*count_ == 0) {
          delete ptr_;
          delete count_;
        }
      }
      ptr_ = shared_ptr.ptr_;
      if (shared_ptr.ptr_ != nullptr) {
        count_ = shared_ptr.count_;
        (*count_)++;
      }
    }
    return *this;
  }

  SharedPtr(SharedPtr &&other) noexcept : ptr_(other.ptr_) {
    if (other.ptr_ != nullptr) {
      count_ = other.count_;
    }
    other.ptr_ = nullptr;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (this != &other) {
      if (ptr_ != nullptr) {
        (*count_)--;
        if (*count_ == 0) {
          delete ptr_;
          delete count_;
        }
      }
      ptr_ = other.ptr_;
      if (other.ptr_ != nullptr) {
        count_ = other.count_;
      }
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ != nullptr) {
      --(*count_);
      if (*count_ == 0) {
        delete ptr_;
        delete count_;
      }
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  void Reset(T *ptr = nullptr) {
    if (ptr_ != nullptr) {
      --(*count_);
      if (*count_ == 0) {
        delete ptr_;
        delete count_;
      }
    }
    ptr_ = ptr;
    if (ptr != nullptr) {
      count_ = new int(1);
    }
  }

  void Swap(SharedPtr<T> &shared_ptr) {
    T *tmp1 = std::move(ptr_);
    ptr_ = std::move(shared_ptr.ptr_);
    shared_ptr.ptr_ = std::move(tmp1);
    int *tmp2 = std::move(count_);
    count_ = std::move(shared_ptr.count_);
    shared_ptr.count_ = std::move(tmp2);
  }

  T *Get() const {
    return ptr_;
  }

  int UseCount() const {
    if (ptr_ == nullptr) {
      return 0;
    }
    return *count_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};