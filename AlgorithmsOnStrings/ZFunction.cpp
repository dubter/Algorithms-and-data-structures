#include <iostream>
#include <vector>

std::vector<int> ZFunc(const std::string &string) {
  int left = 0;
  int right = 0;
  std::vector<int> z_arr;
  z_arr.resize(string.size(), 0);
  z_arr[0] = static_cast<int>(string.size());
  for (int i = 1; i < static_cast<int>(string.size()); ++i) {
    if (i < right) {
      z_arr[i] = std::min(z_arr[i - left], right - i);
    }
    while (i + z_arr[i] < static_cast<int>(string.size()) && string[z_arr[i]] == string[i + z_arr[i]]) {
      ++z_arr[i];
    }
    if (right < i + z_arr[i]) {
      left = i;
      right = i + z_arr[i];
    }
  }
  return z_arr;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  std::vector<int> z_arr = ZFunc(str);
  for (int &i : z_arr) {
    std::cout << i << " ";
  }
  return 0;
}
