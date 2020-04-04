#include <iostream>
#include <vector>

bool checkForCycles(std::vector<std::vector<int>> &graph);
bool checkForCycles(std::vector<std::vector<int>> &graph, int vertex, std::vector<int> &colors);

void read(int &n, int &m, std::vector<std::vector<int>> &graph);
void solve(std::vector<std::vector<int>> &graph);

std::vector<int>  answer;

int main() {
	int n, m;
	std::vector<std::vector<int>> graph;
	read(n, m, graph);
	solve(graph);
}

void read(int &n, int &m, std::vector<std::vector<int>> &graph) {
	std::cin >> n >> m;
	graph = std::vector<std::vector<int>>(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		std::cin >> from >> to;
		graph[from].push_back(to);
	}
}

void solve(std::vector<std::vector<int>> &graph) {
	if (!checkForCycles(graph)) {
		std::cout << "YES" << std::endl;
		for (int i = 0; i < graph.size(); ++i) {
			std::cout << answer[graph.size() - i - 1] << " ";
		}
		std::cout << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
}

bool checkForCycles(std::vector<std::vector<int>> &graph) {
	int n = graph.size();
	std::vector<int> colors(n); // 0 for "white"; 1 for "gray"; 2 for "black"
	for (int i = 0; i < n; ++i) {
		colors[i] = 0;
	}
	bool result = false;
	for (int i = 0; !result && i < n; ++i) {
		if (colors[i] ==  0) {
			result = checkForCycles(graph, i, colors);
		}
	}
	return result;
}

bool checkForCycles(std::vector<std::vector<int>> &graph, int vertex, std::vector<int> &colors) {
	colors[vertex] = 1;
	bool result = false;
	for (int i = 0; !result && i < graph[vertex].size(); ++i) {
		int currentV = graph[vertex][i];
		if (colors[currentV] == 1) {
			result = true;
			break;
		}
		if (colors[currentV] == 0)
			result = checkForCycles(graph, currentV, colors);
	}
	colors[vertex] = 2;
	answer.push_back(vertex);
	return result;
}
