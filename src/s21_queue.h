#include <cstddef>
#include <cstdio>
#include <iostream>

#include "containers/sequential_containers/s21_list.h"

namespace s21 {

template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  Queue() { data_.Clear(); }

  Queue(std::initializer_list<value_type> const &items) {
    data_.Clear();
    for (const auto &item : items) {
      push(item);
    }
  }
  Queue(const Queue &q) : data_(q.data_) {}

  Queue(Queue &&q) : data_(q.data_) { q.clear(); }

  ~Queue() { data_.Clear(); }

  Queue &operator=(Queue &&q) {
    if (this != &q) {
      data_.Clear();

      data_ = std::move(q.data_);
      q.clear();
    }
    return *this;
  }

  T At(int ind) { return data_.At(ind); }
  const_reference front() { return data_.front(); }
  const_reference back() { return data_.back(); }
  bool empty() { return data_.Empty(); }
  void clear() { data_.Clear(); }
  size_type size() { return data_.Size(); }
  void push(const_reference value) { data_.Push_back(value); }
  void pop() { data_.Pop_front(); }
  void swap(Queue &other) { data_.Swap(other.data_); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  List<value_type> data_;
};

}  // namespace s21
