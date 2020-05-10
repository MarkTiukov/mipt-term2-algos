#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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

int minOstWeight(const std::vector<Edge> &sorted_edges, int n);
bool makesCycle(std::vector<int> &trees, const Edge &edge);

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
  std::cout << minOstWeight(edges, n);
}

int minOstWeight(const std::vector<Edge> &sorted_edges, int n) {
  int result = 0;
  std::vector<int> trees = std::vector<int>(n);
  for (int i = 0; i < n; ++i) {
	trees[i] = i;
  }
  for (int i = 0, counter = 0; counter < n - 1; ++i, ++counter) {
	if (!makesCycle(trees, sorted_edges[i])) {
	  result += sorted_edges[i].weight;
	  int change_from = trees[sorted_edges[i].start];
	  int change_to = trees[sorted_edges[i].end];
	  for (int vertex = 0; vertex < n; ++vertex) {
		if (trees[vertex] == change_from)
		  trees[vertex] = change_to;
	  }
	} else {
	  --counter;
	}
  }
  return result;
}

bool makesCycle(std::vector<int> &trees, const Edge &edge) {
  return trees[edge.start] == trees[edge.end];
}

