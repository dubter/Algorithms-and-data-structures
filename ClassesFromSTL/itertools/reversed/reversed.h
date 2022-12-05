#pragma once

template <class Container>
class Reversed {
 private:
  typename Container::const_reverse_iterator cbegin_, cend_;
  typename Container::reverse_iterator begin_, end_;

 public:
  explicit Reversed(Container &container) : begin_(container.rbegin()), end_(container.rend()) {
  }

  explicit Reversed(const Container &container) : cbegin_(container.crbegin()), cend_(container.crend()) {
  }

  typename Container::reverse_iterator begin() {  // NOLINT
    return begin_;
  }

  typename Container::const_reverse_iterator begin() const {  // NOLINT
    return cbegin_;
  }

  typename Container::reverse_iterator end() {  // NOLINT
    return end_;
  }

  typename Container::const_reverse_iterator end() const {  // NOLINT
    return cend_;
  }
};