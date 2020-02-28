#include <iostream>
#include <vector>

void findSCC(std::vector<std::vector<int>> &graph); // finds strongly connected components
void dfs(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices);
void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph);

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph = std::vector<std::vector<int>>(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		std::cin >> from >> to;
		graph[--from].push_back(--to);
	}
	findSCC(graph);
}

void findSCC(std::vector<std::vector<int>> &graph) {
	std::vector<int> outTime = std::vector<int>(graph.size());
	std::vector<int> vertices; // stores vertices sorted by time of exiting'em
	std::vector<int> colors(graph.size(), 0); // 0 = white; 1 = gray; 2 = black;
	int time = 0;
	for (int i = 0; i < graph.size(); ++i) {
		if (colors[i] == 0){
			dfs(graph, i, colors, vertices);
		}
	}
	std::vector<std::vector<int>> invertedGraph(graph.size());
	makeInvertedGraph(graph, invertedGraph);
	for (int i = 0; i < graph.size(); ++i) {
		for (int j : invertedGraph[i]) {
			std::cout << i << " ---> " << j << std::endl;
		}
	}
}

void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph) {
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph[i].size(); ++j) {
			invertedGraph[graph[i][j]].push_back(i);
		}
	}
}

void dfs(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices) {
	colors[current] = 1;
	for (int i = 0; i < graph[current].size(); ++i) {
		int currentV = graph[current][i];
		if (colors[currentV] == 0)
			 dfs(graph, currentV, colors, vertices);
	}
	colors[current] = 2;
	vertices.push_back(current);
}


