#include <iostream>
#include <vector>

const int MY_INT_MAX = 2147483647;

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
  int result = 0;
  if (start == end) {
	result = start;
  } else {
	if (start > end) {
	  result = numbers.size() - 1;
	} else {
	  int j = logarithms[end - start + 1];
	  result = numbers[data.table[start][j]] < numbers[data.table[end - (1 << j) + 1][j]] ? data.table[start][j] : data.table[end - (1 << j) + 1][j];
	}
  }
  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> numbers = std::vector<int>(n + 1);
  logarithms = std::vector<int>(n + 1);
  for (int i = 2; i <= n; i++) {
	logarithms[i] = logarithms[i >> 1] + 1;
  }
  for (int i = 0; i < n; ++i) {
	std::cin >> numbers[i];
  }
  numbers[n] = MY_INT_MAX;
  SparseTable data = SparseTable(n, numbers);
  for (int i = 0; i < m; ++i) {
	int start, end;
	std::cin >> start >> end;
	int min_position = getMin(data, numbers, --start, --end);
	int min_position_left_side = getMin(data, numbers, start, min_position - 1);
	int min_position_right_side = getMin(data, numbers, min_position + 1, end);
	std::cout << std::min(numbers[min_position_left_side], numbers[min_position_right_side]) << std::endl;
  }
}
