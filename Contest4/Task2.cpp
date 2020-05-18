#include <iostream>
#include <vector>

const int MY_INT_MIN = -2147483647;

void buildTree(std::vector<std::pair<int, int>> &tree, std::vector<int> &a, int current_node, int tree_start, int tree_end) {
  if (tree_start == tree_end) {
	tree[current_node] = std::make_pair(a[tree_start], a[tree_start]);
  } else {
	int tm = (tree_start + tree_end) / 2;
	buildTree(tree, a, current_node * 2, tree_start, tm);
	buildTree(tree, a, current_node * 2 + 1, tm + 1, tree_end);
	tree[current_node].second = std::max(tree[current_node * 2].second, tree[current_node * 2 + 1].second);
  }
}

void update(std::vector<std::pair<int, int>> &t, int current_node, int tree_start, int tree_end, int left, int right, int add) {
  if (left <= right) {
	if (left == tree_start && tree_end == right) {
	  t[current_node].first += add;
	  // t[current_node].second = std::max(t[current_node * 2].second, t[current_node * 2 + 1].second) + t[current_node].first;
	} else {
	  int tm = (tree_start + tree_end) / 2;
	  update(t, current_node * 2, tree_start, tm, left, std::min(right, tm), add);
	  update(t, current_node * 2 + 1, tm + 1, tree_end, std::max(left, tm + 1), right, add);
	}
	t[current_node].second = std::max(t[current_node * 2].second, t[current_node * 2 + 1].second) + t[current_node].first;
  }
}

int getMax(std::vector<std::pair<int, int>> &tree, int current_node, int tree_start, int tree_end, int left, int right) {
  if (left > right) {
	return MY_INT_MIN;
  }
  if (left == tree_start && right == tree_end) {
	return tree[current_node].second;
  }
  int tm = (tree_start + tree_end) / 2;
  return std::max(getMax(tree, current_node * 2, tree_start, tm, left, std::min(right, tm)),
				  getMax(tree, current_node * 2 + 1, tm + 1, tree_end, std::max(left, tm + 1), right)) + tree[current_node].first;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> numbers = std::vector<int>(n - 1);
  for (int i = 0; i < n - 1; ++i) {
	std::cin >> numbers[i];
  }
  std::vector<int> ceil_logarithms = std::vector<int>(n + 1, 0);
  for (int i = 2; i <= n; i++) {
	ceil_logarithms[i] = ceil_logarithms[(i + 1) / 2] + 1;
  }
  // std::vector<std::pair<int, int>> tree = std::vector<std::pair<int, int>>((1 << (ceil_logarithms[n] + 1)), std::make_pair(0, 0));
  std::vector<std::pair<int, int>> tree = std::vector<std::pair<int, int>>(4 * n, std::make_pair(0, 0));
  // first -- to add; second -- maximum
  // std::cout << "tree size == " << tree.size() << std::endl;
  buildTree(tree, numbers, 1, 0, n - 2);

  int capacity, m;
  std::cin >> capacity >> m;
  for (int i = 0; i < m; ++i) {
	int start, end, number_of_tickets;
	std::cin >> start >> end >> number_of_tickets;
	int cur_max = getMax(tree, 1, 0, n - 2, start, --end);
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
  std::cout << std::endl;
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
