#include <iostream>
#include <vector>
#include <deque>

void bfs(std::vector<std::vector<int>> &graph, int n, int start, std::vector<int> &distance);
int findMin(const std::vector<int>& disLeon, const std::vector<int>& disMatilda, const std::vector<int>& disMilk, int n);

const int fMAX = 10e6;

int main() {
	int n, m;
	int leon, matilda, milk;
	std::cin >> n >> m >> leon >> matilda >> milk;
	leon--;
	matilda--;
	milk--;
	std::vector<std::vector<int>> graph(n);
	for (int i = 0; i < m; ++i) {
		int first, second;
		std::cin >> first >> second;
		first--;
		second--;
		graph[first].push_back(second);
		graph[second].push_back(first);
	}
	std::vector<int> disLeon(n), disMatilda(n), disMilk(n); // each holds distances for Leon, Matilda and Milk from i vertex
	for (int i = 0; i <  n; ++i) { // filling distances with 0
		disLeon[i] = fMAX;
		disMatilda[i] = fMAX;
		disMilk[i] = fMAX;
	}
	bfs(graph, n, leon, disLeon); // counting distances for Leon
	bfs(graph, n, matilda, disMatilda); // counting distances for Matilda
	bfs(graph, n, milk, disMilk); // counting distances for Milk
	std::cout << findMin(disLeon, disMatilda, disMilk, n) << std::endl;
}

void bfs(std::vector<std::vector<int>> &graph, int n, int start, std::vector<int> &distance) {
	std::deque<int> goingNext;
	goingNext.push_back(start);
	distance[start] = 0;
	while (!goingNext.empty()) {
		int current = goingNext.front();
		goingNext.pop_front();
		for (int i = 0; i < graph[current].size(); ++i) {
			if (graph[current][i] != start && distance[graph[current][i]] == fMAX) {
				distance[graph[current][i]] = distance[current] + 1;
				goingNext.push_back(graph[current][i]);
			}
		}
	}
}

int findMin(const std::vector<int> &disLeon,
						const std::vector<int> &disMatilda,
						const std::vector<int> &disMilk,
						int n) {
	int currentMin = 10e5;
	for (int i = 0; i < n; ++i){
		if (disLeon[i] + disMatilda[i] + disMilk[i] < currentMin)
			currentMin = disLeon[i] + disMatilda[i] + disMilk[i];
	}
	return currentMin;
}

