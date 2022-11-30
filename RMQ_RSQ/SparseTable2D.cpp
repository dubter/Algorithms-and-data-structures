/*
 Твоя наука — полная ерунда! Чего из-за неё волноваться? Если ты не откроешь какую-нибудь молекулу, её обязательно откроет кто-то другой. А вот если с нервами что-то случится, никто к тебе не придёт и не скажет: «Возьми, дружок, пучок моих нервишек, а то, кажется, у меня лишние!»

Смешарики открыли для себя 2D-строй — теперь построение будет не в одну шеренгу, а в прямоугольник. Для новой серии научно-популярного шоу смешарикам необходимо найти в творческой команде самого сообразительного смешарика, принявшего участие в наименьшем количестве выпусков. Командой может быть любой подпрямоугольник смешариков. Вам нужно помочь нашим героям для каждой команды, которую они попросят, найти самого редкого гостя на экране.
 */

#include <iostream>
#include <vector>
#include <cmath>

class SparseTable2d {
 public:
  SparseTable2d(std::vector<std::vector<std::vector<std::vector<int32_t>>>> &vec, int32_t n, int32_t m)
      : tbl_(vec), n_(n), m_(m){};
  void Build(std::vector<std::vector<int32_t>> &vec) {
    n_ = int32_t(vec.size());
    m_ = int32_t(vec[0].size());
    int32_t lgn = log2(n_), lgm = log2(m_);
    tbl_.assign(n_, std::vector<std::vector<std::vector<int32_t>>>(
        lgn + 1, std::vector<std::vector<int32_t>>(m_, std::vector<int32_t>(lgm + 1))));

    for (int32_t i = 0; i < n_; i++) {
      for (int32_t j = 0; j < m_; j++) {
        tbl_[i][0][j][0] = vec[i][j];
      }

      for (int32_t j = 1; j <= lgm; j++) {
        int32_t tmp = m_ - (1 << (j - 1));
        for (int32_t k = 0; k < tmp; k++) {
          tbl_[i][0][k][j] = std::min(tbl_[i][0][k][j - 1], tbl_[i][0][k + (1 << (j - 1))][j - 1]);
        }
      }
    }

    for (int32_t j = 1; j <= lgn; j++) {
      int32_t tmp = n_ - (1 << (j - 1));
      for (int32_t i = 0; i < tmp; i++) {
        int32_t t = i + (1 << (j - 1));
        for (int32_t l = 0; l <= lgm; l++) {
          for (int32_t k = 0; k < m_; k++) {
            tbl_[i][j][k][l] = std::min(tbl_[i][j - 1][k][l], tbl_[t][j - 1][k][l]);
          }
        }
      }
    }
  }

  int32_t Query(int32_t r1, int32_t c1, int32_t r2, int32_t c2) {
    int32_t lgn = log2(r2 - r1 + 1), lgm = log2(c2 - c1 + 1);
    int32_t a = std::min(tbl_[r1][lgn][c1][lgm], tbl_[r1][lgn][c2 - (1 << lgm) + 1][lgm]);
    int32_t b =
        std::min(tbl_[r2 - (1 << lgn) + 1][lgn][c1][lgm], tbl_[r2 - (1 << lgn) + 1][lgn][c2 - (1 << lgm) + 1][lgm]);
    return std::min(a, b);
  }

 private:
  std::vector<std::vector<std::vector<std::vector<int32_t>>>> tbl_;
  int32_t n_;
  int32_t m_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t m, n, q, tmp, x1, x2, y1, y2;
  std::vector<std::vector<int32_t>> number_releases;
  std::vector<std::vector<std::vector<std::vector<int32_t>>>> tbl;
  std::cin >> n >> m;
  number_releases.resize(n);
  for (int32_t i = 0; i < n; ++i) {
    number_releases[i].resize(m);
    for (int32_t j = 0; j < m; ++j) {
      std::cin >> tmp;
      number_releases[i][j] = tmp;
    }
  }
  SparseTable2d sparse_table_2_d{tbl, n, m};
  sparse_table_2_d.Build(number_releases);
  std::cin >> q;
  for (int32_t i = 0; i < q; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;
    std::cout << sparse_table_2_d.Query(x1, y1, x2, y2) << "\n";
  }
  return 0;
}