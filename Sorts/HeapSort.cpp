#include <iostream>
#include <vector>

class Heap {
 private:
  std::vector<int> heap_;
  int size_ = 0;

  int Parent(int index) {
    return (index - 1) / 2;
  }

  int RightChild(int index) {
    return 2 * index + 2;
  }

  int LeftChild(int index) {
    return 2 * index + 1;
  }

 public:
  Heap() = default;
  explicit Heap(std::vector<int> &array) {
    heap_ = array;
    size_ = array.size();
    for (int i = Parent(size_ - 1); i >= 0; --i) {
      SiftDown(i, size_);
    }
  }

  void SiftUp(int index) {
    while (Parent(index) >= 0 && index > 0 && heap_[index] < heap_[(index - 1) / 2]) {
      std::swap(heap_[index], heap_[Parent(index)]);
      index = Parent(index);
    }
  }

  void SiftDown(int index, int count) {
    int left, right, j;
    while (LeftChild(index) < count) {
      left = LeftChild(index);
      right = RightChild(index);
      j = left;
      if (right < count && heap_[right] < heap_[left]) {
        j = right;
      }
      if (heap_[index] <= heap_[j]) {
        break;
      }
      std::swap(heap_[index], heap_[j]);
      index = j;
    }
  }

  std::vector<int> &HeapSort() {
    for (int i = size_ - 1; i > 0; --i) {
      std::swap(heap_[0], heap_[i]);
      SiftDown(0, i - 1);
    }
    for (int i = 0; i < size_ / 2; ++i) {
      std::swap(heap_[i], heap_[size_ - i - 1]);
    }
    return heap_;
  }

  void Insert(int num) {
    heap_.push_back(num);
    ++size_;
    SiftUp(size_ - 1);
  }

  int ExtractMin() {
    --size_;
    int root = heap_[0];
    heap_[0] = heap_.back();
    heap_.pop_back();
    SiftDown(0, size_);
    return root;
  }

  bool Empty() const {
    return size_ == 0;
  }
};

int main() {
  size_t number_elems;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (auto &elem : array) {
    std::cin >> elem;
  }
  Heap heap(array);
  array = heap.HeapSort();
  for (auto &elem : array) {
    std::cout << elem << " ";
  }
  return 0;
}
