#ifndef VECTOR_CAPACITY_TPP
#define VECTOR_CAPACITY_TPP

namespace s21 {

template <typename T>
bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::out_of_range("New size is too large");
  }
  if (size > capacity_) {
    vector<value_type> temp(size);
    for (size_type i = 0; i < size_; ++i) {
      temp.data_[i] = data_[i];
    }
    temp.size_ = size_;
    *this = std::move(temp);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    vector<value_type> temp(size_);
    for (size_type i = 0; i < size_; ++i) {
      temp.data_[i] = data_[i];
    }
    *this = std::move(temp);
  }
}
}  // namespace s21

#endif