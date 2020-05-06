#include <iostream>
#include <vector>
#include <queue>

const long long MY_LONG_MAX = 9e18;

struct Graph {
  std::vector<std::vector<std::pair<int, long long>>> graph;

  Graph(long long n) : graph(n) {}

  void add(long long from, long long to, long long weight) {
	if (to != -1)
	  this->graph[from].push_back(std::make_pair(to, weight));
  }

  void print() {
	for (int from = 0; from < this->graph.size(); ++from) {
	  for (std::pair<long long, long long> pair: this->graph[from]) {
		std::cout << "from " << from << " to " << pair.first << " with weight " << pair.second << std::endl;
	  }
	}
  }

  long long size() const { return this->graph.size(); }

};

struct Node {
  long long number;
  long long distance = MY_LONG_MAX;

  Node(long long number, long long distance) : number(number), distance(distance) {}
};

class myComparator {
 public:
  int operator()(const Node &a, const Node &b) {
	return a.distance > b.distance;
  }
};

int minOstWeight(const Graph &graph,
				 std::priority_queue<Node, std::vector<Node>, myComparator> &queue,
				 std::vector<long long> dist,
				 long long n);

int main() {
  long long n, m;
  std::cin >> n >> m;
  Graph my_graph = Graph(n);
  std::priority_queue<Node, std::vector<Node>, myComparator> queue;
  std::vector<long long> min_distances(n, MY_LONG_MAX);
  min_distances[0] = 0;
  std::vector<long long> a = std::vector<long long>(n);
  for (long long i = 0; i < n; ++i) {
	std::cin >> a[i];
  }
  int min = 0;
  for (long long i = 0; i < n; ++i) {
	if (a[i] < a[min]) {
	  min = i;
	}
  }
  for (long long i = 0; i < n; ++i) {
	if (i != min) {
	  my_graph.add(min, i, a[min] + a[i]);
	  my_graph.add(i, min, a[min] + a[i]);
	  if (min == 0) {
		min_distances[i] = std::min(min_distances[i], a[min] + a[i]);
	  }
	} else {
	  my_graph.add(min, min, MY_LONG_MAX);
	}
  }
  min_distances[min] = std::min(min_distances[min], a[0] + a[min]);
  for (long long i = 0; i < m; ++i) {
	long long one, two;
	long long weight;
	std::cin >> one >> two >> weight;
	long long from = std::min(--one, --two);
	long long to = std::max(one, two);
	if (from == min || to == min) {
	  my_graph.graph[min][(from == min ? to : from)].second =
		  std::min(my_graph.graph[min][(from == min ? to : from)].second, weight);
	  my_graph.graph[(from == min ? to : from)][0].second =
		  std::min(my_graph.graph[(from == min ? to : from)][0].second, weight);
	} else {
	  my_graph.add(from, to, std::min(weight, a[from] + a[to]));
	  my_graph.add(to, from, std::min(weight, a[from] + a[to]));
	}
	if (from == 0) {
	  min_distances[to] = std::min(min_distances[to], std::min(weight, a[from] + a[to]));
	}
  }
  for (int i = 1; i < n; ++i) {
	queue.emplace(Node(i, min_distances[i]));
  }
  std::cout << minOstWeight(my_graph, queue, min_distances, n);
}

int minOstWeight(const Graph &graph,
				 std::priority_queue<Node, std::vector<Node>, myComparator> &queue,
				 std::vector<long long> dist,
				 long long n) {
  long long result = 0;
  std::vector<long long> visited(n, 0);
  visited[0] = 1;
  while (!queue.empty()) {
	Node current = queue.top();
	queue.pop();
	if (current.distance == dist[current.number]) {
	  result += current.distance;
	  for (auto neighbor: graph.graph[current.number]) {
		long long alternative = neighbor.second;
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

