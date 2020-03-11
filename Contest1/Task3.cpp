#include <iostream>
#include <vector>

void findSCC(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components); // finds strongly connected components
void dfs1(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices);
void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph);
void dfs2(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<std::vector<int>> &components, const int &numberOfCurrentCC);
int countToAdd(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components);

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph = std::vector<std::vector<int>>(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		std::cin >> from >> to;
		graph[--from].push_back(--to);
	}
	std::vector<std::vector<int>> components;
	findSCC(graph, components);

}

int countToAdd(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components) {

}

void findSCC(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components) {
	std::vector<int> outTime = std::vector<int>(graph.size());
	std::vector<int> vertices; // stores vertices sorted by time of exiting'em®
	std::vector<int> colors(graph.size(), 0); // 0 = white; 1 = gray; 2 = black;
	int time = 0;
	for (int i = 0; i < graph.size(); ++i) {
		if (colors[i] == 0){
			dfs1(graph, i, colors, vertices);
		}
	}
	std::vector<std::vector<int>> invertedGraph(graph.size());
	makeInvertedGraph(graph, invertedGraph);
	/*
	std::cout << "INVERTED GRAPH:" << std::endl;
	for (int i = 0; i < invertedGraph.size(); ++i) {
		for (int j : invertedGraph[i]) {
			std::cout << i << " " << j << std::endl;
		}
	}
	std::cout << "/////////////////////////" << std::endl;
	 */
	colors = std::vector<int>(graph.size(), 0);
	int numberOfCurrentCC = 0;
	// checking vertices
	/*
	for (int i : vertices)
	std::cout << i << std::endl;
	*/
	for (int i = vertices.size() - 1; i > -1; --i) {
		if (colors[vertices[i]] == 0) {
			dfs2(invertedGraph, vertices[i], colors, components, numberOfCurrentCC);
			numberOfCurrentCC++;
		}
	}
	// printing components
	/*
	for (int i = 0; i < components.size(); ++i) {
		std::cout << "Component number " << i << ": ";
		for (int j = 0; j < components[i].size(); ++j) {
			std::cout << components[i][j] << " ";
		}
		std::cout << std::endl;
	}
	*/
}

void dfs2(std::vector<std::vector<int>> &graph,
				 int current,
				 std::vector<int> &colors,
				 std::vector<std::vector<int>> &components,
				 const int &numberOfCurrentCC) {
	colors[current] = 1;
	for (int i = 0; i < graph[current].size(); ++i) {
		int currentV = graph[current][i];
		if (colors[currentV] == 0)
			dfs2(graph, currentV, colors, components, numberOfCurrentCC);
	}
	colors[current] = 2;
	if (numberOfCurrentCC >= components.size()) {
		std::vector<int> toAdd;
		toAdd.push_back(current);
		components.push_back(toAdd);
	} else
		components[numberOfCurrentCC].push_back(current);
}

void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph) {
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph[i].size(); ++j) {
			invertedGraph[graph[i][j]].push_back(i);
		}
	}
}

void dfs1(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices) {
	colors[current] = 1;
	for (int i = 0; i < graph[current].size(); ++i) {
		int currentV = graph[current][i];
		if (colors[currentV] == 0)
			 dfs1(graph, currentV, colors, vertices);
	}
	colors[current] = 2;
	vertices.push_back(current);
}
