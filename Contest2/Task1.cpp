#include <iostream>
#include <vector>

int costA, costB;
int M;
int start, finish;

struct Graph {
	std::vector<std::vector<std::pair<int, int>>> graph;

	Graph(int n) : graph(n) {}

	void add(int from, int to, int weight);
	void print();

};

void createGraph(Graph &graph);

int main() {
	std::cin >> costA >> costB >> M >> start >> finish;
	Graph graph(M);
	createGraph(graph);
	graph.print();
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
