#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class List {
 public:
  class ListIterator;
  class ListIteratorConst;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListIteratorConst;

  List() : l_size_(0U), begin_(nullptr), end_(nullptr) { fake_ = new Node; };

  List(size_t n) : List() {
    while (n > 0) {
      Push_back(value_type());
      --n;
    }
  };

  List(std::initializer_list<T> const &items) : List() {
    for (const auto &item : items) {
      Push_back(item);
    }
  };

  List(const List &l) : List() { Copy(l); }

  List(List &&l) noexcept
      : l_size_(l.l_size_),
        begin_(l.begin_),
        end_(l.end_),
        fake_(l.fake_) {  // move constructor
    l.l_size_ = 0;
    l.begin_ = nullptr;
    l.end_ = nullptr;
    l.fake_ = nullptr;
  }

  ~List() {
    Clear();
    delete fake_;
    fake_ = nullptr;
  };

  const_reference front() { return begin_->data; };
  const_reference back() { return end_->data; };
  iterator begin() { return iterator(begin_); };
  iterator end() noexcept { return iterator(fake_); }
  const_iterator cend() const noexcept { return const_iterator(fake_); }
  const_iterator cbegin() const noexcept { return const_iterator(begin_); }

  bool Empty() { return ((begin_ == nullptr) && (end_ == nullptr)); };
  size_type Size() { return l_size_; };
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  };

  void Clear() {
    if (!Empty()) {
      while (begin_ != fake_) {
        end_ = begin_->next;
        delete begin_;
        begin_ = end_;
        --l_size_;
      }
      fake_->next = nullptr;
      fake_->prev = nullptr;
      begin_ = nullptr;
      end_ = nullptr;
      delete fake_;
      fake_ = nullptr;
      l_size_ = 0;
    }
  };

  T At(iterator pos) {
    iterator it = begin();
    Node *tmp = begin_;
    for (; it != pos; ++it) {
      tmp = tmp->next;
    }
    return tmp->data;
  };

  T At(int ind) {
    if (ind < 0 || ind > (int)l_size_) throw "over list";
    iterator it = begin();
    Node *tmp = begin_;
    for (int i = 0; i < ind; ++i) {
      ++it;
      tmp = tmp->next;
    }
    return tmp->data;
  };

  iterator Insert(iterator pos, const_reference value) {
    bool out = false;
    iterator it_b = begin();
    for (; it_b != end(); ++it_b) {
      if (it_b == pos) {
        out = false;
        break;
      }
      out = true;
    }
    if (pos == begin()) {
      Push_front(value);
      pos = iterator(begin_);
    } else if (out) {
      Push_back(value);
      pos = iterator(end_);
    } else {
      Node *newNode = new Node(value);
      Node *tmp = begin_;
      Node *tmp2 = tmp->next;
      iterator it = begin();
      --pos;
      for (; it != pos; ++it) {
        tmp = tmp->next;
        tmp2 = tmp2->next;
      }
      newNode->next = tmp->next;
      newNode->prev = tmp;
      tmp->next = newNode;
      tmp2->prev = newNode;
      ++it;
      ++l_size_;
      return it;
    }
    return pos;
  };
  void Erase(iterator pos) {
    if (l_size_ == 0) return;
    Node *tmp;
    if (pos == end()) {
      tmp = end_;
    } else {
      tmp = begin_;
      for (auto i = begin(); i != pos; ++i) {
        tmp = tmp->next;
      }
    }
    Node *prev = tmp->prev;
    Node *next = tmp->next;
    delete tmp;
    if ((l_size_ > 1) && (prev != nullptr)) {
      prev->next = next;
    }
    if ((next != fake_) && (l_size_ > 1)) {
      next->prev = prev;
    }
    if (pos == begin()) {
      begin_ = next;
    }
    if (pos == end()) {
      end_ = prev;
    }
    --l_size_;
  };
  void Push_back(const_reference value) {
    try {
      Node *tmp = new Node;
      tmp->next = nullptr;
      tmp->prev = end_;
      tmp->data = value;
      if (end_ != nullptr) {
        end_->next = tmp;
      }
      if (l_size_ == 0) {
        begin_ = end_ = tmp;
      } else {
        end_ = tmp;
      }
      end_->next = fake_;
      fake_->prev = end_;
      fake_->next = begin_;
      ++l_size_;
    } catch (std::bad_alloc &err) {
      std::cout << err.what() << std::endl;
    }
  };

  void Pop_back() { Erase(end()); };
  void Push_front(const_reference value) {
    Node *tmp = new Node;
    tmp->next = begin_;
    tmp->prev = nullptr;
    tmp->data = value;
    if (l_size_ > 0) {
      begin_->prev = tmp;
      begin_ = tmp;
    } else {
      begin_ = end_ = tmp;
    }
    end_->next = fake_;
    fake_->prev = end_;
    fake_->next = begin_;
    ++l_size_;
  };
  void Pop_front() { Erase(begin()); };
  void Swap(List &other) {
    if (this != &other) {
      std::swap(begin_, other.begin_);
      std::swap(end_, other.end_);
      std::swap(fake_, other.fake_);
      std::swap(l_size_, other.l_size_);
    }
  };
  void Merge(List &other) {
    if (!Empty() && !other.Empty()) {
      iterator it = begin();
      iterator oit = other.begin();
      while (it != end()) {
        if (oit != other.end()) {
          if (*it >= *oit) {
            Insert(it, *oit);
            ++oit;
          } else {
            ++it;
          }
        } else {
          break;
        }
      }
      while (oit != other.end()) {
        Insert(it, *oit);
        ++oit;
      }
    } else if (Empty() && !other.Empty()) {
      Copy(other);
    }
    other.Clear();
  };
  void Splice(ListIteratorConst pos, List &other) {
    if (!other.Empty()) {
      iterator pos_c = begin();
      const_iterator pos_p = cbegin();
      while (pos_p != pos) {
        ++pos_c;
        ++pos_p;
      }
      iterator it = other.begin();
      for (; it != other.end(); ++it) {
        Insert(pos_c, *it);
      }
      other.Clear();
    }
  };
  void Reverse() {
    Node *cur = begin_;
    Node *it = end_;
    size_type mid = Size() / 2;
    for (size_t idx = 0, jdx = Size(); idx < mid; ++idx, --jdx) {
      std::swap(cur->data, it->data);
      cur = cur->next;
      it = it->prev;
    }
  };
  void Unique() {
    iterator next = begin();
    ++next;
    iterator it = begin();
    iterator new_it = it;
    for (; it != end(); ++next) {
      ++new_it;
      if (*it == *next) {
        Erase(it);
      }
      it = new_it;
    }
  };

  void Swap_Elem(value_type &val1, value_type &val2) { std::swap(val1, val2); }

  void Sort() {
    Node *cur = nullptr;
    Node *it = nullptr;
    for (cur = begin_; cur->next != fake_; cur = cur->next) {
      for (it = cur->next; it != fake_; it = it->next) {
        if (cur->data > it->data) {
          Swap_Elem(cur->data, it->data);
        }
      }
    }
  };

  void Copy(const List<value_type> &obj) {
    Clear();
    Node *tmp = obj.begin_;
    while (tmp != obj.fake_) {
      Push_back(tmp->data);
      tmp = tmp->next;
    }
  }

  // Move Assignment Operator
  List &operator=(List &&other) {
    if (this != &other) {
      Clear();
      l_size_ = other.l_size_;
      begin_ = other.begin_;
      end_ = other.end_;
      fake_ = other.fake_;

      other.l_size_ = 0;
      other.begin_ = nullptr;
      other.end_ = nullptr;
      other.fake_ = nullptr;
    }
    return *this;
  }

  List &operator=(List const &l) {
    Clear();
    Copy(l);
    return *this;
  }  // operator copy

  struct Node {
    T data;
    Node *prev;  // end
    Node *next;  // begin
    Node(T value = T()) : data(value) {}
  };

  size_t l_size_;
  Node *begin_;
  Node *end_;
  Node *fake_;

  class ListIterator {
   public:
    using reference = T &;
    using pointer = T *;

    ListIterator() : cur(nullptr) {}

    explicit ListIterator(Node *cur) : cur(cur) {}

    reference operator*() noexcept { return cur->data; }

    ListIterator &operator++() noexcept {
      if (cur) {
        cur = cur->next;
      }
      return *this;
    }

    ListIterator operator++(int) noexcept {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() noexcept {
      if (cur) {
        cur = cur->prev;
      }
      return *this;
    }

    ListIterator operator--(int) noexcept {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return cur == other.cur;
    }

    bool operator!=(const ListIterator &other) const {
      return cur != other.cur;
    }

   private:
    Node *cur;
  };

  class ListIteratorConst {
   public:
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    ListIteratorConst() : cur(nullptr) {}

    explicit ListIteratorConst(Node *cur) : cur(cur) {}

    reference operator*() const noexcept { return cur->data; }

    const_iterator &operator++() noexcept {
      if (cur) {
        cur = cur->next;
      }
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator &operator--() noexcept {
      if (cur) {
        cur = cur->prev;
      }
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator &other) const {
      return (cur == other.cur);
    }

    bool operator!=(const const_iterator &other) const {
      return (cur != other.cur);
    }

   private:
    Node *cur;
  };

  template <typename... Args>
  iterator Insert_Many(const_iterator pos, Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    const_iterator it = cbegin();
    iterator new_pos = begin();
    while (it != pos) {
      ++new_pos;
      ++it;
    }

    for (auto const &i : args_v) {
      new_pos = Insert((new_pos), i);
      ++new_pos;
    }
    return new_pos;
  }

  template <typename... Args>
  void Insert_Many_Back(Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto const &i : args_v) {
      Push_back(i);
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto const &i : args_v) {
      Push_front(i);
    }
  }
};
}  // namespace s21
#endif