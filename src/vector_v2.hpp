#include <iostream>
#include <memory>

template <typename T> class VectorV2 {
  public:
    // Constructor
    VectorV2() : array_(new T[capacity_]) { size_ = 0; }

    // Destructor
    ~VectorV2() { destroy() };

    void destroy() {delete array_[] }

    // Copy Constructor
     VectorV2(const VectorV2& vectorCopy)
        : size_(vectorCopy.size_), capacity_(vectorCopy.capacity_), array_(new T[vectorCopy.capacity_]) {
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = vectorCopy.array_[i];
        }
    }

    // Copy Assignment operator
    VectorV2& operator=(const VectorV2& vectorCopy) {
        destroy();
        size_     = vectorCopy.size_;
        capacity_ = vectorCopy.capacity_;
        array_ = new T[vectorCopy.capacity_];
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = vectorCopy.array_[i];
        }
        return *this;
    }

    // Move Constructor
    VectorV2(VectorV2&& vectorCopy) : array_(vectorCopy.array_), capacity_(vectorCopy.capacity_), size_(vectorCopy.size_) {
        vectorCopy.array_    = new T[original_capacity_];
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = original_capacity_;
    }

    // Move Assignment operator
    VectorV2& operator=(VectorV2&& vectorCopy) {
        destroy();
        array_               = vectorCopy.array_;
        capacity_            = vectorCopy.capacity_;
        size_                = vectorCopy.size_;
        vectorCopy.array_    = new T[original_capacity_];
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = original_capacity_;
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
    int original_capacity_ = 10;
    T* array_;
    int size_ = 0;
};