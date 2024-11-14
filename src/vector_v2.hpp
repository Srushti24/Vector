#ifndef VectorV2_HPP
#define VectorV2_HPP

#include <iostream>
#include <memory>

template <typename T> class VectorV2 {
  public:
    // Constructor
    VectorV2() : array_(new std::unique_ptr<T>[capacity_]) { size_ = 0; }

    // Destructor
    ~VectorV2() { destroy(); }

    void destroy() { delete[] array_; }

    // Copy Constructor
    VectorV2(const VectorV2& VectorV2Copy)
        : size_(VectorV2Copy.size_), capacity_(VectorV2Copy.capacity_), array_(new std::unique_ptr<T>[capacity_]) {
        for (size_t i = 0; i < VectorV2Copy.size(); i++) {
            array_[i] = std::make_unique<T>(*VectorV2Copy.array_[i]);
        }
    }

    // Copy Assignment operator
    VectorV2& operator=(const VectorV2& VectorV2Copy) {
        destroy();
        size_     = VectorV2Copy.size_;
        capacity_ = VectorV2Copy.capacity_;
        array_    = new std::unique_ptr<T>[capacity_];
        for (size_t i = 0; i < VectorV2Copy.size(); i++) {
            array_[i] = std::make_unique<T>(*VectorV2Copy.array_[i]);
        }
        return *this;
    }

    // Move Constructor
    VectorV2(VectorV2&& VectorV2Copy)
        : array_(VectorV2Copy.array_), capacity_(VectorV2Copy.capacity_), size_(VectorV2Copy.size_) {
        VectorV2Copy.array_    = new std::unique_ptr<T>[capacity_];
        VectorV2Copy.size_     = 0;
        VectorV2Copy.capacity_ = original_capacity_;
    }

    // Move Assignment operator
    VectorV2& operator=(VectorV2&& VectorV2Copy) {
        destroy();
        array_                 = VectorV2Copy.array_;
        capacity_              = VectorV2Copy.capacity_;
        size_                  = VectorV2Copy.size_;
        VectorV2Copy.array_    = new std::unique_ptr<T>[capacity_];
        VectorV2Copy.size_     = 0;
        VectorV2Copy.capacity_ = original_capacity_;
        return *this;
    }

    // Push element
    template <typename... Args> void push_back(Args&&... args) {
        if (size_ == capacity_) {
            resize();
        }
        array_[size_] = std::make_unique<T>(std::forward<Args>(args)...);
        size_++;
    }

    void pop_back() { size_--; }

    void clear() {
        destroy();
        size_  = 0;
        array_ = new std::unique_ptr<T>[capacity_];
    }

    // resize
    void resize() {
        capacity_                     = capacity_ * 2;
        std::unique_ptr<T>* tempArray = new std::unique_ptr<T>[capacity_];
        for (size_t i = 0; i < size_; i++) {
            tempArray[i] = std::move(array_[i]);
        }
        array_    = tempArray;
        tempArray = nullptr;
    }

    int size() const { return size_; }

    T operator[](int currentPosition) { return *array_[currentPosition]; }

  private:
    int                 capacity_          = 10;
    int                 original_capacity_ = 10;
    std::unique_ptr<T>* array_;
    int                 size_ = 0;
};

#endif