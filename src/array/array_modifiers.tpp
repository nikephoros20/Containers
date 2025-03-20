#ifndef ARRAY_MODIFIERS_TPP
#define ARRAY_MODIFIERS_TPP

namespace s21 {

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  for (size_type i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}
}  // namespace s21

#endif