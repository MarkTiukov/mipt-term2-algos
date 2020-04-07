
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

int start, finish;
const double MAX_VALUE = -2e9;

struct Graph {
	std::vector<std::vector<std::pair<int, double>>> graph;

	Graph() { this->graph = std::vector<std::vector<std::pair<int, double>>>(); }
	Graph(int n) : graph(n) {}

	void add(int from, int to, double weight);
	void print();
	int size();

};

struct Node {
	int number;
	double distance = MAX_VALUE;

	Node(int number, double distance) : number(number), distance(distance) {}
};

class myComparator {
 public:
	int operator()(const Node &a, const Node &b) {
		return a.distance < b.distance;
	}
};

void dijkstra(Graph &graph, std::vector<double> &dist);

int main() {
	int n, m;
	std::cin >> n >> m >> start >> finish;
	start--;
	finish--;
	Graph graph(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		double cost;
		std::cin >> from >> to >> cost;
		cost = 1.0 - cost / 100.0;
		--from;
		--to;
		graph.add(from, to, cost);
		graph.add(to, from, cost);
	}
	std::vector<double> dist(n, MAX_VALUE);
	dist[start] = 1;
	dijkstra(graph, dist);
	std::cout << std::setprecision(6) << 1 - dist[finish] << std::endl;
}

void Graph::add(int from, int to, double weight) {
	if (to != -1)
		this->graph[from].push_back(std::make_pair(to, weight));
}

void Graph::print() {
	for (int from = 0; from < this->graph.size(); ++from) {
		for (auto pair: this->graph[from]) {
			std::cout << "from " << from << " to " << pair.first << " with weight " << pair.second << std::endl;
		}
	}
}

int Graph::size() {
	return this->graph.size();
}

void dijkstra(Graph &graph, std::vector<double> &dist) {
	std::priority_queue<Node, std::vector<Node>, myComparator> queue;
	queue.emplace(Node(start, 1));
	while (queue.size() > 0) {
		Node current = queue.top();
		queue.pop();
		if (current.distance == dist[current.number]) {
			for (auto neighbor: graph.graph[current.number]) {
				double alternative = dist[current.number] * neighbor.second;
				if (alternative > dist[neighbor.first]) {
					dist[neighbor.first] = alternative;
					queue.push(Node(neighbor.first, alternative));
				}
			}
		}
	}
}