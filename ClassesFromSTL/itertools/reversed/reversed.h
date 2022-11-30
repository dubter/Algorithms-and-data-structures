#pragma once

template <class Container>
class Reversed {
 public:
  explicit Reversed(Container &container) : beg_(container.rbegin()), end_(container.rend()) {
  }
  explicit Reversed(const Container &container) : cbeg_(container.crbegin()), cend_(container.crend()) {
  }
  typename Container::reverse_iterator begin() {  // NOLINT
    return beg_;
  }
  typename Container::reverse_iterator end() {  // NOLINT
    return end_;
  }
  typename Container::const_reverse_iterator begin() const {  // NOLINT
    return cbeg_;
  }
  typename Container::const_reverse_iterator end() const {  // NOLINT
    return cend_;
  }

 private:
  typename Container::reverse_iterator beg_, end_;
  typename Container::const_reverse_iterator cbeg_, cend_;
};