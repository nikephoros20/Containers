#ifndef S21_CONTAINERS_ARRAY_H
#define S21_CONTAINERS_ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {

template <typename T, size_t N>
class array {
 public:
  // member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // constructor
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  array<T, N> &operator=(array &&a);
  // destructor
  ~array();
  // access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin();
  iterator end();
  // capacity
  bool empty();
  size_type size();
  size_type max_size();
  // modifiers
  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type data_[N];
};
};  // namespace s21

#include "array_access.tpp"
#include "array_capacity.tpp"
#include "array_functions.tpp"
#include "array_iterators.tpp"
#include "array_modifiers.tpp"

#endif
