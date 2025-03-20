#ifndef ARRAY_CAPACITY_TPP
#define ARRAY_CAPACITY_TPP

namespace s21 {

template <typename T, size_t N>
bool array<T, N>::empty() {
  return size_ == 0;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}
}  // namespace s21

#endif