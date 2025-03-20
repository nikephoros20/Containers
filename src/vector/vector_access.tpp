#ifndef VECTOR_ACCESS_TPP
#define VECTOR_ACCESS_TPP

namespace s21 {

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (size_ == 0) throw std::out_of_range("Vector is empty");
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (size_ == 0) throw std::out_of_range("Vector is empty");
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return data_;
}
}  // namespace s21

#endif