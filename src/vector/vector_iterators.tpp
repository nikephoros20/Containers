#ifndef VECTOR_ITERATORS_TPP
#define VECTOR_ITERATORS_TPP

namespace s21 {

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}
}  // namespace s21

#endif