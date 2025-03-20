#ifndef VECTOR_MODIFIERS_TPP
#define VECTOR_MODIFIERS_TPP

namespace s21 {

template <typename T>
void vector<T>::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - data_;
  if (size_ >= capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
    reserve(new_capacity);
  }
  std::move_backward(data_ + index, data_ + size_, data_ + size_ + 1);
  data_[index] = value;
  ++size_;
  return data_ + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - data_;
  std::move(data_ + index + 1, data_ + size_, data_ + index);
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
    reserve(new_capacity);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// bonus
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> temp{args...};
  iterator cur_pos = begin() + (pos - begin());
  for (size_t i = 0; i < temp.size(); ++i) {
    cur_pos = insert(cur_pos, temp[i]);
    ++cur_pos;
  }
  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}
}  // namespace s21

#endif