#include <iostream>
#include <vector>
#include <set>

std::vector<int> FromZToPrefix(const std::vector<int> &z_arr) {
  std::vector<int> prefix_arr(z_arr.size(), 0);
  for (int i = 1; i < static_cast<int>(z_arr.size()); ++i) {
    for (int delta = z_arr[i] - 1; delta >= 0; --delta) {
      if (prefix_arr[i + delta] > 0) {
        break;
      }
      prefix_arr[i + delta] = delta + 1;
    }
  }
  return prefix_arr;
}

std::string FromPrefixFuncToString(std::vector<int> prefix_func) {
  std::string string;
  string.resize(prefix_func.size());
  string[0] = 'a';
  for (size_t i = 1; i < prefix_func.size(); i++) {
    if (prefix_func[i] > 0) {
      string[i] = string[prefix_func[i] - 1];
    } else {
      std::set<char> ban = {};
      size_t k = prefix_func[i - 1];
      while (k > 0) {
        ban.emplace(string[k]);
        k = prefix_func[k - 1];
      }
      for (char symbol = 'b'; symbol <= 'z'; symbol++) {
        if (ban.find(symbol) == ban.end()) {
          string[i] = symbol;
          break;
        }
      }
    }
  }
  return string;
}

int main() {
  std::vector<int> z_arr;
  size_t size = 0;
  std::cin >> size;
  z_arr.resize(size);
  for (int &i : z_arr) {
    std::cin >> i;
  }
  std::cout << FromPrefixFuncToString(FromZToPrefix(z_arr));
  return 0;
}

