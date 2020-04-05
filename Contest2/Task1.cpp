#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int costA, costB;
int M;
int start, finish;
const int MAX_VALUE = 2e9;

struct Graph {
	std::vector<std::vector<std::pair<int, int>>> graph;

	Graph(int n) : graph(n) {}

	void add(int from, int to, int weight);
	void print();
	int size();

};

struct Node {
	int number;
	int distance = MAX_VALUE;

	Node(int number, int distance) : number(number), distance(distance) {}
};

class myComparator {
 public:
	int operator()(const Node &a, const Node &b) {
		return a.distance > b.distance;
	}
};

void createGraph(Graph &graph);
void dijkstra(Graph &graph, std::vector<int> &dist);

int main() {
	std::cin >> costA >> costB >> M >> start >> finish;
	Graph graph(M);
	createGraph(graph);
	std::vector<int> dist(M, MAX_VALUE);
	dist[start] = 0;
	dijkstra(graph, dist);
	std::cout << dist[finish] << std::endl;
}

void createGraph(Graph &graph) {
	for (long long i = 0; i < M; ++i) {
		long long next1 = (i + 1) % M;
		long long next2 = (i * i + 1) % M;
		if (next1 == next2) {
			graph.add(i, next1, std::min(costA, costB));
		} else {
			graph.add(i, next1 == i ? -1 : next1, costA);
			graph.add(i, next2 == i ? -1 : next2, costB);
		}
	}
}

void Graph::add(int from, int to, int weight) {
	if (to != -1)
		this->graph[from].push_back(std::make_pair(to, weight));
}

void Graph::print() {
	for (int from = 0; from < M; ++from) {
		for (std::pair<int, int> pair: this->graph[from]) {
			std::cout << "from " << from << " to " << pair.first << " with weight " << pair.second << std::endl;
		}
	}
}

int Graph::size() {
	return this->graph.size();
}

void dijkstra(Graph &graph, std::vector<int> &dist) {
	std::priority_queue<Node, std::vector<Node>, myComparator> queue;
	std::vector<bool> used(graph.size(), false);
	queue.emplace(Node(start, 0));
	while (queue.size() > 0) {
		Node current = queue.top();
		queue.pop();
		if (current.distance == dist[current.number]) {
			for (auto neighbor: graph.graph[current.number]) {
				int alternative = dist[current.number] + neighbor.second;
				if (alternative < dist[neighbor.first]) {
					dist[neighbor.first] = alternative;
					queue.push(Node(neighbor.first, alternative));
				}
			}
		}
	}
}
