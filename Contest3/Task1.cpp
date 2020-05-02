#include <iostream>
#include <vector>

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> graph;

  Graph(int n) : graph(n) {}

  void add(int from, int to, int weight);
  void print();
  int size();

};

struct Node {
  int number;
  int distance = INT_MAX;

  Node(int number, int distance) : number(number), distance(distance) {}
};

class myComparator {
 public:
  int operator()(const Node &a, const Node &b) {
	return a.distance > b.distance;
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;

}
