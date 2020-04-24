/******************************************************************************
* File:             stack.hpp
*
* Author:           Tarik Hamidović  
* Created:          07/02/19 
* Description:      Stack implemented like a linked list
*****************************************************************************/

#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <iostream>

template<typename T>
class stack {
  private:
    struct node;
    node* head_ = nullptr;
    size_t size_ = 0;
    void deleteStack();
    void copyStack(const stack&);

  public:
    stack() = default;
    stack(const stack& other) {
      copyStack(other);
    }
    stack(stack&& other) : head_{other.head_}, size_{other.size_} {
      other.head_ = nullptr;
    }
    stack& operator=(const stack&);
    stack& operator=(stack&&);
    ~stack() { deleteStack(); }
    void push(const T&);
    void pop();
    T& top() { return head_ -> value_; }
    const T& top() const { return head_ -> value_; }
    size_t size() { return size_; }
    bool empty();
};

template<typename T>
struct stack<T>::node {
  node() = default;
  node(T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
void stack<T>::deleteStack() {
  while (head_) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
  }
}

template<typename T>
void stack<T>::copyStack(const stack& other) {
  if (size_ != 0) 
    deleteStack();
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
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) 
    copyStack(other);
  return *this;
}

template<typename T>
stack<T>& stack<T>::operator=(stack&& other) {
  if (size_ != 0) 
    deleteStack();
  head_ = other.head_;
  size_ = other.size_;
  other.head_ = nullptr;
  return *this;
}

template<typename T>
void stack<T>::push(const T& newValue) {
  auto temp = new node(newValue, head_);
  head_ = temp;
  size_++;
}

template<typename T>
void stack<T>::pop() {
  if (size_ != 0) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_--;
  }
}

template<typename T>
bool stack<T>::empty() {
  if (size_ == 0) 
    return true;
  else
    return false;
}

#endif
