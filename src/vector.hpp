#include <iostream>
#include <memory>

template <typename T> class Vector {
  public:
    // Constructor
    Vector() : array_(new std::unique_ptr<T>[capacity_]) { size_ = 0; }

    // Destructor
    ~Vector() { destroy(); }

    void destroy() { 
        delete[] array_;
    }

    // Copy Constructor
     Vector(const Vector& vectorCopy)
        : size_(vectorCopy.size_), capacity_(vectorCopy.capacity_), array_(new std::unique_ptr<T>[capacity_]) {
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = std::make_unique<T>(*vectorCopy.array_[i]);
        }
    }

    // Copy Assignment operator
    Vector& operator=(const Vector& vectorCopy) {
        destroy();
        size_     = vectorCopy.size_;
        capacity_ = vectorCopy.capacity_;
        array_ = new std::unique_ptr<T>[capacity_];
        for (size_t i = 0; i < vectorCopy.size(); i++) {
            array_[i] = std::make_unique<T>(*vectorCopy.array_[i]);
        }
        return *this;
    }

    // Move Constructor
    Vector(Vector&& vectorCopy) : array_(vectorCopy.array_), capacity_(vectorCopy.capacity_), size_(vectorCopy.size_) {
        vectorCopy.array_    = new std::unique_ptr<T>[capacity_];
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = original_capacity_;
    }

    // Move Assignment operator
    Vector& operator=(Vector&& vectorCopy) {
        destroy();
        array_               = vectorCopy.array_;
        capacity_            = vectorCopy.capacity_;
        size_                = vectorCopy.size_;
        vectorCopy.array_    = new std::unique_ptr<T>[capacity_];
        vectorCopy.size_     = 0;
        vectorCopy.capacity_ = original_capacity_;
        return *this;
    }

    // Push element
    template<typename... Args>
    void push_back(Args&&... args) {
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
        capacity_    = capacity_ * 2;
        std::unique_ptr<T>* tempArray =  new std::unique_ptr<T>[capacity_];
        for (size_t i = 0; i < size_; i++) {
            tempArray[i] = std::move(array_[i]);
        }
        array_    = tempArray;
        tempArray = nullptr;
    }

    int size() const { return size_; }

    T operator[](int currentPosition) {
        return *array_[currentPosition]; 
    }

  private:
    int capacity_ = 10;
    int original_capacity_ = 10;
    std::unique_ptr<T>*  array_;
    int size_ = 0;
};