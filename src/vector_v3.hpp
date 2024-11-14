#ifndef VECTOR_V3_HPP
#define VECTOR_V3_HPP

#include <iostream>
#include <memory>

template <typename T> class VectorV3 {
  public:
    VectorV3() : capacity_(10), original_capacity_(10), size_(0), array_(new T*[capacity_]) {}

    ~VectorV3() {
        destroy();
    }

    // Copy constructor
    VectorV3(const VectorV3& copy)
        : capacity_(copy.capacity_), size_(copy.size_), original_capacity_(copy.original_capacity_) {
        array_ = new T*[capacity_];
        for (size_t i = 0; i < size_; i++) {
            array_[i] = new T(*copy.array_[i]);
        }
    }

    // Assignment operator
    VectorV3& operator=(const VectorV3& copy) {
        destroy();
        capacity_          = copy.capacity_;
        size_              = copy.size_;
        original_capacity_ = copy.original_capacity_;
        array_             = new T*[capacity_];
        for (size_t i = 0; i < size_; i++) {
            array_[i] = new T(*copy.array_[i]);
        }
        return *this;
    }

    // Move constructor
    VectorV3(VectorV3&& copy)
        : capacity_(copy.capacity_), size_(copy.size_), original_capacity_(copy.original_capacity_),
          array_(copy.array_) {
        copy.capacity_ = copy.original_capacity_;
        copy.size_     = 0;
        copy.array_    = new T*[original_capacity_];
    }

    int size() const { return size_; }

    // Move Assignmenet operator
    VectorV3& operator=(VectorV3&& copy) {
        destroy();
        capacity_          = copy.capacity_;
        size_              = copy.size_;
        original_capacity_ = copy.original_capacity_;
        array_             = copy.array_;
        copy.size_         = 0;
        copy.array_        = new T*[original_capacity_];
        return *this;
    }

    void clear() {
        destroy();
        capacity_          = 10;
        original_capacity_ = 10;
        size_              = 0;
        array_             = new T*[capacity_];
    }

    void destroy() { delete[] array_; }

    T operator[](int position) { return *array_[position]; }

    void push_back(T element) {
        if (size_ == capacity_) {
            resize();
        }
        array_[size_] = new T(element);
        size_++;
        
    }

    void pop_back(){
        delete array_[size_-1];
        array_[size_-1] = nullptr;
        size_--;
    }

    // resize
    void resize() {
        capacity_ = capacity_ * 2;
        T** temp  = new T*[capacity_];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = array_[i];
        }
        array_ = temp;
    }

    int size() { return size_; }
    int capacity_;
    T** array_;
    int size_;
    int original_capacity_;
};

#endif