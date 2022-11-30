#include <iostream>
#include <cstring>
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
  std::string str;
  std::cin >> str;
  std::vector<size_t> prefix_arr = PrefixFunc(str);
  for (size_t i = 0; i < prefix_arr.size(); i++) {
    std::cout << prefix_arr[i] << " ";
  }
  return 0;
}
