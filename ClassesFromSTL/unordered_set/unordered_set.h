#pragma once
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <vector>

template <class TypeValue>
class UnorderedSet {
 private:
  size_t size_buckets_;
  size_t size_elements_;
  std::vector<std::list<TypeValue>> unordered_set_;

 public:
  UnorderedSet() : size_buckets_(0), size_elements_(0), unordered_set_(std::vector<std::list<TypeValue>>()){};

  explicit UnorderedSet(const size_t& count)
      : size_buckets_(count), size_elements_(0), unordered_set_(std::vector<std::list<TypeValue>>(count)){};

  template <class Iterator>
  UnorderedSet(const Iterator& begin, const Iterator& end) {
    unordered_set_ = std::vector<std::list<TypeValue>>();
    size_elements_ = 0;
    size_buckets_ = 0;
    for (auto it = begin; it != end; ++it) {
      size_buckets_++;
      size_elements_++;
      unordered_set_.emplace_back(std::list<TypeValue>());
    }

    for (auto it = begin; it != end; ++it) {
      auto id = std::hash<TypeValue>{}(*it) % size_buckets_;
      unordered_set_[id].push_back(*it);
    }
  }

  UnorderedSet(UnorderedSet<TypeValue>&& other)
      : size_buckets_(other.size_buckets_), size_elements_(other.size_elements_), unordered_set_(other.unordered_set_) {
    other.size_buckets_ = 0;
    other.unordered_set_.clear();
    other.size_elements_ = 0;
  }

  UnorderedSet(const UnorderedSet<TypeValue>& other)
      : size_buckets_(other.size_buckets_)
      , size_elements_(other.size_elements_)
      , unordered_set_(other.unordered_set_){};

  ~UnorderedSet() = default;

  UnorderedSet& operator=(UnorderedSet<TypeValue>&& other) {
    if (&other != this) {
      size_buckets_ = other.size_buckets_;
      size_elements_ = other.size_elements_;
      unordered_set_ = other.unordered_set_;
      other.size_buckets_ = 0;
      other.size_elements_ = 0;
      other.unordered_set_.clear();
    }
    return *this;
  };
  UnorderedSet& operator=(const UnorderedSet<TypeValue>& other) {
    if (&other != this) {
      size_elements_ = other.size_elements_;
      size_buckets_ = other.size_buckets_;
      unordered_set_ = other.unordered_set_;
    }
    return *this;
  }

  bool Empty() const {
    return size_elements_ == 0;
  }

  const size_t& Size() const {
    return size_elements_;
  }

  void Clear() {
    size_elements_ = 0;
  }

  bool Find(const TypeValue& x) const {
    if (size_buckets_ == 0 || size_elements_ == 0) {
      return false;
    }
    for (const TypeValue& elem : unordered_set_[std::hash<TypeValue>{}(x) % size_buckets_]) {
      if (elem == x) {
        return true;
      }
    }
    return false;
  }

  void Insert(const TypeValue& x) {
    if (size_buckets_ == 0) {
      Rehash(1);
    }
    auto index = std::hash<TypeValue>{}(x) % size_buckets_;
    unordered_set_[index].push_back(x);
    size_elements_++;
    if (size_elements_ > size_buckets_) {
      Rehash(2 * size_buckets_);
    }
  };

  void Insert(TypeValue&& x) {
    if (size_buckets_ == 0) {
      Rehash(1);
    }
    auto index = std::hash<TypeValue>{}(x) % size_buckets_;
    unordered_set_[index].push_back(x);
    size_elements_++;
    if (size_elements_ > size_buckets_) {
      Rehash(2 * size_buckets_);
    }
  }

  void Erase(const TypeValue& x) {
    while (Find(x)) {
      auto index = std::hash<TypeValue>{}(x) % size_buckets_;
      unordered_set_[index].remove(x);
      size_elements_--;
    }
  }

  void Rehash(const size_t& new_bucket_count) {
    if (new_bucket_count >= size_elements_ && new_bucket_count != size_buckets_) {
      UnorderedSet<TypeValue> res(new_bucket_count);
      for (size_t index = 0; index < size_buckets_; index++) {
        for (auto& j : unordered_set_[index]) {
          res.Insert(j);
        }
      }
      *this = res;
    }
  }

  void Reserve(const size_t& new_bucket_count) {
    if (new_bucket_count <= size_buckets_) {
      return;
    }
    Rehash(new_bucket_count);
  }

  double LoadFactor() const {
    if (size_buckets_ != 0) {
      return static_cast<double>(size_elements_) / (size_buckets_);
    }
    return 0;
  }

  size_t BucketSize(const size_t& index) const {
    if (index < size_buckets_) {
      return unordered_set_[index].size();
    }
    return 0;
  }

  const size_t& BucketCount() const {
    return size_buckets_;
  }

  size_t Bucket(const TypeValue& key) const {
    return std::hash<TypeValue>{}(key) % size_buckets_;
  }
};