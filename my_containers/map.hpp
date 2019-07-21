#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <iostream>
#include <iterator>
#include <stack>

template<typename K, typename V>
class map {
  private:
    struct node;
    node* root_ = nullptr;
    size_t size_ = 0;
    void copyMap(node*&, node*);
    void deleteMap(node*);
    node* maxKeyNode(node*);
    void deleteNode(node*&, K);

  public:
    map() = default;
    map(const map& other) : size_{other.size_} {
      copyMap(root_, other.root_);
    }
    map(map&& other) : root_{other.root_}, size_{other.size_} {
      other.root_ = nullptr;
    }
    map& operator=(const map&);
    map& operator=(map&&);
    ~map() { deleteMap(root_); }
    class iterator;
    iterator begin() { return iterator(root_); }
    iterator end() { return iterator(nullptr); }
    size_t size() { return size_; }
    V& operator[](const K&);
    iterator find(const K&);
    void erase(const K&);
    bool empty();
};

template<typename K, typename V>
struct map<K,V>::node {
  node() = default;
  node(K inKey, V inValue, node* inLeft, node* inRight) : key_{inKey}, value_{inValue}, left_{inLeft}, right_{inRight} {}
  K key_ = 0;
  V value_ = 1;
  node* left_ = nullptr;
  node* right_ = nullptr;
};

template<typename K, typename V>
void map<K,V>::copyMap(node*& root, node* temp) {
  if (temp == nullptr) 
    return;
  root = new node(temp -> key_, temp -> value_, nullptr, nullptr);
  copyMap(root -> left_, temp -> left_);
  copyMap(root -> right_, temp -> right_);
}

template<typename K, typename V>
void map<K,V>::deleteMap(node* temp) {
  if (temp == nullptr) 
    return;
  deleteMap(temp -> left_);
  deleteMap(temp -> right_);
  delete temp;
}

template<typename K, typename V>
typename map<K,V>::node* map<K,V>::maxKeyNode(node* temp) {
  while (temp -> right_ != nullptr) {
    temp = temp -> right_;
  }
  return temp;
}

template<typename K, typename V>
void map<K,V>::deleteNode(node*& root, K key) {
  if (root == nullptr) 
    return;
  if (key < root -> key_) 
    deleteNode(root -> left_, key);
  else if (key > root -> key_)
    deleteNode(root -> right_, key);
  else {
    if (root -> left_ == nullptr && root -> right_ == nullptr) {
      delete root;
      size_--;
      root = nullptr;
    }
    else if (root -> left_ && root -> right_) {
      auto temp = maxKeyNode(root -> left_);
      root -> key_ = temp -> key_;
      deleteNode(root -> left_, temp -> key_);
    }
    else {
      auto child = (root -> left_) ? root -> left_ : root -> right_;
      auto curr = root;
      root = child;
      delete curr;
      size_--;
    }
  }
}

template<typename K, typename V>
map<K,V>& map<K,V>::operator=(const map<K,V>& other) {
  if (this != &other) {
    if (root_ != nullptr) 
      deleteMap(root_);
    copyMap(root_, other.root_);
    size_ = other.size_;
  }
  return *this;
}

template<typename K, typename V>
map<K,V>& map<K,V>::operator=(map<K,V>&& other) {
  if (root_ != nullptr) 
    deleteMap(root_);
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  return *this;
}

template<typename K, typename V>
class map<K,V>::iterator : public std::iterator<std::bidirectional_iterator_tag, K> {
  private:
    node* p_ = nullptr;
    std::stack<node*> iterStack;
    
  public:
    iterator(node* p) {
      node* root = p;
      while (root != nullptr) {
        iterStack.push(root);
        root = root -> left_;
      }
      if (iterStack.size() > 0) {
        p_ = iterStack.top();
        iterStack.pop();
      }
      else {
        p_ = nullptr;
      }
    }
    const K& first() const { return p_ -> key_; }
    V& second() { return p_ -> value_; }
    iterator& operator++() {
      if (p_ -> right_) {
        iterStack.push(p_ -> right_);
        if (p_ -> right_ -> left_) 
          iterStack.push(p_ -> right_ -> left_);
      }
      if (iterStack.size() == 0) {
        p_ = nullptr;
        return *this;
      }
      p_ = iterStack.top();
      iterStack.pop();
      return *this;
    }
    iterator operator++(int) {
      auto temp = *this;
      if (p_ -> right_) {
        iterStack.push(p_ -> right_);
        if (p_ -> right_ -> left_) 
          iterStack.push(p_ -> right_ -> left_);
      }
      if (iterStack.size() == 0) {
        p_ = nullptr;
        return *this;
      }
      p_ = iterStack.top();
      iterStack.pop();
      return temp;
    }
    bool operator==(const iterator& other) { return p_ == other.p_; }
    bool operator!=(const iterator& other) { return p_ != other.p_; }
};

template<typename K, typename V>
V& map<K,V>::operator[](const K& inKey) {
  if (root_ == nullptr) {
    root_ = new node(inKey, 1,  nullptr, nullptr);
    size_++;
    return root_ -> value_;
  }
  auto tempChild = root_;
  node* tempParent = nullptr;
  while (tempChild != nullptr) {
    tempParent = tempChild;
    if (inKey == tempChild -> key_) 
      return tempChild -> value_;
    if (inKey < tempChild -> key_) 
      tempChild = tempChild -> left_;
    else
      tempChild = tempChild -> right_;
  }
  if (inKey < tempParent -> key_) {
    tempParent -> left_ = new node(inKey, 1, nullptr, nullptr);
    size_++;
    return tempParent -> left_ -> value_;
  }
  else {
    tempParent -> right_ = new node(inKey, 1, nullptr, nullptr);
    size_++;
    return tempParent -> right_ -> value_;
  }
}

template<typename K, typename V>
typename map<K,V>::iterator map<K,V>::find(const K& inKey) {
  auto temp = root_;
  while (temp) {
    if (temp -> key_ == inKey) 
      return iterator(temp);
    else if (temp -> key_ < inKey)
      temp = temp -> right_;
    else
      temp = temp -> left_;
  }
  return end();
}

template<typename K, typename V>
void map<K,V>::erase(const K& key) {
  deleteNode(root_, key);
}

template<typename K, typename V>
bool map<K,V>::empty() {
  if (size_ == 0) 
    return true;
  else
    return false;
}

#endif
