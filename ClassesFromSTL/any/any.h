#pragma once
#include <stdexcept>
#include <memory>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "BadAnyCast error";
  }
};

struct IHolder {
  virtual IHolder *Clone() const = 0;
  virtual ~IHolder() = default;
};

template <class T>
struct AnyHolder final : IHolder {
  T value_;

  AnyHolder(const T &value) : value_(value) {  // NOLINT
  }

  AnyHolder(T &&value) noexcept : value_(value) {  // NOLINT
  }

  AnyHolder *Clone() const final {
    auto *ret = new AnyHolder<T>(value_);
    return ret;
  }

  ~AnyHolder() final = default;
};

class Any {
 public:
  Any() = default;

  Any(const Any &other) : ptr_(other.ptr_->Clone()) {
  }

  Any(Any &&other) noexcept : ptr_(other.ptr_->Clone()) {
  }

  template <class T>
  Any(T &&value) noexcept {  // NOLINT
    ptr_ = static_cast<std::unique_ptr<IHolder>>((new AnyHolder<T>(std::forward<T>(value))));
  }

  template <class T>
  Any &operator=(T &&value) {
    ptr_ = static_cast<std::unique_ptr<IHolder>>((new AnyHolder<T>(std::forward<T>(value))));
    return *this;
  }

  Any &operator=(Any &&other) {
    ptr_ = static_cast<std::unique_ptr<IHolder>>(other.ptr_->Clone());
    other.ptr_ = nullptr;
    return *this;
  }

  Any &operator=(Any &other) {
    if (this != &other) {
      ptr_ = static_cast<std::unique_ptr<IHolder>>(other.ptr_->Clone());
    }
    return *this;
  }

  void Reset() {
    ptr_ = nullptr;
  }

  void Swap(Any &other) {
    std::swap(ptr_, other.ptr_);
  }

  bool HasValue() const {
    return ptr_ != nullptr;
  }

  auto GetPtr() const {
    return ptr_.get();
  }

 private:
  std::unique_ptr<IHolder> ptr_ = nullptr;
};

template <class T>
T AnyCast(const Any &value) {
  if (dynamic_cast<AnyHolder<T> *>(value.GetPtr()) == nullptr) {
    throw BadAnyCast();
  }
  return dynamic_cast<AnyHolder<T> *>(value.GetPtr())->value_;
}