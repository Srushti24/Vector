#ifndef VECTOR_V4_HPP
#define VECTOR_V4_HPP

#include <iostream>
#include <memory>


template <typename T>
class VectorV4{
    public:
    VectorV4(): capacity(10),temp((T*)(new char[sizeof(T)* capacity])), original_capacity(10),
    size_(0) {
    }

    ~VectorV4(){
        destroy();
    }

    void destroy(){
        for(size_t i=0; i< size_;i++)
        {
            temp[i].~T();
        }
        delete[] temp;
    }

    T operator[](int pos){
        return temp[pos];
    }
    T operator[](int pos) const{
        return temp[pos];
    }

    //Copy Constructor
    VectorV4(const VectorV4& vectorv4Copy)
    {
        temp = (T*)(new char[sizeof(T)* vectorv4Copy.capacity]);
        capacity = vectorv4Copy.capacity;
        original_capacity = vectorv4Copy.original_capacity;
        size_ = vectorv4Copy.size_;
        for(size_t i=0; i<size_; i++)
        {
            temp[i] = vectorv4Copy[i];
        }
    }

    //Copy Assignment Operator
    VectorV4& operator=(const VectorV4& vectorv4Copy)
    {
        destroy();
        temp = (T*)(new char[sizeof(T)* vectorv4Copy.capacity]);
        capacity = vectorv4Copy.capacity;
        original_capacity = vectorv4Copy.original_capacity;
        size_ = vectorv4Copy.size_;
        for(size_t i=0; i<size_; i++)
        {
            temp[i] = vectorv4Copy[i];
        }
        return *this;
    }

    //Move Assignment Operator
    VectorV4& operator=(VectorV4&& vectorv4Copy)
    {
        destroy();
        temp = vectorv4Copy.temp;
        original_capacity = vectorv4Copy.original_capacity;
        capacity = vectorv4Copy.capacity;
        size_ = vectorv4Copy.size_;
        vectorv4Copy.temp = nullptr;
        return *this;
    }

    //Move Constructor
    VectorV4(VectorV4&& vectorv4Copy):temp(vectorv4Copy.temp),
    size_(vectorv4Copy.size_), original_capacity(vectorv4Copy.original_capacity),
    capacity(vectorv4Copy.capacity)
    {
        vectorv4Copy.temp = (T*)new char[sizeof(T)* vectorv4Copy.capacity];
        vectorv4Copy.capacity = 10;
        vectorv4Copy.original_capacity = 10;
        vectorv4Copy.size_ = 0;
    }
    
    //Push Back
    void push_back(T val)
    {
        if(size_ == capacity)
        {
            resize();
        }
        temp[size_] = val;
        size_++;
    }

    void resize()
    {
        capacity = 2*capacity;
        T* copy_size_ = (T*)(new char[sizeof(T)* capacity]);
        for(size_t i =0; i< capacity; i++)
        {
            copy_size_[i] = temp[i];
        }
        delete[] temp;
        temp = copy_size_;
    }

    //Pop Back
    void pop_back()
    {
        size_--;
    }

    // size_
    int size()
    {
        return size_;
    }
    int capacity;
    T* temp;
    int original_capacity;
    int size_;
};

#endif