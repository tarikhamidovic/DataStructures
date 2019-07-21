// Tarik Hamidović
// Doubly linked list

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <iostream>
#include <iterator>
#include <initializer_list>

template<typename T>
class list {
  private:
    struct node;
    node* head_ = nullptr;
    node* tail_ = nullptr;
    size_t size_ = 0;
    void deleteList();
    void copyList(const list&);

  public:
    list() = default;
    list(std::initializer_list<T>);
    list(const list& other) {
      copyList(other);
    }
    list(list&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
      other.head_ = other.tail_ = nullptr;
    }
    list& operator=(const list&);
    list& operator=(list&&);
    ~list() { deleteList(); }
    class iterator;
    size_t size() { return size_; }
    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();
    T& front() { return head_ -> value_; }
    const T& front() const { return head_ -> value_; }
    T& back() { return tail_ -> value_; }
    const T& back() const { return tail_ -> value_; }
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(tail_ -> next_); }
    iterator erase(iterator);
    iterator insert(iterator, const T&);
    bool empty();
};

template<typename T>
struct list<T>::node {
  node() = default;
  node(node* inPrev, T inVal, node* inNext) : previous_{inPrev}, value_{inVal}, next_{inNext} {}
  node* previous_ = nullptr;
  node* next_ = nullptr;
  T value_ = 0;
};

template<typename T>
void list<T>::deleteList() {
  while (head_) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
  }
}

template<typename T>
void list<T>::copyList(const list& other) {
  if (size_ != 0) 
    deleteList();
  if (other.size_ != 0) {
    auto temp = other.head_ -> next_;
    head_ = new node(nullptr, other.head_ -> value_, nullptr);
    tail_ = head_;
    while (temp) {
      tail_ -> next_ = new node(tail_, temp -> value_, nullptr);
      tail_ = tail_ -> next_;
      temp = temp -> next_;
    }
  }
  size_ = other.size_;
}

template<typename T>
list<T>::list(std::initializer_list<T> iniList) {
  auto it = iniList.begin();
  head_ = new node(nullptr, *it, nullptr);
  tail_ = head_;
  it++;
  while (it != iniList.end()) {
    tail_ -> next_ = new node(tail_, *it, nullptr);
    tail_ = tail_ -> next_;
    it++;
  }
  size_ = iniList.size();
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other)
    copyList(other);
  return *this;
}

template<typename T>
list<T>& list<T>::operator=(list<T>&& other) {
  if (size_ != 0) 
    deleteList();
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  other.head_ = other.tail_ = nullptr;
  return *this;
}

template<typename T>
class list<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    node* p_ = nullptr;
    friend class list;
  
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
    iterator& operator--() {
      p_ = p_ -> previous_;
      return *this;
    }
    iterator operator--(int) {
      auto temp = *this;
      p_ = p_ -> previous_;
      return temp;
    }
    bool operator==(const iterator& other) { return p_ == other.p_; }
    bool operator!=(const iterator& other) { return p_ != other.p_; }
};

template<typename T>
void list<T>::push_back(const T& value) {
  if (size_ == 0) {
    head_ = new node(nullptr, value, nullptr);
    tail_ = head_;
  } 
  else {
    tail_ -> next_ = new node(tail_, value, nullptr);
    tail_ = tail_ -> next_;
  }
  size_++;
}

template<typename T>
void list<T>::push_front(const T& value) {
  if (size_ == 0) {
    push_back(value);
  } 
  else {
    head_ -> previous_ = new node(nullptr, value, head_);
    head_ = head_ -> previous_;
    size_++;
  }
}

template<typename T>
void list<T>::pop_back() {
  if (size_ != 0) {
    auto temp = tail_;
    tail_ = tail_ -> previous_;
    delete temp;
    size_--;
  }
}

template<typename T>
void list<T>::pop_front() {
  if (size_ != 0) {
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_--;
  }
}

template<typename T>
typename list<T>::iterator list<T>::erase(iterator position) {
  if (position == begin()) {
    pop_front();
    return begin();
  }
  if (position == iterator(tail_)) {
    pop_back();
    return end();
  }
  auto temp = position.p_;
  temp -> previous_ -> next_ = temp -> next_;
  temp -> next_ -> previous_ = temp -> previous_;
  auto ret = temp -> next_;
  delete temp;
  size_--;
  return ret;
}

template<typename T>
typename list<T>::iterator list<T>::insert(iterator position, const T& value) {
  if (size_ == 0 || position == end()) {
    push_back(value);
    return iterator(tail_);
  }
  if (position == begin()) {
    push_front(value);
    return iterator(head_);
  }
  auto temp = position.p_;
  auto temp2 = temp -> previous_;
  temp2 -> next_ = new node(temp2, value, temp);
  temp -> previous_ = temp2 -> next_;
  size_++;
  return iterator(temp2 -> next_);
}

template<typename T>
bool list<T>::empty() {
  if (size_ == 0)
    return true;
  else
    return false;
}

#endif
