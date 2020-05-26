#include <utility>
#include <iterator>
#include <type_traits>

template<typename T>
class List {
 public:
  struct Node {
	T value;
	Node* next = nullptr;
	Node* previous = nullptr;

	Node() = default;

	Node(const T& value) : value(value) {}
	Node(const T& value, Node* previous) : value(value), previous(previous) {}
	Node(const T& value, Node* previous, Node* next) : Node(value, previous), next(next) {}

	Node(T&& value) : value(std::move(value)) {}
	Node(T&& value, Node* previous) : value(std::move(value)), previous(previous) {}
	Node(T&& value, Node* previous, Node* next) : value(std::move(value)), previous(previous), next(next) {}

	template<typename... Args>
	Node(Args&& ... args) : value(std::forward<Args>(args)...) {}

	template<typename... Args>
	Node(Node* previous, Args&& ... args) : value(std::forward<Args>(args)...), previous(previous) {}

	template<typename... Args>
	Node(Node* previous, Node* next, Args&& ... args) : value(std::forward<Args>(args)...), previous(previous), next(next) {}

	bool operator==(const Node& rhs) const { return this->value == rhs.value; }
	bool operator!=(const Node& rhs) const { return !(rhs == *this); }

  };
 private:
  size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;

  template<bool IsConst = true>
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, std::conditional_t<IsConst, const T, T>> {
   private:
	Node* iter_;
   public:
	Iterator() = default;
	Iterator(Node* pointer) : iter_(pointer) {}
	Iterator(const Iterator<false>& it) : iter_(it.iter_) {}
	Iterator(const Iterator<true>& it) : iter_(it.iter_) {}

	bool operator==(const Iterator<IsConst>& rhs) const { return this->iter_ == rhs.iter_; }
	bool operator!=(const Iterator<IsConst>& rhs) const { return !(rhs == *this); }

	bool operator==(const Iterator<!IsConst>& rhs) const { return this->iter_ == rhs.iter_; }
	bool operator!=(const Iterator<!IsConst>& rhs) const { return !(rhs == *this); }

	Iterator operator++();
	Iterator operator--();

	typename Iterator::reference operator*() const { return this->iter_->value; }

  };

 public:

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using value_type = T;

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

  iterator begin() { return iterator(this->first_); }
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(this->first_); }
  const_iterator cend() const { return const_iterator(nullptr); }

  void insert(const_iterator it, const T& element);
  void insert(const_iterator it, T&& element);
  void insert(const_iterator it, const_iterator first, const_iterator last);

  void erase(iterator it);
  void erase(iterator first, iterator last);

  void push_front(const T& element);
  void push_front(T&& element);
  void push_back(const T& element);
  void push_back(T&& element);

  void pop_front();
  void pop_back();

  template<typename... Args>
  void emplace(const_iterator it, Args&& ... args);

  template<typename... Args>
  void emplace_back(Args&& ... args);

  template<typename... Args>
  void emplace_front(Args&& ... args);

  void reverse();

  void unique();

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
	  first_ = new Node(*(rhs.first_->value));
	  Node* current_node = first_;
	  Node* current_node_rhs = rhs.first_;
	  while (current_node_rhs != rhs.last_) {
		current_node_rhs = current_node_rhs->next;
		auto new_node = new Node(*(current_node_rhs->value));
		new_node->previous = current_node;
		current_node->next = new_node;
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
	  first_ = new Node(std::move(*(rhs.first_->value)));
	  Node* current_node = first_;
	  Node* current_node_rhs = rhs.first_;
	  while (current_node_rhs != rhs.last_) {
		current_node_rhs = current_node_rhs->next;
		delete current_node_rhs->previous;
		auto new_node = new Node(std::move(*(current_node_rhs->value)));
		new_node->previous = current_node;
		current_node->next = new_node;
		current_node = new_node;
	  }
	  delete current_node_rhs;
	  last_ = current_node;
	}
  }
  return *this;
}

template<typename T>
template<bool IsConst>
typename List<T>::template Iterator<IsConst> List<T>::Iterator<IsConst>::operator++() {
  this->iter_ = this->iter_->next;
  return *this;
}

template<typename T>
template<bool IsConst>
typename List<T>::template Iterator<IsConst> List<T>::Iterator<IsConst>::operator--() {
  if (this->iter_ == nullptr)
	this->iter_ = List<T>::last_;
  else
	this->iter_ = this->iter_->previous;
  return *this;
}

template<typename T>
void List<T>::insert(List::const_iterator it, const T& element) {
  Node* insertion = new Node(element, it.iter_->previous, it.iter_);
  if (it.iter_->previous != nullptr) {
	it.iter_->previous->next = insertion;
  } else {
	this->first_ = it.iter_;
  }
  it.iter_->previous = insertion;
  ++(this->size_);
}

