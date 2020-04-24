/******************************************************************************
* File:             forward_list.hpp
*
* Author:           Tarik Hamidović  
* Created:          07/18/19 
* Description:      STL-like forward list
*****************************************************************************/

#ifndef _FORWARD_LIST_HPP_
#define _FORWARD_LIST_HPP_

#include <iostream>
#include <iterator>
#include <initializer_list>

template<typename T>
class forward_list {
  private:
    struct node;
    node* head_ = nullptr;
    size_t size_ = 0;
    void deleteList();
    void copyList(const forward_list&);

  public:
    forward_list() = default;
    forward_list(std::initializer_list<T>);
    forward_list(const forward_list& other) {
      copyList(other);
    }
    forward_list(forward_list&& other) : head_{other.head_}, size_{other.size_} {
      other.head_ = nullptr;
    }
    forward_list& operator=(const forward_list&);
    forward_list& operator=(forward_list&&);
    ~forward_list() { deleteList(); }
    class iterator;
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(); }
    void push_front(const T&);
    void pop_front();
    iterator erase_after(iterator);
    iterator insert_after(iterator, const T&);
    size_t size() { return size_; }
    T& front() { return head_ -> value_; }
    const T& front() const { return head_ -> value_; }
    bool empty();
    void clear() { deleteList(); }
};

template<typename T>
struct forward_list<T>::node {
  node() = default;
  node(T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
void forward_list<T>::deleteList() {
  while (head_) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
  }
  size_ = 0;
}

template<typename T>
void forward_list<T>::copyList(const forward_list& other) {
  if (size_ != 0) 
    deleteList();
  if (other.size_ != 0) {
    auto temp = other.head_ -> next_;
    head_ = new node(other.head_ -> value_, nullptr);
    auto tail = head_;
    while (temp) {
      tail -> next_ = new node(temp -> value_, nullptr);
      tail = tail -> next_;
      temp = temp -> next_;
    }
  }
  size_ = other.size_;
}

template<typename T>
forward_list<T>::forward_list(std::initializer_list<T> iniList) {
  auto it = iniList.begin();
  head_ = new node(*it, nullptr);
  auto temp = head_;
  it++;
  while (it != iniList.end()) {
    temp -> next_ = new node(*it, nullptr);
    temp = temp -> next_;
    it++;
  }
  size_ = iniList.size();
}

template<typename T>
forward_list<T>& forward_list<T>::operator=(const forward_list& other) {
  if (this != &other) 
    copyList(other);
  return *this;
}

template<typename T>
forward_list<T>& forward_list<T>::operator=(forward_list&& other) {
  if (size_ != 0) 
    deleteList();
  head_ = other.head_;
  size_ = other.size_;
  other.head_ = nullptr;
  return *this;
}

template<typename T>
class forward_list<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
  private:
    node* p_ = nullptr;

  public:
    iterator() = default;
    iterator(node* p) : p_{p} {}
    T& operator*() { 
      return p_ -> value_; 
    }
    iterator& operator++() {
      p_ = p_ -> next_;
      return *this;
    }
    iterator operator++(int) {
      auto temp = *this;
      p_ = p_ -> next_;
      return temp;
    }
    bool operator==(const iterator& other) const { return p_ == other.p_; }
    bool operator!=(const iterator& other) const { return p_ != other.p_; }
};

template<typename T>
void forward_list<T>::push_front(const T& newValue) {
  if (size_ == 0) {
    head_ = new node(newValue, nullptr);
  }
  else {
    auto temp = new node(newValue, head_);
    head_ = temp;
  }
  size_++;
}

template<typename T>
void forward_list<T>::pop_front() {
  if (size_ != 0) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_--;
  }
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::erase_after(iterator position) {
  auto temp = head_;
  while (temp) {
    if (iterator(temp) == position) {
      auto toDelete = temp -> next_;
      temp -> next_ = toDelete -> next_;
      delete toDelete;
      size_--;
      return iterator(temp -> next_);
    }
    temp = temp -> next_;
  }
  return iterator(temp);
}

template<typename T>
typename forward_list<T>::iterator forward_list<T>::insert_after(iterator position, const T& newValue) {
  auto temp = head_;
  while (temp) {
    if (iterator(temp) == position) {
      auto newNode = new node(newValue, temp -> next_);
      temp -> next_ = newNode;
      size_++;
      return iterator(newNode);
    }
    temp = temp -> next_;
  }
  return iterator(temp);
}

template<typename T>
bool forward_list<T>::empty() {
  if (size_ == 0) 
    return true;
  else
    return false;
}

#endif
