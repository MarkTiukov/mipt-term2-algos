#include <iostream>
#include <vector>

const long long MY_long_long_MIN = 0;

void buildTree(std::vector<std::pair<long long, long long>> &tree,
			   const std::vector<long long> &numbers,
			   long long current_node,
			   long long tree_start,
			   long long tree_end) {
  if (tree_start == tree_end) {
	tree.at(current_node) = std::make_pair(numbers.at(tree_start), numbers.at(tree_start));
  } else {
	long long median = (tree_start + tree_end) / 2;
	buildTree(tree, numbers, current_node * 2, tree_start, median);
	buildTree(tree, numbers, current_node * 2 + 1, median + 1, tree_end);
	tree.at(current_node).second = std::max(tree.at(current_node * 2).second, tree.at(current_node * 2 + 1).second);
  }
}

void update(std::vector<std::pair<long long, long long>> &tree,
			long long current_node,
			long long tree_start,
			long long tree_end,
			long long left,
			long long right,
			long long add) {
  if (left <= right) {
	if (left == tree_start && tree_end == right) {
	  tree.at(current_node).first += add;
	  tree.at(current_node).second += add;
	  // t.at(current_node).second = std::max(t.at(current_node * 2).second, t.at(current_node * 2 + 1).second) + t.at(current_node).first;
	} else {
	  long long median = (tree_start + tree_end) / 2;
	  update(tree, current_node * 2, tree_start, median, left, std::min(right, median), add);
	  update(tree, current_node * 2 + 1, median + 1, tree_end, std::max(left, median + 1), right, add);
	  tree.at(current_node).second = std::max(tree.at(current_node * 2).second, tree.at(current_node * 2 + 1).second) + tree.at(current_node).first;
	}
  }
}

long long getMax(std::vector<std::pair<long long, long long>> &tree,
				 long long current_node,
				 long long tree_start,
				 long long tree_end,
				 long long left,
				 long long right) {
  if (left > right) {
	return MY_long_long_MIN;
  }
  if (left == tree_start && right == tree_end) {
	return tree.at(current_node).second;
  }
  long long median = (tree_start + tree_end) / 2;
  return std::max(getMax(tree, current_node * 2, tree_start, median, left, std::min(right, median)),
				  getMax(tree, current_node * 2 + 1, median + 1, tree_end, std::max(left, median + 1), right)) + tree.at(current_node).first;
}

int main() {
  long long n;
  std::cin >> n;
  std::vector<long long> numbers = std::vector<long long>(n - 1, 0);
  for (long long i = 0; i < n - 1; ++i) {
	std::cin >> numbers.at(i);
  }

  /*std::vector<long long> ceil_logarithms = std::vector<long long>(n + 1, 0);
  for (long long i = 2; i <= n; i++) {
	ceil_logarithms.at(i) = ceil_logarithms.at((i + 1) / 2) + 1;
  }*/
  // std::vector<std::pair<long long, long long>> tree = std::vector<std::pair<long long, long long>>((1 << (ceil_logarithms.at(n) + 1)), std::make_pair(0, 0));
  std::vector<std::pair<long long, long long>> tree = std::vector<std::pair<long long, long long>>(4 * n, std::make_pair(0, 0));
  // first -- to add; second -- maximum
  // std::cout << "tree size == " << tree.size() << std::endl;
  buildTree(tree, numbers, 1, 0, n - 2);
  long long capacity, m;
  std::cin >> capacity >> m;
  for (long long i = 0; i < m; ++i) {
	long long start, end, number_of_tickets;
	std::cin >> start >> end >> number_of_tickets;
	long long cur_max = getMax(tree, 1, 0, n - 2, start, --end);
	if (cur_max + number_of_tickets <= capacity) {
	  update(tree, 1, 0, n - 2, start, end, number_of_tickets);
	  /*std::cout << "tree:  ";
	  for (auto k: tree) {
		std::cout << "addition == " << k.first << ";  maximum == " << k.second << std::endl;
	  }
	  std::cout << std::endl; */
	} else {
	  std::cout << i << " ";
	}
  }
  std::cout << std::endl;

  /*std::cout << "tree:  ";
  for (auto k: tree) {
	std::cout << "addition == " << k.first << ";  maximum == " << k.second << std::endl;
  }*/
  //update(tree, 1, 0, n - 2, 0, 2, 2);
/*
  std::cout << "tree after update:  ";
  for (auto k: tree) {
	std::cout << "addition == " << k.first << ";  maximum == " << k.second << std::endl;
  }
  std::cout << std::endl;
  std::cout << getMax(tree, 1, 0, n - 2, 2, 3);
*/
}
