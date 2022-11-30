#include <iostream>
#include <vector>

int LevenshteinDistance(const std::string &str1, const std::string &str2) {
  int len1, len2, minimum;
  len1 = static_cast<int>(str1.size());
  len2 = static_cast<int>(str2.size());
  std::vector<std::vector<int>> distance(len1 + 1);
  for (int i = 0; i <= len1; i++) {
    distance[i].resize(len2 + 1);
  }
  for (int i = 0; i <= len1; i++) {
    distance[i][0] = i;
  }
  for (int j = 0; j <= len2; j++) {
    distance[0][j] = j;
  }
  for (int i = 1; i <= len1; i++) {
    for (int j = 1; j <= len2; j++) {
      minimum = std::min(distance[i - 1][j], distance[i][j - 1]) + 1;
      if (str1[i - 1] == str2[j - 1]) {
        distance[i][j] = std::min(minimum, distance[i - 1][j - 1]);
      } else {
        distance[i][j] = std::min(minimum, distance[i - 1][j - 1] + 1);
      }
    }
  }
  return distance[len1][len2];
}

int main() {
  std::string str1, str2;
  std::cin >> str1;
  std::cin >> str2;
  std::cout << LevenshteinDistance(str1, str2);
  return 0;
}