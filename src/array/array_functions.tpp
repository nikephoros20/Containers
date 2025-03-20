#ifndef ARRAY_FUNCTIONS_TPP
#define ARRAY_FUNCTIONS_TPP

namespace s21 {

template <typename T, size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items)
    : size_(items.size()) {
  size_t i = 0;
  for (const auto &item : items) {
    data_[i++] = item;
  }
}

template <typename T, size_t N>
array<T, N>::array(const array &a) : size_(a.size_) {
  std::copy(a.data_, a.data_ + N, data_);
}

template <typename T, size_t N>
array<T, N>::array(array &&a) : size_(a.size_) {
  std::move(a.data_, a.data_ + N, data_);
  a.size_ = 0;
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    std::swap(data_, a.data_);
    std::swap(size_, a.size_);
  }
  return *this;
}
}  // namespace s21

#endif