#include <iostream>
#include <vector>

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		std::cin >> from >> to;
		graph[from].push_back(to);
	}

}