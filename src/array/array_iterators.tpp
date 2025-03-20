#ifndef ARRAY_ITERATORS_TPP
#define ARRAY_ITERATORS_TPP

namespace s21 {

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return &data_[0];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return &data_[size_];
}
}  // namespace s21

#endif