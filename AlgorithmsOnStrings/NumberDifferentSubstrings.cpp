#include <iostream>
#include <vector>

std::vector<size_t> PrefixFunc(std::string string) {
  size_t tmp = 0;
  std::vector<size_t> prefix_arr(string.size(), 0);
  for (size_t i = 1; i < string.size(); i++) {
    tmp = prefix_arr[i - 1];
    while (tmp > 0 && string[i] != string[tmp]) {
      tmp = prefix_arr[tmp - 1];
    }
    if (string[i] == string[tmp]) {
      tmp++;
    }
    prefix_arr[i] = tmp;
  }
  return prefix_arr;
}

int main() {
  std::string string;
  std::string sub_str;
  std::cin >> string;
  size_t count_sub_strings = 0;
  size_t max_elem = 0;
  for (size_t i = 0; i < string.size(); ++i) {
    sub_str = string[i] + sub_str;
    std::vector<size_t> prefix_arr = PrefixFunc(sub_str);
    max_elem = 0;
    for (size_t i = 0; i < prefix_arr.size(); ++i) {
      if (max_elem < prefix_arr[i]) {
        max_elem = prefix_arr[i];
      }
    }
    count_sub_strings += i + 1 - max_elem;
  }
  std::cout << count_sub_strings;
  return 0;
}
