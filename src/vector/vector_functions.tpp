#ifndef VECTOR_FUNCTIONS_TPP
#define VECTOR_FUNCTIONS_TPP

namespace s21 {

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : data_(new value_type[n]), size_(n), capacity_(n) {
  std::fill(data_, data_ + n, value_type{});
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(const vector &v)
    : data_(new value_type[v.size_]), size_(v.size_), capacity_(v.size_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr, v.size_ = 0, v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this != &v) {
    delete[] data_;
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}
}  // namespace s21

#endif