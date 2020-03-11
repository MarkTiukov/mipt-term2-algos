#include <iostream>
#include <vector>

void findSCC(std::vector<std::vector<int>> &graph); // finds strongly connected components
void dfs1(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices);
void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph);
bool dfs2(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<std::vector<int>> &components, const int &numberOfCurrentCC);

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
			dfs1(graph, i, colors, vertices);
		}
	}
	std::vector<std::vector<int>> invertedGraph(graph.size());
	makeInvertedGraph(graph, invertedGraph);
	int ccWithOutEdges = 0;
	int ccWithInEdges = 0;
	colors = std::vector<int>(graph.size(), 0);
	std::vector<std::vector<int>> components;
	int numberOfCurrentCC = 0;
	for (int i : vertices)
		std::cout << i << std::endl;
	for (int i = 0; i < vertices.size(); ++i) {
		if (colors[i] == 0 && dfs2(invertedGraph, i, colors, components, numberOfCurrentCC)) {
			ccWithInEdges++;
		}
		numberOfCurrentCC++;
	}
	for (int i = 0; i < components.size(); ++i) {
		std::cout << "Component number " << i << ": ";
		for (int j = 0; j < components[i].size(); ++j) {
			std::cout << components[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool dfs2(std::vector<std::vector<int>> &graph,
				 int current,
				 std::vector<int> &colors,
				 std::vector<std::vector<int>> &components,
				 const int &numberOfCurrentCC) {
	bool resultForCurrent = false; // if true then this vertice has an in-edge
	colors[current] = 1;
	for (int i = 0; i < graph[current].size(); ++i) {
		int currentV = graph[current][i];
		if (colors[currentV] == 0)
			resultForCurrent = resultForCurrent || dfs2(graph, currentV, colors, components, numberOfCurrentCC);
		else {
			if (colors[currentV] == 2)
				resultForCurrent = true;
		}
	}
	colors[current] = 2;
	if (numberOfCurrentCC >= components.size()) {
		std::vector<int> toAdd;
		toAdd.push_back(current);
		components.push_back(toAdd);
	} else
		components[numberOfCurrentCC].push_back(current);
	return resultForCurrent;
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
