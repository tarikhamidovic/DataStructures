// Vector (array)
#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include<iostream>
#include<iterator>
#include<stdexcept>
#include<algorithm>

template<typename T>
class Vector {
  public:
    Vector() = default;
    Vector(const Vector& otherVector) : cap_{otherVector.cap_}, size_{otherVector.size_}, ptr_{new T[cap_]} {
      std::copy(otherVector.ptr_, otherVector.ptr_ + otherVector.size_, ptr_);
    }
    Vector(Vector&& otherVector) : cap_{otherVector.cap_}, size_{otherVector.size_}, ptr_{otherVector.ptr_} {
      otherVector.ptr_ = nullptr;
    }
    Vector& operator=(const Vector& otherVector) {
      if(this != &otherVector) {
        delete [] ptr_;
        cap_ = otherVector.cap_;
        size_ = otherVector.size_;
        ptr_ = new T[cap_];
        std::copy(otherVector.ptr_, otherVector.ptr_ + otherVector.size_, ptr_);
      }
      return *this;
    }
    Vector& operator=(Vector&& otherVector) {
      delete [] ptr_;
      cap_ = otherVector.cap_;
      size_ = otherVector.size_;
      ptr_ = otherVector.ptr_;
      otherVector.ptr_ = nullptr;
      return *this;
    }
    ~Vector(){
      delete [] ptr_;
    }
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
      public:
        iterator(T* p) : p_{p} {}
        T* getp() {
          return p_;
        }
        T& operator*() {
          return *p_;
        }
        iterator& operator++() {
          p_++;
          return *this;
        }
        iterator operator++(int) {
          auto temp = *this;
          p_++;
          return temp;
        }
        iterator& operator--() {
          p_--;
          return *this;
        }
        iterator operator--(int) {
          auto temp = *this;
          p_--;
          return temp;
        }
        iterator operator+(int x) {
          p_+= x;
          return *this;
        }
        iterator operator-(int x) {
          p_-=x;
          return *this;
        }
        bool operator==(iterator otherIterator) {
          return getp() == otherIterator.getp();
        }
        bool operator!=(iterator otherIterator) {
          return getp() != otherIterator.getp();
        }
        bool operator<(iterator otherIterator) {
          return p_ < otherIterator.p_;
        }
        bool operator>(iterator otherIterator) {
          return p_ > otherIterator.p_;
        }
        bool operator>=(iterator otherIterator) {
          return p_ >= otherIterator.p_;
        }
        bool operator<=(iterator otherIterator) {
          return p_ <= otherIterator.p_;
        }
      private:
        T* p_;
    };
    iterator begin() {
      return iterator(ptr_);
    }
    iterator end() {
      return iterator(ptr_ + size_);
    }
    T& operator[](size_t index) {
      return ptr_[index];
    }
    const T& operator[](ssize_t index) const {
      return ptr_[index];
    }
    T& at(size_t index) {
      try {
        if (index < 0 || index >= size_) {
          throw std::out_of_range("Index goes out of range");
        }
        return ptr_[index];
      }
      catch(std::out_of_range error) {
        std::cout << error.what() << std::endl;
      }
    }
    const T& at(size_t index) const {
      try {
        if (index < 0 || index >= size_) {
          throw std::out_of_range("Index goes out of range");
        }
        return ptr_[index];
      }
      catch(std::out_of_range error) {
        std::cout << error.what() << std::endl;
      }
    }
    void push_back(const T& value) {
      if (cap_ == size_) {
        realocate();
      }
      ptr_[size_++] = value;
    }
    size_t size() {
      return size_;
    }
    void pop_back() {
      if (size_ != 0) {
        size_--;
      }
    }
    T& back() {
      return ptr_[size_ - 1];
    }
    T& front() {
      return ptr_[0];
    }
    iterator erase(iterator it) {
      if (it >= end() || it < begin()) {
        throw std::out_of_range("Out of range iterator!");
      }
      for(auto iter = it; iter != end(); iter++) {
        std::swap(*iter, *(iter + 1));
      }
      size_--;
      return it;
    }
    iterator erase(iterator it1, iterator it2) {
      if (it1 > end() || it1 < begin() || it2 > end() || it2 < begin() || it1 > it2) {
        throw std::out_of_range("Out of range iterator!");
      }
      for(auto iter = it1; iter != it2; iter++) {
        erase(iter);
      }
      return it1;
    }
    iterator insert(iterator pos, const T& value) {
      if (pos > end() || pos < begin()) {
        throw std::out_of_range("Out of range iterator!");
      }
      if (size_ == cap_) {
        realocate();
      }
      ptr_[size_++] = value;
      for(auto it = end() - 2; it != pos - 1; it--) {
        std::swap(*it, *(it + 1));
      }
      return pos;
    }
  private:
    size_t cap_ = 0;
    size_t size_ = 0;
    T* ptr_ = nullptr;
    void realocate() {
      cap_ *= 2;
      auto temp = new T[cap_];
      std::copy(ptr_, ptr_ + size_, temp);
      delete [] ptr_;
      ptr_ = temp;
    }
};

#endif
