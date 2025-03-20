#ifndef CPP2_S21_CONTAINERS_1_BINARYTREE_H
#define CPP2_S21_CONTAINERS_1_BINARYTREE_H

#include <stdint.h>

#include <functional>
#include <iostream>

namespace BinaryTree {

template <class T, class Compare = std::less<T>>
class BinaryTree {
 public:
  using Key = T;
  using size_type = size_t;
  struct Node;

  struct iterator {
    Node *node_;

    explicit iterator(Node *node) : node_(node) {}

    iterator &operator++() & noexcept {
      if (node_ == nullptr) return *this;
      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        while (node_->left_ != nullptr) node_ = node_->left_;
        return *this;
      }
      Node *parent = node_->parent_;
      while (parent && node_ == parent->right_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    iterator &operator--() & noexcept {
      if (node_ == nullptr) return *this;
      if (node_->left_ != nullptr) {
        node_ = node_->left_;
        while (node_->right_ != nullptr) node_ = node_->right_;
        return *this;
      }
      Node *parent = node_->parent_;
      while (parent && node_ == parent->left_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    bool operator==(const iterator &other) const noexcept {
      return node_ == other.node_;
    }
    bool operator!=(const iterator &other) const noexcept {
      return node_ != other.node_;
    }

    Key &operator*() const & { return node_->key_; }
  };

  struct const_iterator {
    const Node *node_;

    explicit const_iterator(Node *node) : node_(node) {}

    const_iterator &operator++() & noexcept {
      if (node_ == nullptr) return *this;
      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        while (node_->left_ != nullptr) node_ = node_->left_;
        return *this;
      }
      Node *parent = node_->parent_;
      while (parent && node_ == parent->right_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    const_iterator &operator--() & noexcept {
      if (node_ == nullptr) return *this;
      if (node_->left_ != nullptr) {
        node_ = node_->left_;
        while (node_->right_ != nullptr) node_ = node_->right_;
        return *this;
      }
      Node *parent = node_->parent_;
      while (parent && node_ == parent->left_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    bool operator==(const const_iterator &other) const noexcept {
      return node_ == other.node_;
    }
    bool operator!=(const const_iterator &other) const noexcept {
      return node_ != other.node_;
    }

    const Key &operator*() const & { return node_->key_; }
  };

  BinaryTree() noexcept : root_(nullptr), size_(0) {}

  explicit BinaryTree(std::initializer_list<Key> const &items)
      : root_(nullptr), size_(0) {
    for (const auto &item : items) insert(item);
  }
  BinaryTree(const BinaryTree &other) : root_(nullptr), size_(0) {
    *this = other;
  }
  BinaryTree(BinaryTree &&other) noexcept
      : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  ~BinaryTree() { clear(); }

  void merge(BinaryTree<Key, Compare> &other) {
    for (auto it = other.begin(); it != other.end();) {
      auto new_node = new Node(*it);
      auto next_it = it;
      ++next_it;
      if (InsertHelper(new_node))
        other.erase(it);
      else
        delete new_node;
      it = next_it;
    }
  }

  iterator begin() {
    if (root_ == nullptr) return iterator(nullptr);
    Node *current = root_;
    while (current->left_ != nullptr) current = current->left_;
    return iterator(current);
  }
  const_iterator begin() const {
    if (root_ == nullptr) return const_iterator(nullptr);
    Node *current = root_;
    while (current->left_ != nullptr) current = current->left_;
    return const_iterator(current);
  }
  iterator end() noexcept { return iterator(nullptr); }
  const_iterator end() const noexcept { return const_iterator(nullptr); }

  void erase(iterator pos) {
    if (pos.node_ == nullptr) return;
    if (pos.node_->left_ == nullptr) {
      if (pos.node_->parent_ == nullptr) {
        root_ = pos.node_->right_;
        if (root_ != nullptr) root_->parent_ = nullptr;
      } else {
        if (pos.node_->parent_->left_ == pos.node_)
          pos.node_->parent_->left_ = pos.node_->right_;
        else
          pos.node_->parent_->right_ = pos.node_->right_;
        if (pos.node_->right_ != nullptr)
          pos.node_->right_->parent_ = pos.node_->parent_;
      }
      delete pos.node_;
      --size_;
    } else if (pos.node_->right_ == nullptr) {
      if (pos.node_->parent_ == nullptr) {
        root_ = pos.node_->left_;
        root_->parent_ = nullptr;
      } else {
        if (pos.node_->parent_->left_ == pos.node_) {
          pos.node_->parent_->left_ = pos.node_->left_;
          pos.node_->left_->parent_ = pos.node_->parent_;
        } else {
          pos.node_->parent_->right_ = pos.node_->left_;
          pos.node_->left_->parent_ = pos.node_->parent_;
        }
      }
      delete pos.node_;
      --size_;
    } else {
      Node *successor = pos.node_->right_;
      while (successor->left_ != nullptr) {
        successor = successor->left_;
      }
      auto new_node = new Node(successor->key_, pos.node_->left_,
                               pos.node_->right_, pos.node_->parent_);
      if (pos.node_->left_ != nullptr) pos.node_->left_->parent_ = new_node;
      if (pos.node_->right_ != nullptr) pos.node_->right_->parent_ = new_node;
      delete pos.node_;
      pos.node_ = new_node;
      if (new_node->parent_ == nullptr) root_ = new_node;
      erase(iterator(successor));
    }
  }

  void Delete(T key) { deleteHelper(key, root_); }

  Node *GetMax(Node node) const { return getMaxHelper(&node); }

  Node *GetMin(Node node) const { return getMinHelper(&node); }

  Key &at(const Key &key) & {
    auto it = find(key);
    if (it != end()) return (*it);
    throw std::out_of_range("Key not found in BinaryTree");
  }

  const Key &at(const Key &key) const & {
    auto it = find(key);
    if (it != end()) return (*it);
    throw std::out_of_range("Key not found in BinaryTree");
  }

  Node *getMinHelper(Node *node) const {
    if (node == nullptr) return nullptr;
    if (node->left_ == nullptr) return node;
    return getMinHelper(node->left_);
  }

  Node *getMaxHelper(Node *node) const {
    if (node == nullptr) return nullptr;
    if (node->right_ == nullptr) return node;
    return getMaxHelper(node->right_);
  }
  iterator find(T const &key) {
    auto cmp = Compare{};
    auto current = root_;
    while (current && (cmp(current->key_, key) || cmp(key, current->key_))) {
      if (cmp(current->key_, key))
        current = current->right_;
      else
        current = current->left_;
    }
    if (current == nullptr)
      return iterator(nullptr);
    else
      return iterator(current);
  }

  const_iterator find(const Key &key) const noexcept {
    auto cmp = Compare{};
    auto current = root_;
    while (current && (cmp(current->key_, key) || cmp(key, current->key_))) {
      if (cmp(current->key_, key))
        current = current->right_;
      else
        current = current->left_;
    }
    if (current == nullptr)
      return const_iterator(nullptr);
    else
      return const_iterator(current);
  }

  bool contains(const Key &key) const noexcept { return find(key) != end(); }

  void clear() noexcept {
    iterator it = begin();
    while (it != end()) {
      iterator current = it;
      ++it;
      erase(current);
    }
    root_ = nullptr;
  }

  Key &operator[](const Key &key) & noexcept {
    auto it = find(key);
    if (it != end()) return *it;
    auto new_node = new Node(key);
    InsertHelper(new_node);
    return new_node->key_;
  }

  BinaryTree &operator=(const BinaryTree &other) & {
    if (this == &other) return *this;
    clear();
    for (const auto &item : other) {
      insert_with_repetitions(item);
    }
    size_ = other.size_;
    return *this;
  }

  BinaryTree &operator=(BinaryTree &&other) & noexcept {
    if (this == &other) return *this;
    clear();
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
  }

  bool empty() const noexcept { return root_ == nullptr; }
  size_type size() const { return size_; }
  size_type max_size() const { return SIZE_MAX / sizeof(Node) / 2; }

  iterator insert_with_repetitions(const Key &key) {
    auto new_node = new Node(key);
    auto cmp = Compare{};
    if (root_ == nullptr) {
      root_ = new_node;
      ++size_;
      return iterator(new_node);
    }
    Node *current = root_;
    Node *parent = root_;
    while (current != nullptr) {
      parent = current;
      if (cmp(new_node->key_, current->key_))
        current = current->left_;
      else
        current = current->right_;
    }
    if (cmp(new_node->key_, parent->key_))
      parent->left_ = new_node;
    else
      parent->right_ = new_node;
    new_node->parent_ = parent;
    ++size_;
    return iterator(new_node);
  }

  std::pair<iterator, iterator> equal_range(const Key &key) noexcept {
    auto last = find(key);
    auto first = last;
    while (last != end()) {
      if (Compare{}(*last, key) || Compare{}(key, *last)) break;
      ++last;
    }
    return std::make_pair(first, last);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const Key &key) const noexcept {
    auto last = find(key);
    auto first = last;
    while (last != end()) {
      if (Compare{}(*last, key) || Compare{}(key, *last)) break;
      ++last;
    }
    return std::make_pair(first, last);
  }

  iterator lower_bound(const Key &key) noexcept {
    auto current = root_;
    while (current != nullptr && Compare{}(current->key_, key))
      current = current->right_;
    return iterator(current);
  }
  const_iterator lower_bound(const Key &key) const noexcept {
    auto current = root_;
    while (current != nullptr && Compare{}(current->key_, key))
      current = current->right_;
    return const_iterator(current);
  }
  iterator upper_bound(const Key &key) noexcept {
    auto current = root_;
    while (current != nullptr && !Compare{}(key, current->key_))
      current = current->right_;
    return iterator(current);
  }
  const_iterator upper_bound(const Key &key) const noexcept {
    auto current = root_;
    while (current != nullptr && !Compare{}(key, current->key_))
      current = current->right_;
    return const_iterator(current);
  }

  size_type count(const Key &key) const noexcept {
    auto it = find(key);
    size_type result = 0;
    while (it != end() && !(Compare{}(*it, key) || Compare{}(key, *it))) {
      ++result;
      ++it;
    }
    return result;
  }

  struct Node {
    Key key_;
    Node *left_;
    Node *right_;
    Node *parent_;
    explicit Node(Key key, Node *left = nullptr, Node *right = nullptr,
                  Node *parent = nullptr)
        : key_(key), left_(left), right_(right), parent_(parent) {}
  };

  Node *root_;
  size_type size_;

  std::pair<iterator, bool> insert(T const &val) {
    auto new_node = new Node(val);
    auto is_insert = InsertHelper(new_node);
    if (is_insert) {
      return std::make_pair(iterator(new_node), is_insert);
    } else {
      delete new_node;
      return std::make_pair(find(val), is_insert);
    }
  }

  bool InsertHelper(Node *new_node) {
    auto cmp = Compare{};
    if (root_ == nullptr) {
      root_ = new_node;
      ++size_;
      return true;
    }
    Node *current = root_;
    Node *parent = root_;
    while (current != nullptr) {
      parent = current;
      if (!(cmp(new_node->key_, current->key_) ||
            cmp(current->key_, new_node->key_)))
        return false;
      if (cmp(new_node->key_, current->key_))
        current = current->left_;
      else
        current = current->right_;
    }
    if (cmp(new_node->key_, parent->key_))
      parent->left_ = new_node;
    else
      parent->right_ = new_node;
    new_node->parent_ = parent;
    ++size_;
    return true;
  }
};
}  // namespace BinaryTree
#endif
