#include <iostream>
#include <vector>
#include <deque>

void bfs(std::vector<std::vector<int>> &graph, int start, std::vector<int> &distance);
int findMin(const std::vector<int>& disLeon, const std::vector<int>& disMatilda, const std::vector<int>& disMilk, int n);

void read(std::vector<std::vector<int>> &graph, int &n, int &m, int &leon, int &matilda, int &milk);
int solve(std::vector<std::vector<int>> &graph, const int& leon, const int& matilda, const int& milk);
void write(int result);

const int fMAX = 10e6;

int main() {
	int n, m;
	int leon, matilda, milk;
	std::vector<std::vector<int>> graph;
	int result = solve(graph, leon, matilda, milk);
	write(result);
}

void read(std::vector<std::vector<int>> &graph, int &n, int &m, int &leon, int &matilda, int &milk) {
	std::cin >> n >> m >> leon >> matilda >> milk;
	leon--;
	matilda--;
	milk--;
	graph = std::vector<std::vector<int>>(n);
	for (int i = 0; i < m; ++i) {
		int first, second;
		std::cin >> first >> second;
		first--;
		second--;
		graph[first].push_back(second);
		graph[second].push_back(first);
	}
}

int solve(std::vector<std::vector<int>> &graph, const int& leon, const int& matilda, const int& milk) {
	int n = graph.size();
	std::vector<int> disLeon(n), disMatilda(n), disMilk(n); // each holds distances for Leon, Matilda and Milk from i vertex
	for (int i = 0; i <  n; ++i) { // filling distances with 0
		disLeon[i] = fMAX;
		disMatilda[i] = fMAX;
		disMilk[i] = fMAX;
	}
	bfs(graph, leon, disLeon); // counting distances for Leon
	bfs(graph, matilda, disMatilda); // counting distances for Matilda
	bfs(graph, milk, disMilk); // counting distances for Milk
	return findMin(disLeon, disMatilda, disMilk, n);
}

void write(const int& result) {
	std::cout << result << std::endl;
}

void bfs(std::vector<std::vector<int>> &graph, int start, std::vector<int> &distance) {
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

