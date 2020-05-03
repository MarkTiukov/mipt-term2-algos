template<typename T>
struct Node {
  T value;
  Node *next = nullptr;
  Node *previous = nullptr;

  Node(T value) : value(value) {}
  Node(T value, Node *previous) : value(value), previous(previous) {}

};

template<typename T>
class List {
 private:

 public:

};