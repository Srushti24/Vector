#ifndef VECTOR_V4_HPP
#define VECTOR_V4_HPP

#include <iostream>
#include <memory>

template <typename T> class VectorV4 {
  public:
    VectorV4() : capacity_(10), array_((T*) (new char[sizeof(T) * capacity_])), size_(0) {}

    ~VectorV4() { destroy(); }

    void destroy() {
        if (size_ != 0) {
            for (size_t i = 0; i < size_; i++) {
                array_[i].~T();
            }
            delete[] reinterpret_cast<char*>(array_);
            size_ = 0;
        }
    }

    T& operator[](int pos) { return array_[pos]; }
    T& operator[](int pos) const { return array_[pos]; }

    VectorV4(const VectorV4& vectorv4Copy) {
        array_    = (T*) (new char[sizeof(T) * vectorv4Copy.capacity_]);
        capacity_ = vectorv4Copy.capacity_;
        size_     = vectorv4Copy.size_;
        for (size_t i = 0; i < size_; i++) {
            new (&array_[i]) T(vectorv4Copy.array_[i]);
        }
    }

    VectorV4& operator=(const VectorV4& vectorv4Copy) {
        destroy();
        capacity_ = vectorv4Copy.capacity_;
        array_    = (T*) (new char[sizeof(T) * vectorv4Copy.capacity_]);
        size_     = vectorv4Copy.size_;
        for (size_t i = 0; i < size_; i++) {
            new (&array_[i]) T(vectorv4Copy.array_[i]);
        }
        return *this;
    }

    VectorV4& operator=(VectorV4&& vectorv4Copy) {
        destroy();
        array_              = vectorv4Copy.array_;
        capacity_              = vectorv4Copy.capacity_;
        size_                  = vectorv4Copy.size_;
        vectorv4Copy.array_    = nullptr;
        vectorv4Copy.capacity_ = 10;
        vectorv4Copy.size_     = 0;
        return *this;
    }

    VectorV4(VectorV4&& vectorv4Copy)
        : array_(vectorv4Copy.array_), size_(vectorv4Copy.size_), capacity_(vectorv4Copy.capacity_) {
        vectorv4Copy.array_    = (T*) new char[sizeof(T) * vectorv4Copy.capacity_];
        vectorv4Copy.capacity_ = 10;
        vectorv4Copy.size_     = 0;
    }

    void push_back(T val) {
        if (size_ == capacity_) {
            resize();
        }
        new (&array_[size_]) T(val);
        size_++;
    }

    void clear() {
        destroy();
        array_    = nullptr;
        capacity_ = 10;
        size_     = 0;
    }

    void resize() {
        capacity_     = 2 * capacity_;
        T* new_array_ = (T*) (new char[sizeof(T) * capacity_]);
        for (size_t i = 0; i < size_; i++) {
            new (&new_array_[i]) T(array_[i]);
        }
        for (size_t i = 0; i < size_; i++) {
            array_[i].~T();
        }
        delete[] reinterpret_cast<char*>(array_);
        array_ = new_array_;
    }

    void pop_back() {
        array_[size_ - 1].~T();
        size_--;
    }

    int size() { return size_; }

  private:
    int capacity_;
    T*  array_;
    int size_;
};

#endif