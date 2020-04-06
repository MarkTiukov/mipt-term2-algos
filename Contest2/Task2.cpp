#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int costA, costB;
int start, finish;
int k;
const int MAX_VALUE = 2e9;

struct Graph {
	std::vector<std::vector<std::pair<int, int>>> graph;

	Graph() { this->graph = std::vector<std::vector<std::pair<int, int>>>(); }
	Graph(int n) : graph(n) {}

	void add(int from, int to, int weight);
	void print();
	int size();

};

struct Node {
	int number;
	int distance = MAX_VALUE;
	int numberOfSteps = 0;

	Node(int number, int distance) : number(number), distance(distance) {}
	Node(int number, int distance, int number_of_steps)
			: number(number), distance(distance), numberOfSteps(number_of_steps) {}

};

class myComparator {
 public:
	int operator()(const Node &a, const Node &b) {
		return a.distance > b.distance;
	}
};

void dijkstra(Graph &graph, std::vector<int> &dist);

int main() {
	int n, m;
	std::cin >> n >> m >> k >> start >> finish;
	start--;
	finish--;
	Graph graph(n);
	for (int i = 0; i < m; ++i) {
		int from, to, cost;
		std::cin >> from >> to >> cost;
		graph.add(--from, --to, cost);
	}
	// graph.print();
	std::vector<int> dist(n, MAX_VALUE);
	dist[start] = 0;
	dijkstra(graph, dist);
	std::cout << (dist[finish] == MAX_VALUE ? -1 : dist[finish]) << std::endl;
}

void Graph::add(int from, int to, int weight) {
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

void dijkstra(Graph &graph, std::vector<int> &dist) {
	std::priority_queue<Node, std::vector<Node>, myComparator> queue;
	std::vector<bool> used(graph.size(), false);
	queue.emplace(Node(start, 0));
	while (queue.size() > 0) {
		Node current = queue.top();
		queue.pop();
		if (current.distance == dist[current.number] && current.numberOfSteps < k) {
			for (auto neighbor: graph.graph[current.number]) {
				int alternative = dist[current.number] + neighbor.second;
				if (alternative < dist[neighbor.first]) {
					dist[neighbor.first] = alternative;
					queue.push(Node(neighbor.first, alternative, current.numberOfSteps + 1));
				}
			}
		}
	}
}

