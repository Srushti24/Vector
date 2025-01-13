#ifndef Vector_V1_HPP
#define Vector_V1_HPP

#include <iostream>
#include <memory>

template <typename T> class VectorV1 {
  public:
    // Constructor
    VectorV1()
        : array_(new T[capacity_]) {

          };

    // Destructor
    ~VectorV1() { destroy(); };

    void destroy() { delete[] array_; }

    // Copy Constructor
    VectorV1(const VectorV1& VectorV1Copy)
        : size_(VectorV1Copy.size_), capacity_(VectorV1Copy.capacity_), array_(new T[VectorV1Copy.capacity_]) {
        for (size_t i = 0; i < VectorV1Copy.size(); i++) {
            array_[i] = VectorV1Copy.array_[i];
        }
    }

    // Copy Assignment operator
    VectorV1& operator=(const VectorV1& VectorV1Copy) {
        destroy();
        size_     = VectorV1Copy.size_;
        capacity_ = VectorV1Copy.capacity_;
        array_    = new T[VectorV1Copy.capacity_];
        for (size_t i = 0; i < VectorV1Copy.size(); i++) {
            array_[i] = VectorV1Copy.array_[i];
        }
        return *this;
    }

    // Move Constructor
    VectorV1(VectorV1&& VectorV1Copy)
        : array_(VectorV1Copy.array_), capacity_(VectorV1Copy.capacity_), size_(VectorV1Copy.size_) {
        VectorV1Copy.array_    = new T[original_capacity_];
        VectorV1Copy.size_     = 0;
        VectorV1Copy.capacity_ = original_capacity_;
    }

    // Move Assignment operator
    VectorV1& operator=(VectorV1&& VectorV1Copy) {
        destroy();
        array_                 = VectorV1Copy.array_;
        capacity_              = VectorV1Copy.capacity_;
        size_                  = VectorV1Copy.size_;
        VectorV1Copy.array_    = new T[original_capacity_];
        VectorV1Copy.size_     = 0;
        VectorV1Copy.capacity_ = original_capacity_;
        return *this;
    }

    // Push element
    void push_back(T value) {
        if (size_ == capacity_) {
            resize();
        }
        array_[size_] = value;
        size_++;
    }

    void pop_back() { size_--; }

    void clear() {
        destroy();
        size_  = 0;
        array_ = new T[capacity_];
    }

    // resize
    void resize() {
        capacity_    = capacity_ * 2;
        T* tempArray = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            tempArray[i] = array_[i];
        }
        array_    = tempArray;
        tempArray = nullptr;
    }

    int size() const { return size_; }

    T operator[](int currentPosition) { return array_[currentPosition]; }

  private:
    int capacity_          = 10;
    int original_capacity_ = 10;
    T*  array_;
    int size_ = 0;
};

#endif