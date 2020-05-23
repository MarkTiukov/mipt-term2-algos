#include <utility>
#include <iterator>

template<typename T>
class List {
 public:
  struct Node {
	T value;
	Node* next = nullptr;
	Node* previous = nullptr;

	Node() = default;

	Node(T& value) : value(std::move(value)) {}
	Node(T& value, Node* previous) : value(std::move(value)), previous(previous) {}
	Node(T& value, Node* previous, Node* next) : Node(std::move(value), previous), next(next) {}

	Node(T&& value) : value(std::move(value)) {}
	Node(T&& value, Node* previous) : value(std::move(value)), previous(previous) {}
	Node(T&& value, Node* previous, Node* next) : Node(std::move(value), previous), next(next) {}

	bool operator==(const Node& rhs) const { return this->value == rhs.value; }
	bool operator!=(const Node& rhs) const { return !(rhs == *this); }

  };
 private:
  size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;

  class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
   private:
	Node* iter_;
   public:
	ConstIterator() = default;
	ConstIterator(Node* pointer) : iter_(pointer) {}

	bool operator==(const ConstIterator& rhs) const { return this->iter_ == rhs.iter_; }
	bool operator!=(const ConstIterator& rhs) const { return !(rhs == *this); }

	ConstIterator operator++();
	ConstIterator operator--();
  };

 public:
  List() = default;

  List(size_t count, const T& value = T());

  List(const List& rhs) { *this = rhs; }

  List(const List&& rhs) { *this = std::move(rhs); }

  List& operator=(const List& rhs);

  List& operator=(const List&& rhs);

  void clear();
  size_t size() { return this->size_; }

  T& front() { return this->first_->value; }
  T& back() { return this->last_->value; }

  bool empty() { return this->size_ == 0; }

  virtual ~List();

};

template<typename T>
void List<T>::clear() {
  if (this->size_ > 0) {
	if (this->size_ == 1) {
	  delete this->first_;
	} else {
	  Node* current_node = this->first_;
	  do {
		Node* next = current_node->next;
		delete current_node;
		current_node = next;
	  } while (current_node != this->last_);
	  delete current_node;
	}
	this->size_ = 0;
	this->first_ = nullptr;
	this->last_ = nullptr;
  }
}

template<typename T>
List<T>::~List() {
  this->clear();
}

template<typename T>
List<T>::List(size_t count, const T& value) : size_(count) {
  if (this->size_ > 0) {
	this->first_ = new Node(std::move(value));
  }
  Node* current_node = this->first_;
  for (size_t i = 1; i < this->size_; ++i) {
	Node* new_node = new Node(value, current_node);
	current_node->next = new_node;
	new_node->previous = current_node;
	current_node = new_node;
  }
  this->last_ = current_node;

}

template<typename T>
List<T>& List<T>::operator=(const List& rhs) {
  if (this != &rhs) {
	this->clear();
	if (rhs.first_ != nullptr) {
	  size_ = rhs.size_;
	  first_ = new Node(*rhs.first_->value);
	  Node* current_node = first_;
	  Node* current_node_rhs = rhs.first_;
	  while (current_node_rhs != rhs.last_) {
		current_node_rhs = current_node_rhs->right;
		auto new_node = new Node(*current_node_rhs->value);
		new_node->left = current_node;
		current_node->right = new_node;
		current_node = new_node;
	  }
	  last_ = current_node;
	}
  }
  return *this;
}

template<typename T>
List<T>& List<T>::operator=(const List&& rhs) {
  if (this != &rhs) {
	this->clear();
	if (rhs.first_ != nullptr) {
	  size_ = rhs.size_;
	  first_ = new Node(std::move(*rhs.first_->value));
	  Node* current_node = first_;
	  Node* current_node_rhs = rhs.first_;
	  while (current_node_rhs != rhs.last_) {
		current_node_rhs = current_node_rhs->right;
		delete current_node_rhs->left;
		auto new_node = new Node(std::move(*current_node_rhs->value));
		new_node->left = current_node;
		current_node->right = new_node;
		current_node = new_node;
	  }
	  delete current_node_rhs;
	  last_ = current_node;
	}
  }
  return *this;
}
template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++() {
  this->iter_ = this->iter_->next;
  return *this;
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--() {
  this->iter_ = this->iter_->previous;
  return *this;
}
