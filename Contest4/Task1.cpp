#include <iostream>
#include <vector>

std::vector<int> logarithms;

struct SparseTable {

  std::vector<std::vector<int>> table;

  SparseTable(int n, const std::vector<int> &numbers) {
	this->table = std::vector<std::vector<int>>(n);
	for (int i = 0; i < n; ++i) {
	  this->table[i] = std::vector<int>(logarithms[n] + 1);
	}
	/////////////////////////////
	for (int i = 0; i < n; i++)
	  this->table[i][0] = i;
	for (int j = 0; j + 1 <= logarithms[n]; j++) {
	  for (int i = 0; i < n; i++) {
		if (i + (1 << (j + 1)) > n)
		  break;
		this->table[i][j + 1] =
			numbers[this->table[i][j]] < numbers[this->table[i + (1 << j)][j]] ? this->table[i][j] : this->table[i
				+ (1 << j)][j];
	  }
	}
  }

  void print() const {
	for (auto line: this->table) {
	  for (auto column: line) {
		std::cout << column << "  ";
	  }
	  std::cout << std::endl;
	}
  }

};

int getMin(const SparseTable &data, const std::vector<int> &numbers, const int &start, const int &end) {
  int j = logarithms[end - start + 1];
  return std::min(numbers[data.table[start][j]], numbers[data.table[end - (1 << j) + 1][j]]);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> numbers = std::vector<int>(n);
  logarithms = std::vector<int>(n + 1);
  for (int i = 2; i <= n; i++) {
	logarithms[i] = logarithms[i >> 1] + 1;
  }
  for (int i = 0; i < n; ++i) {
	std::cin >> numbers[i];
  }
  SparseTable data = SparseTable(n, numbers);
  for (int i = 0; i < m; ++i) {
	int start, end;
	std::cin >> start >> end;
	std::cout << getMin(data, numbers, start - 1, end - 1) << std::endl;
  }
}
