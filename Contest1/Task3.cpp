#include <iostream>
#include <vector>

void findSCC(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components); // finds strongly connected components
void dfs1(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<int> &vertices);
void makeInvertedGraph(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &invertedGraph);
void dfs2(std::vector<std::vector<int>> &graph, int current, std::vector<int> &colors, std::vector<std::vector<int>> &components, const int &numberOfCurrentCC, bool& result);
int countToAdd(std::vector<std::vector<int>> &graph);
void countOutGoingEdges(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components, std::vector<int> &colors);


int ccIn = 0; // number of cc with in-edges
int ccOut = 0; // number of c with out-edges
int maxColor = 2;

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
	std::cout << countToAdd(components) << std::endl;
}

int countToAdd(std::vector<std::vector<int>> &graph) {
	if (graph.size() > 1) {
		return std::max(ccIn, ccOut);
	}
	return 0;
}

void countOutGoingEdges(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &components, std::vector<int> &colors) {
	for (int i = 0; i < components.size(); ++i) {
		bool test = true;
		for (int j = 0; j < components[i].size(); ++j) {
			if (test) {
				for (int k = 0; k < graph[components[i][j]].size(); ++k) {
					if (test && colors[graph[components[i][j]][k]] != colors[components[i][0]]) {
						test = false;
					}
				}
			}
		}
		if (test)
			ccOut++;
	}
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
	colors = std::vector<int>(graph.size(), 0);
	int numberOfCurrentCC = 0;
	for (int i = vertices.size() - 1; i > -1; --i) {
		if (colors[vertices[i]] == 0) {
			bool result = true;
			dfs2(invertedGraph, vertices[i], colors, components, numberOfCurrentCC, result);
			if (result)
				ccIn++;
			numberOfCurrentCC++;
			maxColor++;
		}
	}
	countOutGoingEdges(graph, components, colors);
}

void dfs2(std::vector<std::vector<int>> &graph,
				 int current,
				 std::vector<int> &colors,
				 std::vector<std::vector<int>> &components,
				 const int &numberOfCurrentCC, bool& result) {
	colors[current] = 1;
	for (int i = 0; i < graph[current].size(); ++i) {
		int currentV = graph[current][i];
		if (colors[currentV] > 1 && colors[currentV] != maxColor) {
			result = false;
		}
		if (colors[currentV] == 0) {
			dfs2(graph, currentV, colors, components, numberOfCurrentCC, result);
		}
	}
	colors[current] = maxColor;
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
