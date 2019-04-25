#ifndef _LIST_HPP_
#define _LIST_HPP_

#include<iostream>
#include<iterator>
#include<functional>

template<typename T>
struct Node {
  Node() = default;
  Node(Node* p, T v, Node* n) : previous_{p}, value_{v}, next_{n} {}
  Node* previous_ = nullptr;
  T value_ = 0;
  Node* next_ = nullptr;
};

template<typename T>
class List {
  public:
    List() = default;
    List(const List& otherList) {
      if (otherList.size_ != 0) {
        if (size_ != 0) {
          deleteList();
        }
        copyList(otherList);
      }
      else {
        if (size_ != 0) {
          deleteList();
        }
        head_ = tail_ = nullptr;
      }
    }
    List(List&& otherList) : head_{otherList.head_}, tail_{otherList.tail_}, size_{otherList.size_} {
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
      if (size_ != 0) {
        deleteList();
      }
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
        bool operator==(const iterator& otherIterator) {
          return p_ == otherIterator.p_;
        }
        bool operator!=(const iterator& otherIterator) {
          return p_ != otherIterator.p_;
        }
        Node<T>* getpointer() {
          return p_;
        }
      private:
        Node<T>* p_;
    };
    iterator begin() {
      return iterator(head_);
    }
    iterator end() {
      return iterator(tail_ -> next_);
    }
   void add(const T& val) {
      if (size_ == 0) {
        head_ = new Node<T>(nullptr, val, nullptr);
        tail_ = head_;
      }
      else {
        tail_ -> next_ = new Node<T>(tail_, val, nullptr);
        tail_ = tail_ -> next_;
      }
      size_++;
      auto temp1 = head_;
      auto temp2 = tail_;
      while (temp1 != temp2) {
        while (temp1 != temp2) {
          if (temp1 -> value_ > temp1 -> next_ -> value_) {
            std::swap(temp1 -> value_, temp1 -> next_ -> value_);
          }
          temp1 = temp1 -> next_;
        }
        temp1 = head_;
        temp2 = temp2 -> previous_;
      }
    }
    void remove(iterator position) {
      auto temp = position.getpointer();
      if (size_ == 0) {
        return;
      }
      if (size_ == 1) {
        delete head_;
        head_ = tail_ = nullptr;
        size_--;
        return;
      }
      if (temp == head_) {
        head_ = head_ -> next_;
        head_ -> previous_ = nullptr;
        delete temp;
        size_--;
        return;
      }
      if (temp == tail_) {
        tail_ = tail_ -> previous_;
        tail_ -> next_ = nullptr;
        delete temp;
      }
      else {
        auto temp2 = temp -> previous_;
        temp2 -> next_ = temp -> next_;
        temp -> next_ -> previous_ = temp2;
        delete temp;
      }
      size_--;
    }
    iterator find(std::function<bool(const T&)> predicate) {
      auto temp = head_;
      while (temp) {
        if (predicate(temp -> value_)) {
          return iterator(temp);
        }
        temp = temp -> next_;
      }
      return end();
    }
    void print() {
      auto temp = head_;
      while (temp) {
        std::cout << temp -> value_ << std::endl;
        std::cout << "------------------------------------" << std::endl;
        temp = temp -> next_;
      }
    }
    size_t size() {
      return size_;
    }
  private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t size_ = 0;
    void copyList(const List& otherList) {
      auto temp = otherList.head_ -> next_;
      head_ = new Node<T>(nullptr, otherList.head_ -> value_, nullptr);
      tail_ = head_;
      while (temp) {
        tail_ -> next_ = new Node<T>(tail_, temp -> value_, nullptr);
        tail_ = tail_ -> next_;
        temp = temp -> next_;
      }
      size_ = otherList.size_;
    }
    void deleteList() {
      while (head_) {
        auto temp = head_;
        head_ = head_ -> next_;
        delete temp;
      }
      size_ = 0;
    }
};

#endif
