#ifndef ARRAY_ACCESS_TPP
#define ARRAY_ACCESS_TPP

namespace s21 {

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return data_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return data_[size_ - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}
}  // namespace s21

#endif