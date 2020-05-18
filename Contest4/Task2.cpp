#include <iostream>
#include <vector>

const int MY_INT_MIN = 0;

void buildTree(std::vector<std::pair<int, int>> &tree,
			   const std::vector<int> &numbers,
			   int current_node,
			   int tree_start,
			   int tree_end) {
  if (tree_start == tree_end) {
	tree.at(current_node) = std::make_pair(numbers.at(tree_start), numbers.at(tree_start));
  } else {
	int median = (tree_start + tree_end) / 2;
	buildTree(tree, numbers, current_node * 2, tree_start, median);
	buildTree(tree, numbers, current_node * 2 + 1, median + 1, tree_end);
	tree.at(current_node).second = std::max(tree.at(current_node * 2).second, tree.at(current_node * 2 + 1).second);
  }
}

void update(std::vector<std::pair<int, int>> &tree,
			int current_node,
			int tree_start,
			int tree_end,
			int left,
			int right,
			int add) {
  if (left <= right) {
	if (left == tree_start && tree_end == right) {
	  tree.at(current_node).first += add;
	  tree.at(current_node).second += add;
	} else {
	  int median = (tree_start + tree_end) / 2;
	  update(tree, current_node * 2, tree_start, median, left, std::min(right, median), add);
	  update(tree, current_node * 2 + 1, median + 1, tree_end, std::max(left, median + 1), right, add);
	  tree.at(current_node).second = std::max(tree.at(current_node * 2).second, tree.at(current_node * 2 + 1).second) + tree.at(current_node).first;
	}
  }
}

int getMax(std::vector<std::pair<int, int>> &tree,
				 int current_node,
				 int tree_start,
				 int tree_end,
				 int left,
				 int right) {
  if (left > right) {
	return MY_INT_MIN;
  }
  if (left == tree_start && right == tree_end) {
	return tree.at(current_node).second;
  }
  int median = (tree_start + tree_end) / 2;
  return std::max(getMax(tree, current_node * 2, tree_start, median, left, std::min(right, median)),
				  getMax(tree, current_node * 2 + 1, median + 1, tree_end, std::max(left, median + 1), right)) + tree.at(current_node).first;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> numbers = std::vector<int>(n - 1, 0);
  for (int i = 0; i < n - 1; ++i) {
	std::cin >> numbers.at(i);
  }
  std::vector<std::pair<int, int>> tree = std::vector<std::pair<int, int>>(4 * n, std::make_pair(0, 0));
  // first -- to add; second -- maximum

  buildTree(tree, numbers, 1, 0, n - 2);
  int capacity, m;
  std::cin >> capacity >> m;
  for (int i = 0; i < m; ++i) {
	int start, end, number_of_tickets;
	std::cin >> start >> end >> number_of_tickets;
	int cur_max = getMax(tree, 1, 0, n - 2, start, --end);
	if (cur_max + number_of_tickets <= capacity) {
	  update(tree, 1, 0, n - 2, start, end, number_of_tickets);
	} else {
	  std::cout << i << " ";
	}
  }
  std::cout << std::endl;
}
