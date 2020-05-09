#include <iostream>
#include <vector>

bool dfs(std::vector<std::vector<int>> &graph,
		 std::vector<int> &current_matching,
		 std::vector<int> &visited,
		 int current_vertex) {
  if (visited[current_vertex] == 0) {
	visited[current_vertex] = 1;
	for (auto next: graph[current_vertex]) {
	  if (current_matching[next / 2] == -1 || dfs(graph, current_matching, visited, current_matching[next / 2])) {
	    current_matching[next / 2] = current_vertex;
		return true;
	  }
	}
  }
  return false;
}

bool dfs(std::vector<std::vector<int>> &graph, std::vector<int> &current_matching, int start) {
  std::vector<int> visited(graph.size(), 0);
  return dfs(graph, current_matching, visited, start);
}

int maxDominoes(std::vector<std::vector<int>> &graph, int n, int m) {
  std::vector<int> current_matching = std::vector<int>(n * m / 2, -1);
  int result = 0;
  for (int i = 0; i < graph.size(); ++i) {
	if (dfs(graph, current_matching, i)) {
	  result += 1;
	}
  }
  return result;
}

int main() {
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;
  std::vector<std::vector<int>> graph;
  std::vector<std::vector<char>> table = std::vector<std::vector<char>>(n);
  int number = 0;
  for (int i = 0; i < n; ++i) {
	std::string line;
	std::cin >> line;
	table[i] = std::vector<char>(m);
	for (int j = 0; j < m; ++j) {
	  table[i][j] = line[j];
	  if (line[j] == '*') {
		++number;
	  }
	}
  }
  if (a >= 2 * b) {
	std::cout << number * b << std::endl;
	return 0;
  }
  for (long i = 0; i < n; ++i) {
	for (long j = 0; j < m; ++j) {
	  if (table[i][j] == '*' && (i + j) % 2 == 0) {
		graph.push_back(std::vector<int>());
		if (i != 0 && table[i - 1][j] == '*') {
		  graph[graph.size() - 1].push_back(m * (i - 1) + j);
		}
		if (j != 0 && table[i][j - 1] == '*') {
		  graph[graph.size() - 1].push_back(m * i + (j - 1));
		}
		if (i != n - 1 && table[i + 1][j] == '*') {
		  graph[graph.size() - 1].push_back(m * (i + 1) + j);
		}
		if (j != m - 1 && table[i][j + 1] == '*') {
		  graph[graph.size() - 1].push_back(m * i + (j + 1));
		}
	  }
	}
  }
  int dominoes = maxDominoes(graph, n, m);
  std::cout << (dominoes * a + (number - dominoes * 2) * b) << std::endl;
}