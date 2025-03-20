#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 public:
  // member type
  using value_type = T;
  using reference = T &;
  using iterator = T *;
  using const_reference = const T &;
  using const_iterator = const T *;
  using size_type = size_t;
  // constructor
  vector();
  vector(const vector &v);
  vector(vector &&v) noexcept;
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector &operator=(vector &&v) noexcept;
  // destructor
  ~vector();
  // access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();
  // capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  // iterators
  iterator begin();
  iterator end();
  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
  // bonus
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};
};  // namespace s21

#include "vector_access.tpp"
#include "vector_capacity.tpp"
#include "vector_functions.tpp"
#include "vector_iterators.tpp"
#include "vector_modifiers.tpp"

#endif
