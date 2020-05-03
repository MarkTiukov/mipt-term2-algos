#include <iostream>
#include <vector>
#include <queue>

const int MY_INT_MAX = 2147483647;

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> graph;

  Graph(int n) : graph(n) {}

  void add(int from, int to, int weight) {
	if (to != -1)
	  this->graph[from].push_back(std::make_pair(to, weight));
  }

  void print() {
	for (int from = 0; from < this->graph.size(); ++from) {
	  for (std::pair<int, int> pair: this->graph[from]) {
		std::cout << "from " << from << " to " << pair.first << " with weight " << pair.second << std::endl;
	  }
	}
  }

  int size() const { return this->graph.size(); }

};

struct Edge {
  int start, end;
  int weight;

  Edge() = default;
  Edge(int start, int an_end, int weight) : start(start), end(an_end), weight(weight) {}
};

class MyComparator {
 public:
  int operator()(const Edge &a, const Edge &b) {
	return a.weight < b.weight;
  }
};

int minOstWeight(const Graph &graph, int n);

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph my_graph = Graph(n);
  std::vector<Edge> edges = std::vector<Edge>();
  for (int i = 0; i < m; ++i) {
	int from, to, weight;
	std::cin >> from >> to >> weight;
	edges.push_back(Edge(--from, --to, weight));
	my_graph.add(from, to, weight);
	my_graph.add(to, from, weight);
  }
  std::sort(edges.begin(), edges.end(), MyComparator());
  for (auto edge: edges) {
	std::cout << edge.start << " " << edge.end << " " << edge.weight << std::endl;
  }
  //std::cout << minOstWeight(my_graph, n);
}

int minOstWeight(const Graph &graph, int n) {
  int result = 0;
  return result;
}