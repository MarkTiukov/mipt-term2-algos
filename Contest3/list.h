#include <utility>

template<typename T>
class List {
 public:
  struct Node {
	T value;
	Node* next = nullptr;
	Node* previous = nullptr;

	Node() = default;
	Node(T value) : value(value) {}
	Node(T value, Node* previous) : value(value), previous(previous) {}
	Node(T value, Node* previous, Node* next) : value(value), previous(previous), next(next) {}
  };
 private:
  size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;
 public:
  List() = default;
  List(size_t count, const T& value = T()) : size_(count) {
    if (this->size_ > 0) {
    	this->first_ = new Node(value);
    }

  }
};