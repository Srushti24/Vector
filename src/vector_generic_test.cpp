#ifndef VECTOR_GENERIC_TEST_HPP
#define VECTOR_GENERIC_TEST_HPP

#include "vector_v1.hpp"
#include "vector_v2.hpp"
#include "vector_v3.hpp"
#include "vector_v4.hpp"
#include <cassert>
#include <iostream>
#include <memory>

int constructionCount = 0;
int destructionCount  = 0;

struct S {
    S(int& constructionCount, int& destructionCount)
        : constructionCount_(constructionCount), destructionCount_(destructionCount) {
        std::cout << "constructor of S called" << std::endl;
        constructionCount_++;
    }
    ~S() {
        std::cout << "destructor of S called" << std::endl;
        destructionCount_++;
    }

    S(const S& copy)                                                                             // Copy Constructor
        : constructionCount_(copy.constructionCount_), destructionCount_(copy.destructionCount_) // copy constructor
    {
        std::cout << "copy constructor of S called" << std::endl;
        constructionCount_++;
    }

    S& operator=(const S& copy) // copy assign operator
    {
        constructionCount_ = copy.constructionCount_;
        destructionCount_  = copy.destructionCount_;
        std::cout << "copy assignment operator of S called" << std::endl;
        return *this;
    }

    S(S&& copy)                                                                                    // Move constructor
        : constructionCount_(copy.constructionCount_), destructionCount_(copy.destructionCount_) { // Move Constructor
        std::cout << "Move constructor of S called" << std::endl;
    }

    S& operator=(S&& copy) { // Move Assignment Operator
        std::cout << "move assign operator called" << std::endl;
        constructionCount_ = copy.constructionCount_;
        destructionCount_  = copy.destructionCount_;
        return *this;
    }

    int& constructionCount_;
    int& destructionCount_;
};

template <template <typename> class T> void testWithS() {
    int constructionCount = 0;
    int destructionCount  = 0;

    // Test construction
    {
        T<S> vector_v2;
        for (size_t i = 0; i < 5; i++) {
            vector_v2.push_back(S(constructionCount, destructionCount));
        }
    }
    assert(constructionCount == destructionCount);

    // Test copy constructor and copy assign
    constructionCount = 0;
    destructionCount  = 0;
    {
        {
            T<S> vector_v3;
            for (size_t i = 0; i < 2; i++) {
                vector_v3.push_back(S(constructionCount, destructionCount));
            }

            // Copy constructor
            {
                T<S> vector_v4(vector_v3);
                assert(constructionCount == 6);
            }
            assert(destructionCount == 4);

            // Copy Assignment Operator
            {
                T<S> vector_v5;
                for (size_t i = 0; i < 4; i++) {
                    vector_v5.push_back(S(constructionCount, destructionCount));
                }
                assert(destructionCount == 8);
                assert(vector_v5.size() == 4);
                vector_v5 = vector_v3;
                assert(vector_v5.size() == 2);
            }
        }
    }
    assert(destructionCount == 16);
    assert(constructionCount == destructionCount);

    constructionCount = 0;
    destructionCount  = 0;
    {
        T<S> vector_v3;
        for (size_t i = 0; i < 2; i++) {
            vector_v3.push_back(S(constructionCount, destructionCount));
        }
        assert(constructionCount == 4);
        assert(destructionCount == 2);
        T<S> vector_v4;
        vector_v4 = std::move(vector_v3);
        assert(vector_v3.size() == 0);
        assert(vector_v4.size() == 2);
        assert(constructionCount == 4);
        assert(destructionCount == 2);
        T<S> vector_v5(std::move(vector_v4));
    }
    assert(constructionCount == destructionCount);
}

int main() {
    testWithS<VectorV2>();
    testWithS<VectorV3>();
    testWithS<VectorV4>();
}

#endif