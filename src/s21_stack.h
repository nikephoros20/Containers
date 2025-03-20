#include <cstddef>
#include <cstdio>
#include <iostream>

#include "containers/sequential_containers/s21_list.h"

namespace s21 {

template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() { data_.Clear(); }
  Stack(std::initializer_list<value_type> const &items) {
    data_.Clear();
    for (const auto &i : items) {
      push(i);
    }
  }

  Stack(Stack &&s) : data_(s.data_) { s.clear(); }

  Stack(const Stack &s) : data_(s.data_) {}

  ~Stack() { data_.Clear(); }

  Stack &operator=(Stack &&s) {
    if (this != &s) {
      data_.Clear();

      data_ = std::move(s.data_);
      s.clear();
    }
    return *this;
  }

  const_reference top() { return data_.front(); }
  void push(const_reference value) { data_.Push_front(value); }
  void pop() { data_.Pop_front(); }
  bool empty() { return data_.Empty(); }
  void clear() { data_.Clear(); }
  size_type size() { return data_.Size(); };
  void swap(Stack &other) { data_.Swap(other.data_); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  List<value_type> data_;
};
}  // namespace s21
