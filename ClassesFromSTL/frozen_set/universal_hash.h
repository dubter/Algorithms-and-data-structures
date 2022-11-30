#pragma once
#include <random>

class UniversalHash {
 public:
  static const uint64_t kMaxValue = 1073676286;

  UniversalHash(uint64_t a = 1, uint64_t b = 0) : a_(a % (kMaxValue + 1)), b_(b % (kMaxValue + 1)){};  // NOLINT

  uint64_t operator()(uint64_t number) const {
    return (a_ * (number % (kMaxValue + 1)) + b_) % (kMaxValue + 1);
  }

  template <class Generator>
  static UniversalHash GenerateHash(Generator& generator) {
    uint64_t a = generator();
    uint64_t b = generator();
    return {a, b};
  }

 private:
  uint64_t a_ = 1;
  uint64_t b_ = 0;
};