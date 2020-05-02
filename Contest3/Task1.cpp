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

struct Node {
  int number;
  int distance = MY_INT_MAX;

  Node(int number, int distance) : number(number), distance(distance) {}
};

class myComparator {
 public:
  int operator()(const Node &a, const Node &b) {
	return a.distance > b.distance;
  }
};

int minOstWeight(const Graph &graph,
				 std::priority_queue<Node, std::vector<Node>, myComparator> &queue,
				 std::vector<int> dist,
				 int n);

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph my_graph = Graph(n);
  std::priority_queue<Node, std::vector<Node>, myComparator> queue;
  std::vector<int> min_distances(n, MY_INT_MAX);
  min_distances[0] = 0;
  for (int i = 0; i < m; ++i) {
	int one, two, weight;
	std::cin >> one >> two >> weight;
	int from = std::min(--one, --two);
	int to = std::max(one, two);
	my_graph.add(from, to, weight);
	my_graph.add(to, from, weight);
	if (from == 0) {
	  min_distances[to] = std::min(min_distances[to], weight);
	}
  }
  for (int i = 1; i < n; ++i) {
	queue.emplace(Node(i, min_distances[i]));
  }
  std::cout << minOstWeight(my_graph, queue, min_distances, n);
}

int minOstWeight(const Graph &graph,
				 std::priority_queue<Node, std::vector<Node>, myComparator> &queue,
				 std::vector<int> dist,
				 int n) {
  int result = 0;
  std::vector<int> visited(n, 0);
  visited[0] = 1;
  while (!queue.empty()) {
	Node current = queue.top();
	queue.pop();
	if (current.distance == dist[current.number]) {
	  result += current.distance;
	  for (auto neighbor: graph.graph[current.number]) {
		int alternative = neighbor.second;
		if (!visited[neighbor.first] && alternative < dist[neighbor.first]) {
		  dist[neighbor.first] = alternative;
		  queue.push(Node(neighbor.first, alternative));
		}
	  }
	  visited[current.number] = 1;
	}
  }
  return result;
}