template<typename T>
void List<T>::insert(List::const_iterator it, T&& element) {
  Node* insertion = new Node(std::move(element), it.iter_->previous, it.iter_);
  if (it.iter_->previous != nullptr) {
	it.iter_->previous->next = insertion;
  } else {
	this->first_ = it.iter_;
  }
  it.iter_->previous = insertion;
  ++(this->size_);
}

template<typename T>
void List<T>::insert(List::const_iterator it, List::const_iterator first, List::const_iterator last) {
  while (first != last) {
	this->insert(it, first->value);
  }
  this->insert(it, first->value);
}

template<typename T>
void List<T>::erase(List::iterator it) {
  if (it.iter_->previous != nullptr) {
	it.iter_->previous = it.iter_->next;
  }
  if (it.iter_->next != nullptr) {
	it.iter_->next = it.iter_->previous;
  } else {
	this->last_ = it.iter_->previous;
  }
  delete it.iter_;
  --(this->size_);
}

template<typename T>
void List<T>::erase(List::iterator first, List::iterator last) {
  const_iterator it = first.iter_;
  while (first != last) {
	first++;
	this->erase(it);
	it = first;
  }
  this->erase(it);
}

template<typename T>
void List<T>::push_front(const T& element) {
  Node* new_node = new Node(element);
  if (size_ > 0) {
	this->first_->previous = new_node;
	new_node->next = this->first_;
  } else {
	this->last_ = new_node;
  }
  this->first_ = new_node;
  ++(this->size_);
}

template<typename T>
void List<T>::push_front(T&& element) {
  Node* new_node = new Node(std::move(element));
  if (size_ > 0) {
	this->first_->previous = new_node;
	new_node->next = this->first_;
  } else {
	this->last_ = new_node;
  }
  this->first_ = new_node;
  ++(this->size_);
}

template<typename T>
void List<T>::push_back(const T& element) {
  Node* new_node = new Node(element);
  if (size_ > 0) {
	this->last_->next = new_node;
	new_node->previous = this->last_;
  } else {
	this->first_ = new_node;
  }
  this->last_ = new_node;
  ++(this->size_);
}

template<typename T>
void List<T>::push_back(T&& element) {
  Node* new_node = new Node(std::move(element));
  if (size_ > 0) {
	this->last_->next = new_node;
	new_node->previous = this->last_;
  } else {
	this->first_ = new_node;
  }
  this->last_ = new_node;
  ++(this->size_);
}

template<typename T>
template<typename... Args>
void List<T>::emplace(List::const_iterator it, Args&& ... args) {
  Node* insertion = new Node(it.iter_->previous, it.iter_, std::forward<Args>(args)...);
  if (it.iter_->previous != nullptr) {
	it.iter_->previous->next = insertion;
  } else {
	this->first_ = it.iter_;
  }
  it.iter_->previous = insertion;
  ++(this->size_);
}

template<typename T>
void List<T>::pop_front() {
  if (this->size_ > 0) {
	if (this->size_ > 1) {
	  this->first_->next->previous = nullptr;
	} else {
	  this->first_ = nullptr;
	}
	this->first_ = this->first_->next;
  }
}

template<typename T>
void List<T>::pop_back() {
  if (this->size_ > 0) {
	if (this->size_ > 1) {
	  this->last_->previous->next = nullptr;
	} else {
	  this->last_ = nullptr;
	}
	this->last_ = this->last_->previous;
  }
}

template<typename T>
template<typename... Args>
void List<T>::emplace_back(Args&& ... args) {
  Node* insertion = new Node(std::forward<Args>(args)..., this->last_);
  if (this->size_ > 0) {
	this->last_->next = insertion;
  } else {
	this->first_ = insertion;
  }
  this->last_ = insertion;
  ++(this->size_);
}

template<typename T>
template<typename... Args>
void List<T>::emplace_front(Args&& ... args) {
  Node* insertion = new Node(std::forward<Args>(args)...);
  if (this->size_ > 0) {
	insertion->next = this->first_;
	this->first_->previous = insertion;
  } else {
	this->last_ = insertion;
  }
  this->first_ = insertion;
  ++(this->size_);
}

template<typename T>
void List<T>::reverse() {
  Node* current_node = this->last_;
  while (current_node != nullptr) {
	Node* prev = current_node->previous;
	current_node->prev = current_node->next;
	current_node->next = prev;
	current_node = prev;
  }
  Node* last = this->last_;
  this->last_ = this->first_;
  this->first_ = last;
}

template<typename T>
void List<T>::unique() {
  if (this->size_ > 0) {
	Node* prev = this->first_;
	Node* current_node = this->first_->next;
	for (int i = 0; i < this->size_; ++i) {
	  if (current_node->value == prev->value) {
		prev->next = current_node->next;
		if (current_node->next != nullptr) {
		  current_node->next->previous = prev;
		}
		delete current_node;
	  }
	}
  }
}
