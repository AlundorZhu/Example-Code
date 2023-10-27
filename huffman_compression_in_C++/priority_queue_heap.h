#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <algorithm>
#include <vector>

template <typename T>
class PriorityQueue {
 public:
  // Constructor capacity
  PriorityQueue(int capacity)
      : items(capacity + 1) {}
  // Constructor build heap
  PriorityQueue(const std::vector<T> &v);
  // Return number of items in priority queue
  size_t Size();
  // Return top of priority queue
  T& Top();
  // Remove top of priority queue
  void Pop();
  // Insert item and sort priority queue
  void Push(const T &item);

 private:
  std::vector<T> items;
  size_t cur_size = 0;

  // Helper methods for indices
  size_t Root() {
    return 1;
  }
  size_t Parent(size_t n) {
    return n / 2;
  }
  size_t LeftChild(size_t n) {
    return 2 * n;
  }
  size_t RightChild(size_t n) {
    return 2 * n + 1;
  }

  // Helper methods for node testing
  bool HasParent(size_t n) {
    return n != Root();
  }
  bool IsNode(size_t n) {
    return n <= cur_size;
  }

  // Helper methods for restructuring
  void PercolateUp(size_t n);
  void PercolateDown(size_t n);
};

template <typename T>
size_t PriorityQueue<T>::Size() {
  return cur_size;
}

template <typename T>
T& PriorityQueue<T>::Top(void) {
  if (!Size())
    throw std::underflow_error(
        "Empty priority queue!");
  return items[Root()];
}

template <typename T>
void PriorityQueue<T>::PercolateUp(size_t n) {
  while (HasParent(n) && items[Parent(n)] > items[n]) {
    std::swap(items[Parent(n)], items[n]);
    n = Parent(n);
  }
}

template <typename T>
void PriorityQueue<T>::Push(const T &item) {
  if (cur_size + 1 == items.size())
    throw std::overflow_error("Priority queue full!");

  // Insert at the end
  items[++cur_size] = std::move(item);
  // Percolate up
  PercolateUp(cur_size);
}

template <typename T>
void PriorityQueue<T>::PercolateDown(size_t n) {
  // While node has at least one child (if one, necessarily on the left)
  while (IsNode(LeftChild(n))) {
    // Consider left child by default
    size_t child = LeftChild(n);
    // If right child exists and smaller than left child, then consider right child
    if (IsNode(RightChild(n)) && items[RightChild(n)] < items[LeftChild(n)])
      child = RightChild(n);

    // Exchange smallest child with node to restore heap-order if necessary
    if (items[child] < items[n])
      std::swap(items[child], items[n]);
    else
      break;

    // Do it again, one level down
    n = child;
  }
}

template <typename T>
void PriorityQueue<T>::Pop() {
  if (!Size())
    throw std::underflow_error("Empty priority queue!");
  // Move last item back to root and reduce heap's size
  items[Root()] = std::move(items[cur_size--]);
  PercolateDown(Root());
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T> &v)
  : items(v.size() + 1), cur_size(v.size()) {
    // Only enforce structure property
    for (size_t n = 0; n < v.size(); n++)
      items[n + 1] = v[n];

    // Now enforce heap-property
    for (size_t n = cur_size / 2; n >= 1; n--)
      PercolateDown(n);
}

#endif  // PRIORITY_QUEUE_H_
