#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <iostream>

template<typename T>
struct node {
  node() = default;
  node(T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
class stack
{
public:
  stack() = default;
  stack(const stack& other) {
    copyStack(other);
  }
  stack(stack&& other) : head_{other.head_}, size_{other.size_} {
    other.head_ = nullptr;
  }
  stack& operator=(const stack& other) {
    if (this != &other) {
      copyStack(other);
    }
    return *this;
  }
  stack& operator=(stack&& other) {
    if (size_ != 0) {
      deleteStack();
    }
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = nullptr;
    return *this;
  }
  ~stack() {
    deleteStack();
  }
  void push(const T& newValue) {
    auto temp = new node<T>(newValue, head_);
    head_ = temp;
    size_++;
  }
  void pop() {
    if (size_ != 0) {
      auto temp = head_;
      head_ = head_ -> next_;
      delete temp;
      size_--;
    }
  }
  T& top() {
    return head_ -> value_;
  }
  const T& top() const {
    return head_ -> value_;
  }
  size_t size() {
    return size_;
  }
  bool empty() {
    if (size_ == 0) return true;
    return false;
  }
private:
  node<T>* head_ = nullptr;
  size_t size_ = 0;
  void deleteStack() {
    while (head_) {
      auto temp = head_;
      head_ = head_ -> next_;
      delete temp;
    }
  }
  void copyStack(const stack& other) {
    if (size_ != 0) {
      deleteStack();
    }
    if (other.size_ != 0) {
      auto temp = other.head_ -> next_;
      head_ = new node<T>(other.head_ -> value_, nullptr);
      auto tail = head_;
      while (temp) {
        tail -> next_ = new node<T>(temp -> value_, nullptr);
        tail = tail -> next_;
        temp = temp -> next_;
      }
    }
    size_ = other.size_;
  }
};

#endif 
