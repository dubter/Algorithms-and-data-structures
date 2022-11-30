#pragma once
#include <vector>
#include <random>
#include "universal_hash.h"
#include <optional>

template <class KeyType, class HashType = UniversalHash>
class FrozenSet {
 public:
  FrozenSet() = default;
  template <class Iterator,
      class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag,
                                                 typename std::iterator_traits<Iterator>::iterator_category>>,
      class Generator>
  FrozenSet(Iterator first, Iterator last, Generator& generator) {
    size_ = 0;
    for (auto iter = first; iter != last; ++iter) {
      ++size_;
    }
    size_t sum = 0;
    do {
      sum = 0;
      buckets_.clear();
      buckets_.resize(size_);
      hash_ = HashType::GenerateHash(generator);
      for (auto iter = first; iter != last; ++iter) {
        size_t key_hash = Hash(*iter);
        buckets_[key_hash].Insert(*iter);
      }
      for (size_t i = 0; i < size_; ++i) {
        sum += buckets_[i].Size() * buckets_[i].Size();
      }
    } while (sum >= 4 * size_);
    for (size_t i = 0; i < size_; ++i) {
      buckets_[i].BuildTable(generator);
    }
  }
  FrozenSet(const FrozenSet&) = default;
  FrozenSet(FrozenSet&&) = default;

  FrozenSet& operator=(const FrozenSet&) = default;
  FrozenSet& operator=(FrozenSet&&) = default;

  size_t Size() const {
    return size_;
  }
  bool Empty() const {
    return size_ == 0;
  }
  void Clear() {
    buckets_.clear();
    hash_ = HashType();
    size_ = 0;
  }
  bool Find(const KeyType& key) const {
    if (Empty()) {
      return false;
    }
    size_t key_hash = Hash(key);
    return buckets_[key_hash].Find(key);
  }

 private:
  class Bucket {
   public:
    Bucket() = default;

    void Insert(const KeyType& key) {
      bucket_.push_back(key);
      ++size_;
    }

    size_t Size() const {
      return size_;
    }

    template <class Generator>
    void BuildTable(Generator& generator) {
      std::vector<std::optional<KeyType>> table(size_ * size_);
      hash_ = HashType::GenerateHash(generator);
      size_t key_hash = 0;
      for (size_t i = 0; i < size_; ++i) {
        key_hash = hash_(bucket_[i].value()) % (size_ * size_);
        if (table[key_hash].has_value()) {
          BuildTable(generator);
          return;
        }
        table[key_hash] = bucket_[i].value();
      }
      bucket_.swap(table);
      size_ *= size_;
    }

    bool Find(const KeyType& key) const {
      if (size_ == 0) {
        return false;
      }
      size_t key_hash = Hash(key);
      if (bucket_[key_hash].has_value()) {
        return bucket_[key_hash].value() == key;
      }
      return false;
    }

   private:
    std::vector<std::optional<KeyType>> bucket_;
    HashType hash_;
    size_t size_ = 0;

    size_t Hash(const KeyType& key) const {
      return hash_(key) % size_;
    }
  };

  void Swap(FrozenSet& other) {
    std::swap(buckets_, other.buckets_);
    std::swap(hash_, other.hash_);
    std::swap(size_, other.size_);
  }

  std::vector<Bucket> buckets_;
  HashType hash_;
  size_t size_ = 0;

  size_t Hash(const KeyType& key) const {
    return hash_(key) % size_;
  }
};
