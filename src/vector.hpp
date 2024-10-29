#include <iostream>

template <typename T> class Vector {
  public:
    // Constructor
    Vector() : array_(new T[capacity_]) { size_ = 0; }

    // Destructor
    ~Vector() { destroy(); }

    void destroy() { delete[] array_; }

    // Copy Constructor
    Vector(const Vector& vectorCopy)
        : array_(new T[vectorCopy.capacity_]), size_(vectorCopy.size_), capacity_(vectorCopy.capacity_) {
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = vectorCopy.array_[i];
        }
    }

    // Copy Assignment operator
    Vector& operator=(const Vector& vectorCopy) {
        destroy();
        array_ = new T[vectorCopy.capacity_];
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = vectorCopy.array_[i];
        }
        size_     = vectorCopy.size_;
        capacity_ = vectorCopy.capacity_;
        return *this;
    }

    // Move Constructor
    Vector(Vector&& vectorCopy) : array_(vectorCopy.array_), capacity_(vectorCopy.capacity_), size_(vectorCopy.size_) {
        vectorCopy.array_    = nullptr;
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = 0;
    }

    // Move Assignment operator
    Vector& operator=(Vector&& vectorCopy) {
        destroy();
        array_               = vectorCopy.array_;
        capacity_            = vectorCopy.capacity_;
        size_                = vectorCopy.size_;
        vectorCopy.array_    = nullptr;
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = 0;
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
    int capacity_ = 10;
    T*  array_;
    int size_ = 0;
};