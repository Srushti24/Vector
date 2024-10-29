#include<iostream>

template<typename T>
class Vector{
    public:
    //Constructor
    Vector():
    array_(new T[capacity_]){
        size_ = 0;
    }

    //Destructor
    ~Vector(){
        destroy();
    }

    void destroy()
    {
        delete array_;
    }

    //Copy Constructor
    Vector(const Vector& vectorCopy):array_(new T[vectorCopy.array_]),
    size_(vectorCopy.size_),
    capacity_(vectorCopy.capacity_)
    {
        for(size_t i=0;i <size_; i++)
        {
            array_[i] = vectorCopy[i];
        }
    }

    //Copy Assignment operator
    Vector& operator=(const Vector& vectorCopy)
    {
        destroy();
        array_ = new T[vectorCopy.array_];
        for(size_t i=0;i <size_; i++)
        {
            array_[i] = vectorCopy[i];
        }
        size_ = vectorCopy.size_;
        capacity_ = vectorCopy.capacity_;
        return *this;
    }

    //Move Constructor
    Vector(Vector&& vectorCopy):
    array_(vectorCopy.array_), capacity_(vectorCopy.capacity_),size_(vectorCopy.size_)
    {
        vectorCopy.array_ = nullptr;
        vectorCopy.size_ = 0;
        vectorCopy.capacity_ = 0;
    }

    //Move Assignment operator
    Vector& operator=(Vector&& vectorCopy)
    {
        destroy();
        array_ = vectorCopy.array_;
        capacity_ = vectorCopy.capacity_;
        size_ = vectorCopy.size_;
        vectorCopy.array_ = nullptr;
        vectorCopy.size_ = 0;
        vectorCopy.capacity_ = 0;
        return *this;
    }

    //Push element
    void push_back(T value)
    {
        array_[size_] = value;
        size_++;
    }

    //resize
    void resize()
    {
        capacity_ = capacity_*2;
        
    }

    T operator[](int currentPosition)
    {
        return array_[currentPosition];
    }

    private:
    T* array_;
    int capacity_ = 10;
    int size_ = 0;
};