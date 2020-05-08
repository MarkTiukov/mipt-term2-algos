#include <iostream>
#include <vector>

int main() {
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;
  std::vector<std::vector<int>> graph;
  int numberA = 0;
  int numberB = 0;
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
  if (a > 2 * b) {
	std::cout << number << std::endl;
	return 0;
  }
  for (int i = 0; i < n; ++i) {
	for (int j = 0; j < m; ++j) {
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
		if (j != n - 1 && table[i][j + 1] == '*') {
		  graph[graph.size() - 1].push_back(m * i + (j + 1));
		}
	  }
	}
  }
}