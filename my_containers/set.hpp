// Tarik Hamidović
// Set (Binary Search Tree)

#ifndef _SET_HPP_
#define _SET_HPP_

#include <iostream>
#include <iterator>
#include <stack>
#include <initializer_list>

template<typename T>
class set {
  private:
    struct node;
    node* root_ = nullptr;
    size_t size_ = 0;
    void copySet(node*&, node*);
    void deleteSet(node*);
    node* maxValNode(node*);
    void deleteNode(node*&, T);

  public:
    set() = default;
    set(std::initializer_list<T>);
    set(const set& other) : size_{other.size_} {
      copySet(root_, other.root_);
    }
    set(set&& other) : root_{other.root_}, size_{other.size_} {
      other.root_ = nullptr;
    }
    set& operator=(const set&);
    set& operator=(set&&);
    ~set() { deleteSet(root_); }
    class iterator;
    iterator begin() { return iterator(root_); }
    iterator end() { return iterator(nullptr); }
    size_t size() { return size_; }
    bool find(const T&);
    void insert(const T&);
    void erase(iterator);
    bool empty();
};

template<typename T>
struct set<T>::node {
  node() = default;
  node(T inValue, node* inLeft, node* inRight) : value_{inValue}, left_{inLeft}, right_{inRight} {}
  T value_ = 0;
  node* left_ = nullptr;
  node* right_ = nullptr;
};

template<typename T>
void set<T>::copySet(node*& root, node* temp) {
  if (temp == nullptr) 
    return;
  root = new node(temp -> value_, nullptr, nullptr);
  copySet(root -> left_, temp -> left_);
  copySet(root -> right_, temp -> right_);
}

template<typename T>
void set<T>::deleteSet(node* temp) {
  if (temp == nullptr) 
    return;
  deleteSet(temp -> left_);
  deleteSet(temp -> right_);
  delete temp;
}

template<typename T>
typename set<T>::node* set<T>::maxValNode(node* temp) {
  while (temp -> right_ != nullptr) {
    temp = temp -> right_;
  }
  return temp;
}

template<typename T>
void set<T>::deleteNode(node*& root, T val) {
  if (root == nullptr) 
    return;
  if (val < root -> value_) 
    deleteNode(root -> left_, val);
  else if (val > root -> value_)
    deleteNode(root -> right_, val);
  else {
    if (root -> left_ == nullptr && root -> right_ == nullptr) {
      delete root;
      size_--;
      root = nullptr;
    }
    else if (root -> left_ && root -> right_) {
      auto temp = maxValNode(root -> left_);
      root -> value_ = temp -> value_;
      deleteNode(root -> left_, temp -> value_);
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

template<typename T>
set<T>::set(std::initializer_list<T> iniList) {
  for (auto it = iniList.begin(); it != iniList.end(); it++) {
    insert(*it);
  }
  size_ = iniList.size();
}

template<typename T>
set<T>& set<T>::operator=(const set<T>& other) {
  if (this != &other) {
    if (root_ != nullptr) 
      deleteSet(root_);
    copySet(root_, other.root_);
    size_ = other.size_;
  }
  return *this;
}

template<typename T>
set<T>& set<T>::operator=(set<T>&& other) {
  if (root_ != nullptr) 
    deleteSet(root_);
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  return *this;
}

template<typename T>
class set<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
    T& operator*() { return p_ -> value_; }
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

template<typename T>
bool set<T>::find(const T& val) {
  auto temp = root_;
  while (temp) {
    if (temp -> value_ == val) 
      return true;
    else if (temp -> value_ < val)
      temp = temp -> right_;
    else
      temp = temp -> left_;
  }
  return false;
}

template<typename T>
void set<T>::insert(const T& newValue) {
  if (root_ == nullptr) {
    root_ = new node(newValue, nullptr, nullptr);
    size_++;
    return;
  }
  auto tempChild = root_;
  node* tempParent = nullptr;
  while (tempChild != nullptr) {
    tempParent = tempChild;
    if (newValue == tempChild -> value_) 
      return;
    if (newValue < tempChild -> value_) 
      tempChild = tempChild -> left_;
    else
      tempChild = tempChild -> right_;
  }
  if (newValue < tempParent -> value_) 
    tempParent -> left_ = new node(newValue, nullptr, nullptr);
  else
    tempParent -> right_ = new node(newValue, nullptr, nullptr);
  size_++;
}

template<typename T>
void set<T>::erase(iterator position) {
  deleteNode(root_, *position);
}

template<typename T>
bool set<T>::empty() {
  if (size_ == 0) 
    return true;
  else
    return false;
}

#endif
