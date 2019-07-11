#ifndef _FORWARD_LIST_HPP_
#define _FORWARD_LIST_HPP_ 

#include <iostream>
#include <iterator>

template<typename T>
struct node {
  node() = default;
  node(T inVal, node* inNext) : value_{inVal}, next_{inNext} {}
  T value_ = 0;
  node* next_ = nullptr;
};

template<typename T>
class forward_list
{
public:
  forward_list() = default;
  forward_list(const forward_list& other) {
    copylist(other);
  }
  forward_list(forward_list&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = other.tail_ = nullptr;
  }
  forward_list& operator=(const forward_list& other) {
    if (this != &other) {
      copylist(other);
    }
    return *this;
  }
  forward_list& operator=(forward_list&& other) {
    if (size_ != 0) {
      deletelist();
    }
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    return *this;
  }
  ~forward_list() {
    deletelist();
  }
  class iterator : public std::iterator<std::forward_iterator_tag, T> {
  public:
    iterator(node<T>* p) : p_{p} {}
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
    bool operator==(const iterator& other) {
      return p_ == other.p_;
    }
    bool operator!=(const iterator& other) {
      return p_ != other.p_;
    }
  private:
    node<T>* p_;
  };
  iterator begin() {
    return iterator(head_);
  }
  iterator end() {
    return iterator(tail_ -> next_);
  }
  void push_back(const T& newValue) {
    if (size_ == 0) {
      tail_ = new node<T>(newValue, nullptr);
      head_ = tail_;
    }
    else {
      tail_ -> next_ = new node<T>(newValue, nullptr);
      tail_ = tail_ -> next_;
    }
    size_++;
  }
  void push_front(const T& newValue) {
    if (size_ == 0) {
      head_ = new node<T>(newValue, nullptr);
      tail_ = head_;
    }
    else {
      auto temp = new node<T>(newValue, head_);
      head_ = temp;
    }
    size_++;
  }
  void pop_front() {
    if (size_ != 0) {
      auto temp = head_;
      head_ = head_ -> next_;
      delete temp;
      size_--;
    }
  }
  iterator erase(iterator position) {
    if (position == begin()) {
      pop_front();
      return begin();
    }
    auto temp = head_;
    auto temp2 = temp -> next_;
    while (temp2) {
      if (iterator(temp2) == position) {
        temp -> next_ = temp2 -> next_;
        delete temp2;
        size_--;
        if (temp -> next_ == nullptr) 
          tail_ = temp;
        return iterator(temp -> next_);
      }
      temp = temp -> next_;
      temp2 = temp2 -> next_;
    }
    return end();
  }
  iterator insert(iterator position, const T& newValue) {
    if (position == begin()) {
      push_front(newValue);
      return begin();
    }
    auto temp = head_;
    auto temp2 = temp -> next_;
    while (temp2) {
      if (iterator(temp2) == position) {
        temp -> next_ = new node<T>(newValue, temp2);
        size_++;
        return iterator(temp -> next_);
      }
      temp = temp -> next_;
      temp2 = temp2 -> next_;
    }
    temp -> next_ = new node<T>(newValue, nullptr);
    size_++;
    tail_ = temp -> next_;
    return iterator(temp -> next_);
  }
  size_t size() {
    return size_;
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
  void clear() {
    deletelist();
  }
private:
  node<T>* head_ = nullptr;
  node<T>* tail_ = nullptr;
  size_t size_ = 0;
  void deletelist() {
    while (head_) {
      auto temp = head_;
      head_ = head_ -> next_;
      delete temp;
    }
    size_ = 0;
  }
  void copylist(const forward_list& other) {
    if (size_ != 0) {
      deletelist();
    }
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
