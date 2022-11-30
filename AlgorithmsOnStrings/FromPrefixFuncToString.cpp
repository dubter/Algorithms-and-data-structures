#include <iostream>
#include <vector>
#include <set>

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
  std::vector<int> prefix_func;
  size_t size = 0;
  std::cin >> size;
  prefix_func.resize(size);
  for (int &i : prefix_func) {
    std::cin >> i;
  }
  std::cout << FromPrefixFuncToString(prefix_func);
  return 0;
}
