// Doubly linked list
#ifndef _DOUBLYLIST_HPP_
#define _DOUBLYLIST_HPP_

#include<iostream>
#include<iterator>
#include<functional>

template<typename T>
struct Node {
  Node() = default;
  Node(Node* pre, T val, Node* nex) : previous_{pre}, value_{val}, next_{nex} {}
  Node* previous_ = nullptr;
  Node* next_ = nullptr;
  T value_ = 0;
};

template<typename T>
class List {
  public:
    List() = default;
    List(const List& otherList) {
      copyList(otherList);
    }
    List(List&& otherList) : head_{otherList.head_}, tail_{otherList.tail_}, size_{otherList.size_}{
      otherList.head_ = otherList.tail_ = nullptr;
    }
    List& operator=(const List& otherList) {
      if (this != &otherList) {
        if (size_ != 0) {
          deleteList();
        }
        if (otherList.size_ != 0) {
          copyList(otherList);
        }
        else {
          head_ = tail_ = nullptr;
        }
      }
      return *this;
    }
    List& operator=(List&& otherList) {
      deleteList();
      head_ = otherList.head_;
      tail_ = otherList.tail_;
      size_ = otherList.size_;
      otherList.head_ = otherList.tail_ = nullptr;
      return *this;
    }
    ~List() {
      deleteList();
    }
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
      public:
        iterator(Node<T>* p) : p_{p} {}
        Node<T>* getpointer() {
          return p_;
        }
        T& operator*() {
          return p_->value_;
        }
        iterator& operator++() {
          p_ = p_->next_;
          return *this;
        }
        iterator operator++(int) {
          auto temp = *this;
          p_ = p_->next_;
          return temp;
        }
        iterator& operator--() {
          p_ = p_->previous_;
          return *this;
        }
        iterator operator--(int) {
          auto temp = *this;
          p_ = p_->previous_;
          return temp;
        }
        bool operator==(iterator otherIterator) {
          return p_ == otherIterator.p_;
        }
        bool operator!=(iterator otherIterator) {
          return p_ != otherIterator.p_;
        }
      private:
        Node<T>* p_;
    };
    void push_back(const T& value) {
      if (size_ == 0) {
        head_ = new Node<T>(nullptr, value, nullptr);
        tail_ = head_;
      }
      else {
        tail_->next_ = new Node<T>(tail_, value, nullptr);
        tail_ = tail_->next_;
      }
      size_++;
    }
    void push_front(const T& value) {
      if (size_ == 0) {
        head_ = new Node<T>(nullptr, value, nullptr);
        tail_ = head_;
      }
      else {
        head_->previous_ = new Node<T>(nullptr, value, head_);
        head_ = head_->previous_;
      }
      size_++;
    }
    void pop_back() {
      if (size_ == 0) {
        throw std::out_of_range("The list is empty!");
      }
      auto temp = tail_;
      tail_ = tail_->previous_;
      tail_->next_ = nullptr;
      delete temp;
      size_--;
    }
    void pop_front() {
      if (size_ == 0) {
        throw std::out_of_range("The list is empty!");
      }
      auto temp = head_;
      head_ = head_->next_;
      head_->previous_ = nullptr;
      delete temp;
      size_--;
    }
    iterator begin() {
      return iterator(head_);
    }
    iterator end() {
      return iterator(tail_->next_);
    }
    void erase(iterator position) {
      if (position == end()) {
        throw std::invalid_argument("Trying to erase a nullptr!");
      }
      if (position == begin()) {
        pop_front();
        return;
      }
      if (position.getpointer() == tail_) {
        pop_back();
      }
      else {
        auto temp = position.getpointer();
        auto temp2 = temp -> previous_;
        temp -> next_ -> previous_ = temp2;
        temp2 -> next_ = temp -> next_;
        delete temp;
        size_--;
      }
    }
    void insert(iterator position, const T& val) {
      if (size_ == 0) {
        head_ = new Node<T>(nullptr, val, nullptr);
        tail_ = head_;
        size_++;
        return;
      }
      if (position == end()) {
        push_back(val);
        return;
      }
      if (position == begin()) {
        push_front(val);
      }
      else {
        auto temp = position.getpointer();
        auto temp2 = temp -> previous_;
        temp ->  previous_ = new Node<T>(temp2, val, temp);
        temp2 -> next_ = temp -> previous_;
      }
    }
    void for_each(std::function<void(const T&)> callback) {
      auto temp = head_;
      while (temp) {
        callback(temp->value_);
        temp = temp->next_;
      }
    }
  private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t size_ = 0;
    void copyList(const List& otherList) {
      if (otherList.size_ != 0) {
        auto temp = otherList.head_->next_;
        head_ = new Node<T>(nullptr, otherList.head_->value_, nullptr);
        tail_ = head_;
        while (temp) {
          tail_->next_ = new Node<T>(tail_, temp->value_, nullptr);
          tail_ = tail_->next_;
          temp = temp->next_;
        }
      }
      size_ = otherList.size_;
    }
    void deleteList() {
      while (head_) {
        auto temp = head_;
        head_ = head_->next_;
        delete temp;
      }
    }
};

#endif
