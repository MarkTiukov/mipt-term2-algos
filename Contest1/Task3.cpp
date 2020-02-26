#include <iostream>
#include <vector>

struct Graph {
	std::vector<std::vector<int>> graph;
	int numberOfVertices = 0;

	Graph(int n) {
		this->numberOfVertices = n;
		graph = std::vector<std::vector<int>>(n);
	}

	void add(int from, int to) {
		this->graph[from].push_back(to);
	}

};

void findSCC(std::vector<std::vector<int>> &graph, int n); // find strongly connected components

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph graph = Graph(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		std::cin >> from >> to;
		graph.add(from, to);
	}
	
}

void findSCC(std::vector<std::vector<int>> &graph, int n) {
	
}
