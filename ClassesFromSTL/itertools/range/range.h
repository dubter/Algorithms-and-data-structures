#pragma once

class Range {
 private:
  int64_t start_;
  int64_t end_;
  int64_t step_;

 public:
  class RangeIterator {
   private:
    int64_t state_;
    int64_t step_;

   public:
    using IteratorCategory = std::bidirectional_iterator_tag;
    using ValueType = int64_t;
    using DifferenceType = int64_t;
    using Reference = int64_t;
    using Pointer = void;

    explicit RangeIterator(int64_t state = 0, int64_t step = 1) {
      state_ = state;
      step_ = step;
    }
    const int64_t &operator*() const {
      return state_;
    }
    int64_t operator[](int64_t index) const {
      return state_ + step_ * index;
    }
    RangeIterator &operator++() {
      state_ += step_;
      return *this;
    }
    RangeIterator &operator--() {
      state_ -= step_;
      return *this;
    }
    RangeIterator &operator+=(int64_t num) {
      state_ += step_ * num;
      return *this;
    }
    RangeIterator &operator-=(int64_t num) {
      state_ -= step_ * num;
      return *this;
    }

    bool operator==(RangeIterator iterator) {
      return state_ == iterator.state_ && step_ == iterator.step_;
    }
    bool operator!=(RangeIterator iterator) {
      if (step_ > 0) {
        return state_ < iterator.state_;
      }
      return state_ > iterator.state_;
    }
  };
  using Iterator = RangeIterator;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ValueType = Iterator::ValueType;

  explicit Range(int64_t end) : start_(0), end_(end), step_(1) {
    if (end_ < start_) {
      end_ = start_;
    }
  }
  Range(int64_t start, int64_t end, int64_t step = 1) : start_(start), end_(end), step_(step) {
    if ((end_ < start_ && step >= 0) || (step <= 0 && start_ < end_)) {
      end_ = start_;
    }
  }
  RangeIterator begin() const {  // NOLINT
    return RangeIterator(start_, step_);
  }
  RangeIterator end() const {  // NOLINT
    return RangeIterator(end_, step_);
  }
};
