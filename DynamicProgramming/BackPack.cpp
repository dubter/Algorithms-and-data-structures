#include <iostream>
#include <vector>

struct Product {
  int cost;
  int weight;
};

void FindSet(std::vector<std::vector<int>> &products, std::vector<Product> &startData, int i, int j) {
  if (products[i][j] == 0) {
    return;
  }
  if (products[i - 1][j] == products[i][j]) {
    FindSet(products, startData, i - 1, j);
  } else {
    FindSet(products, startData, i - 1, j - startData[i].weight);
    std::cout << i << "\n";
  }
}

void PrintNumbersOfThingsFromBackPack(std::vector<std::vector<int>> &products, std::vector<Product> &startData, int number_things, int weight_backpack) {
  for (int i = 1; i <= number_things; i++) {
    for (int j = 1; j <= weight_backpack; j++) {
      if (j >= startData[i].weight) {
        products[i][j] = std::max(products[i - 1][j], products[i - 1][j - startData[i].weight] + startData[i].cost);
      } else {
        products[i][j] = products[i - 1][j];
      }
    }
  }
  FindSet(products, startData, number_things, weight_backpack);
}

int main() {
  int number_things = 0, weight_backpack = 0;
  std::cin >> number_things;
  std::cin >> weight_backpack;
  std::vector<std::vector<int>> products(number_things + 1);
  for (int i = 0; i <= number_things; i++) {
    products[i].resize(weight_backpack + 1, 0);
  }
  std::vector<Product> startData(number_things + 1);
  for (int i = 1; i <= number_things; i++) {
    std::cin >> startData[i].weight;
  }
  for (int i = 1; i <= number_things; i++) {
    std::cin >> startData[i].cost;
  }
  PrintNumbersOfThingsFromBackPack(products, startData, number_things, weight_backpack);
  return 0;
}