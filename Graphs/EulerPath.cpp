// Для решения транспортной проблемы в некотором городе до недавнего времени использовались N автобусных маршрутов. Каждый маршрут начинался на одной из M площадей и там же заканчивался. В процессе проезда по маршруту автобус мог несколько раз проезжать одну и ту же площадь, и даже мог проезжать более одного раза по одной и той же улице в одном и том же направлении. В определенный момент местные власти решили сократить количество автобусных маршрутов в городе до одного. По их мнению, должен был остаться лишь один маршрут, который проходил бы по всем улицам, по которым раньше проходили автобусные маршруты, причем в том же направлении (но не обязательно в том же порядке). Если по каким-либо улицам автобусы ездили в обоих направлениях, то и новый маршрут должен проходить по этим улицам в обоих направлениях. По тем улицам и в тех направлениях, по которым раньше автобусы не ездили, новый маршрут проходить не должен. Однако так как контролеров увольнять нельзя, власти решили, что по каждой улице в каждом направлении новый маршрут должен проходить столько раз, сколько по ней проходили все старые маршруты, вместе взятые. Требуется написать программу, которая для заданных исходных данных определяет требуемый местным властям автобусный маршрут.

// Формат ввода
// Входной файл состоит из следующей последовательности строк. Первая строка содержит число N (N ≤ 10^5) — количество автобусных маршрутов, M (M ≤ 10^5) — количество площадей. Каждая из последующих N строк служит для описания соответствующего автобусного маршрута и содержит сначала число k (k ≤ 10^5), определяющее количество элементов маршрута, а затем k + 1 чисел, задающих номера площадей, которые последовательно проезжает автобус на этом маршруте. Общая длина маршрутов не более 10^5 улиц. При описании маршрута всегда задаются номера первой и последней площади маршрута, причем они всегда совпадают.
// Формат вывода
// В строку через пробел выведите число площадей в найденном маршруте (стартовая и конечная площади совпадают, но учитываются по отдельности) и саму последовательность площадей. Если организовать требуемый маршрут не удастся, вывод должен содержать одно число - 0. A

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <stack>

enum COLOUR {
  WHITE,
  GREY,
  BLACK,
};

class Graph {
 private:
  std::vector<std::vector<size_t>> adjacency_list_;
  std::vector<COLOUR> colors_;
  std::vector<size_t> deg_in_;
  std::vector<size_t> deg_out_;
  std::vector<size_t> euler_path_;
  std::set<std::pair<size_t, size_t>> edges_;
  std::map<std::pair<size_t, size_t>, size_t> count_each_edge_;
  size_t ver_start_ = 100001;

 public:
  explicit Graph(size_t size) : adjacency_list_(size), colors_(size, WHITE), deg_in_(size, 0), deg_out_(size, 0){};

  bool IsEulerGraph() {
    for (size_t i = 0; i < adjacency_list_.size(); ++i) {
      if (!adjacency_list_[i].empty() && ver_start_ == 100001) {
        ver_start_ = i;
      }
      if (deg_in_[i] != deg_out_[i]) {
        return false;
      }
    }
    if (ver_start_ == 100001) {
      return false;
    }
    DFS(ver_start_);
    for (size_t i = 0; i < adjacency_list_.size(); ++i) {
      if (!adjacency_list_[i].empty() && colors_[i] == WHITE) {
        return false;
      }
    }
    return true;
  }

  std::vector<size_t> EulerPath() {
    std::stack<size_t> stack;
    stack.push(ver_start_);
    while (!stack.empty()) {
      size_t ver = stack.top();
      bool found_edge = false;
      for (auto &neighbour : adjacency_list_[ver]) {
        std::pair<size_t, size_t> pair_ver = std::make_pair(ver, neighbour);
        if (count_each_edge_.find(pair_ver) != count_each_edge_.end() && count_each_edge_[pair_ver] != 0) {
          stack.push(neighbour);
          --count_each_edge_[pair_ver];
          if (count_each_edge_[pair_ver] == 0) {
            edges_.erase(pair_ver);
          }
          found_edge = true;
          break;
        }
      }
      if (!found_edge) {
        stack.pop();
        euler_path_.push_back(ver);
      }
    }
    return euler_path_;
  }

  void InsertEdgeOrient(size_t ver_first, size_t ver_second) {
    deg_out_[ver_first]++;
    deg_in_[ver_second]++;
    std::pair<size_t, size_t> pair_ver = std::make_pair(ver_first, ver_second);
    if (edges_.find(pair_ver) != edges_.end()) {
      ++count_each_edge_[pair_ver];
    } else {
      adjacency_list_[ver_first].push_back(ver_second);
      edges_.insert(pair_ver);
      count_each_edge_[pair_ver] = 1;
    }
  }

  void DFS(size_t ver) {
    colors_[ver] = GREY;
    for (auto u : adjacency_list_[ver]) {
      if (colors_[u] == WHITE) {
        DFS(u);
      }
    }
    colors_[ver] = BLACK;
  }
};

int main() {
  size_t amount_of_bus_routes = 0;
  size_t amount_of_squares = 0;
  std::cin >> amount_of_bus_routes >> amount_of_squares;
  Graph graph(amount_of_squares);
  size_t count_ver = 0;
  size_t ver_first = 0;
  size_t ver_second = 0;
  for (size_t i = 0; i < amount_of_bus_routes; ++i) {
    std::cin >> count_ver;
    std::cin >> ver_first;
    --ver_first;
    for (size_t j = 0; j < count_ver; ++j) {
      std::cin >> ver_second;
      --ver_second;
      graph.InsertEdgeOrient(ver_first, ver_second);
      ver_first = ver_second;
    }
  }
  if (graph.IsEulerGraph()) {
    std::vector<size_t> euler_path = graph.EulerPath();
    std::cout << euler_path.size() << " ";
    for (auto &ver : euler_path) {
      std::cout << ver + 1 << " ";
    }
  } else {
    std::cout << 0;
  }
  return 0;
}