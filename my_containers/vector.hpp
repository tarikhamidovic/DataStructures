// Tarik Hamidović
// Vector

#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

template<typename T>
class vector {
  private:
    size_t cap_ = 10;
    size_t size_ = 0;
    T* ptr_ = nullptr;
    void realocate();

  public:
    vector() : ptr_{new T[cap_]} {}
    vector(std::initializer_list<T> iniList) : cap_{iniList.size()}, size_{iniList.size()}, ptr_{new T[cap_]} {
      std::copy(iniList.begin(), iniList.end(), ptr_);
    }
    vector(const vector& other) : cap_{other.cap_}, size_{other.size_}, ptr_{new T[cap_]} {
      std::copy(other.ptr_, other.ptr_ + other.size_, ptr_);
    }
    vector(vector&& other) : cap_{other.cap_}, size_{other.size_}, ptr_{other.ptr_} { other.ptr_ = nullptr; }
    vector& operator=(const vector&);
    vector& operator=(vector&&);
    ~vector() { delete [] ptr_; }
    using iterator = T*;
    iterator begin() { return iterator(ptr_); }
    iterator end() { return iterator(ptr_ + size_); }
    T& operator[](size_t index) { return ptr_[index]; }
    const T& operator[](size_t index) const { return ptr_[index]; }
    T& at(size_t);
    const T& at(size_t) const;
    void push_back(const T&);
    size_t size() { return size_; }
    void pop_back() { if (size_ != 0) size_--; }
    T& back() { return ptr_[size_ - 1]; }
    const T& back() const { return ptr_[size_ - 1]; }
    T& front() { return ptr_[0]; }
    const T& front() const { return ptr_[0]; }
    iterator erase(iterator);
    iterator insert(iterator, const T&);
    size_t capacity() { return cap_; }
    bool empty();
};

template<typename T>
void vector<T>::realocate() {
  cap_ *= 2;
  auto temp = new T[cap_];
  std::copy(ptr_, ptr_ + size_, temp);
  delete [] ptr_;
  ptr_ = temp;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    delete [] ptr_;
    cap_ = other.cap_;
    size_ = other.size_;
    ptr_ = new T[cap_];
    std::copy(other.ptr_, other.ptr_ + other.size_, ptr_);
  }
  return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& other) {
  delete [] ptr_;
  cap_ = other.cap_;
  size_ = other.size_;
  ptr_ = other.ptr_;
  other.ptr_ = nullptr;
  return *this;
}

template<typename T>
T& vector<T>::at(size_t index) {
    if (index >= size_) 
      throw std::out_of_range("Index goes out of range");
    return ptr_[index];
}

template<typename T>
const T& vector<T>::at(size_t index) const {
    if (index >= size_) 
      throw std::out_of_range("Index goes out of range");
    return ptr_[index];
}

template<typename T>
void vector<T>::push_back(const T& value) {
  if (cap_ == size_) 
    realocate();
  ptr_[size_++] = value;
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator it) {
  if (it == end() - 1) {
    pop_back();
    return it - 1;
  }
  for (auto iter = it; iter != end() - 1; iter++)
    std::swap(*iter, *(iter + 1));
  size_--;
  return it;
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const T& value) {
  int difference = pos - begin();
  push_back(value);
  pos = begin() + difference;
  for (auto it = end() - 1; it != pos; it--) 
    std::swap(*it, *(it - 1));
  return pos;
}

template<typename T>
bool vector<T>::empty() {
  if (size_ == 0) 
    return true;
  else
    return false;
}

#endif
