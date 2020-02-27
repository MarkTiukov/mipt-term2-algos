#include <iostream>
#include <vector>

bool checkForCycles(std::vector<std::vector<int>> &graph, int n);
bool checkForCycles(std::vector<std::vector<int>> &graph, int n, int vertex, std::vector<int> &colors);

void read(int &n, int &m, std::vector<std::vector<int>> &graph);
void solve();

std::vector<int>  answer;

int main() {
	int n, m;
	std::vector<std::vector<int>> graph;
	read(n, m, graph);
	if (!checkForCycles(graph, n)) {
		std::cout << "YES" << std::endl;
		for (int i = 0; i < n; ++i) {
			std::cout << answer[n - i - 1] << " ";
		}
		std::cout << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
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

bool checkForCycles(std::vector<std::vector<int>> &graph, int n) {
	std::vector<int> colors(n); // 0 for "white"; 1 for "gray"; 2 for "black"
	for (int i = 0; i < n; ++i) {
		colors[i] = 0;
	}
	bool result = false;
	for (int i = 0; !result && i < n; ++i) {
		if (colors[i] ==  0) {
			result = checkForCycles(graph, n, i, colors);
		}
	}
	return result;
}

bool checkForCycles(std::vector<std::vector<int>> &graph, int n, int vertex, std::vector<int> &colors) {
	colors[vertex] = 1;
	bool result = false;
	for (int i = 0; !result && i < graph[vertex].size(); ++i) {
		int currentV = graph[vertex][i];
		if (colors[currentV] == 1) {
			result = true;
			break;
		}
		if (colors[currentV] == 0)
			result = checkForCycles(graph, n, currentV, colors);
	}
	colors[vertex] = 2;
	answer.push_back(vertex);
	return result;
}
