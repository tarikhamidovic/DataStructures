// Tarik Hamidović
// Queue

#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <iostream>

template<typename T>
struct node {
  node () = default;
  node (T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
class queue
{
public:
  queue() = default;
  queue(const queue& other) {
    copyqueue(other);
  }
  queue(queue&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = other.tail_ = nullptr;
  }
  queue& operator=(const queue& other) {
    if (this != &other) {
      if (size_ != 0) 
        deletequeue();
      copyqueue(other);
    }
    return *this;
  }
  queue& operator=(queue&& other) {
    if (size_ != 0) 
      deletequeue();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    return *this;
  }
  ~queue() {
    deletequeue();
  }
  void push(const T& newVal) {
    if (size_ == 0) {
      head_ = new node<T>(newVal, nullptr);
      tail_ = head_;
    }
    else {
      tail_ -> next_ = new node<T>(newVal, nullptr);
      tail_ = tail_ -> next_;
    }
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
  T& front() {
    return head_ -> value_;
  }
  const T& front() const {
    return head_ -> value_;
  }
  T& back() {
    return tail_ -> value_;
  }
  const T& back() const {
    return tail_ -> value_;
  }
  bool empty() {
    if (size_ == 0) return true;
    return false;
  }
  size_t size() {
    return size_;
  }
private:
  node<T>* head_ = nullptr;
  node<T>* tail_ = nullptr;
  size_t size_ = 0;
  void deletequeue() {
    while (head_) {
      auto temp = head_;
      head_ = head_ -> next_;
      delete temp;
    }
  }
  void copyqueue(const queue& other) {
    if (other.size_ != 0) {
      auto temp = other.head_ -> next_;
      head_ = new node<T>(other.head_ -> value_, nullptr);
      tail_ = head_;
      while (temp) {
        tail_ -> next_ = new node<T>(temp -> value_, nullptr);
        tail_ = tail_ -> next_;
        temp = temp -> next_;
      }
    }
    size_ = other.size_;
  }
};

#endif
