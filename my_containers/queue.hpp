/******************************************************************************
* File:             queue.hpp
*
* Author:           Tarik Hamidović  
* Created:          07/20/19 
* Description:      Queue implemented like a linked list
*****************************************************************************/


#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <iostream>

template<typename T>
class queue {
  private:
    struct node;
    node* head_ = nullptr;
    node* tail_ = nullptr;
    size_t size_ = 0;
    void deleteQueue();
    void copyQueue(const queue&);

  public:
    queue() = default;
    queue(const queue& other) {
      copyQueue(other);
    }
    queue(queue&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
      other.head_ = other.tail_ = nullptr;
    }
    queue& operator=(const queue&);
    queue& operator=(queue&&);
    ~queue() { deleteQueue(); }
    void push(const T&);
    void pop();
    T& front() { return head_ -> value_; }
    const T& front() const { return head_ -> value_; }
    T& back() { return tail_ -> value_; }
    const T& back() const { return tail_ -> value_; }
    bool empty();
    size_t size() { return size_; }
};

template<typename T>
struct queue<T>::node {
  node() = default;
  node(T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
void queue<T>::deleteQueue() {
  while (head_) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
  }
}

template<typename T>
void queue<T>::copyQueue(const queue& other) {
  if (other.size_ != 0) {
    auto temp = other.head_ -> next_;
    head_ = new node(other.head_ -> value_, nullptr);
    tail_ = head_;
    while (temp) {
      tail_ -> next_ = new node(temp -> value_, nullptr);
      tail_ = tail_ -> next_;
      temp = temp -> next_;
    }
  }
  size_ = other.size_;
}

template<typename T>
queue<T>& queue<T>::operator=(const queue& other) {
  if (this != &other) {
    if (size_ != 0) 
      deleteQueue();
    copyQueue(other);
  }
  return *this;
}

template<typename T>
queue<T>& queue<T>::operator=(queue&& other) {
  if (size_ != 0) 
    deleteQueue();
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  other.head_ = other.tail_ = nullptr;
  return *this;
}

template<typename T>
void queue<T>::push(const T& newVal) {
  if (size_ == 0) {
    head_ = new node(newVal, nullptr);
    tail_ = head_;
  }
  else {
    tail_ -> next_ = new node(newVal, nullptr);
    tail_ = tail_ -> next_;
  }
  size_++;
}

template<typename T>
void queue<T>::pop() {
  if (size_ != 0) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_--;
  }
}

template<typename T>
bool queue<T>::empty() {
  if (size_ == 0) 
    return true;
  else 
    return false;
}

#endif
