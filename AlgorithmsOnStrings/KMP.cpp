#include <iostream>
#include <vector>

std::vector<int> PrefixFunc(std::string string) {
  int tmp = 0;
  std::vector<int> prefix_arr(string.size(), 0);
  for (int i = 1; i < static_cast<int>(string.size()); i++) {
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

std::vector<int> KMP(const std::string &sub_str, const std::string &main_string) {
  int sub_str_size = static_cast<int>(sub_str.size());
  int main_str_size = static_cast<int>(main_string.size());
  std::vector<int> positions;
  std::vector<int> prefix_func = PrefixFunc(sub_str + "#" + main_string);
  for (int i = 0; i < main_str_size; ++i) {
    if (prefix_func[sub_str_size + i + 1] == sub_str_size) {
      positions.emplace_back(i - sub_str_size);
    }
  }
  return positions;
}

int main() {
  std::string sub_str;
  std::string main_str;
  std::cin >> main_str >> sub_str;
  std::vector<int> positions = KMP(sub_str, main_str);
  for (int i = 0; i < static_cast<int>(positions.size()); i++) {
    std::cout << positions[i] + 1 << "\n";
  }
  return 0;
}
