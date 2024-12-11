#include "vector_v4.hpp"
#include <cassert>
#include <iostream>

void Vectorv4TestStruct() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}
        int m_a;
        int m_b;
        int m_c;
    };
    VectorV4<S> temp;
    temp.push_back(S(4, 5, 6)); // push_back
    temp.push_back(S(43, 52, 61));
    assert(temp.size() == 2);
    VectorV4<S> temp1(temp); // Copy constructor
    assert(temp1.size() == 2);
    assert(temp1[0].m_a == 4);
    assert(temp1[0].m_b == 5);
    assert(temp1[0].m_c == 6);
    assert(temp1[1].m_a == 43);
    assert(temp1[1].m_b == 52);
    assert(temp1[1].m_c == 61);
    VectorV4<S> temp3;
    temp3.push_back(S(5, 6, 7));
    temp3.push_back(S(7, 8, 9));
    temp3.push_back(S(27, 28, 29));
    temp = temp3; // Copy Assign
    assert(temp.size() == 3);
    assert(temp[0].m_a == 5);
    assert(temp[0].m_b == 6);
    assert(temp[0].m_c == 7);
    assert(temp3.size() == 3);
    VectorV4<S> temp4(std::move(temp3)); // Move constructor
    assert(temp4.size() == 3);
    assert(temp3.size() == 0);
    assert(temp[2].m_a == 27);
    assert(temp[2].m_b == 28);
    assert(temp[2].m_c == 29);
    temp4 = std::move(temp1); // Move Assign
    assert(temp4.size() == 2);
    assert(temp1.size() == 0); // Size
}

void testVectorV4PushPopMoveSize() {
    VectorV4<int> temp;
    temp.push_back(3);
    temp.push_back(5);
    assert(temp.size() == 2);
    VectorV4<int> temp1;
    temp1 = std::move(temp);
    assert(temp1.size() == 2);
    assert(temp1[0] == 3);
    assert(temp1[1] == 5);
    assert(temp.size() == 0);
    VectorV4<int> temp2(std::move(temp1));
    assert(temp1.size() == 0);
    assert(temp2[0] == 3);
    assert(temp2[1] == 5);
    temp2.pop_back();
    assert(temp2.size() == 1);
}

void testVectorV4ResizeValueOptClear() {
    VectorV4<int> temp;
    for (size_t i = 0; i < 15; i++) {
        temp.push_back(i);
    }
    assert(temp.size() == 15);
    for (size_t i = 0; i < temp.size(); i++) {
        assert(temp[i] == i);
    }
    temp.clear();
    assert(temp.size() == 0);
}

// void checkMemoryLeaks(){
//     int constructor =0;
//     int destructor =0;
//     struct S{
//         S(int& constructor, int& destructor): m_constructor(constructor), m_destructor(destructor){
//             m_constructor++;
//         }

//         S& operator=(const S& copy){
//            m_constructor = copy.m_constructor;
//            m_destructor = copy.m_destructor;
//            return *this;
//         }

//         ~S(){
//             m_destructor++;
//         }

//         int& m_constructor;
//         int& m_destructor;
//     };
//     {
//         VectorV4<S> temp;
//         for(int i =0; i<4; i++)
//         {
//           S s(constructor, destructor);
//           temp.push_back(s);
//         }
//        //  assert(constructor == 4);
//     }
//     // assert(destructor ==4);

// }

void testVectorResizeValueOptClear() {
    VectorV4<int> temp;
    for (size_t i = 0; i < 15; i++) {
        temp.push_back(i);
    }
    assert(temp.size() == 15);
    for (size_t i = 0; i < temp.size(); i++) {
        assert(temp[i] == i); // Operator [] tested
    }
    temp.clear();
    assert(temp.size() == 0);
}

void testVectorCopyConstructorCopyAssign() {
    VectorV4<int> temp;
    for (size_t i = 0; i < 15; i++) {
        temp.push_back(i * 2);
    }
    VectorV4<int> temp1 = temp; // Copy Assign
    VectorV4<int> temp2(temp);  // Copy constructor
    assert(temp1.size() == 15);
    assert(temp2.size() == 15);
    for (size_t i = 0; i < temp.size(); i++) {
        assert(temp2[i] == i * 2);
        assert(temp1[i] == i * 2);
    }
}

void testS() {
    struct S {
        S() { // constructor
        }
        void realDefaultConstructor() {}
        ~S() { // destructor
        }
        S& operator=(const S& copy) // copy assignment operator a = b
        {
            x = copy.x;
            return *this;
        }
        S(const S& copy) // copy constructor  a(b) int b(c)
        {
            // assert(x == 5);
            std::cout << " copy constructor x = " << x << std::endl;
        }
        void realCopyConstructor(const S& copy) {
            // this->x(copy->x) /// calls copy constructor of all members ( ?? )
            // S::S(copy) // call my copy
        }
        int x = 5;
    };

    {
        VectorV4<S> temp;
        S           S1;
        S           S2;
        temp.push_back(S1);
        temp.push_back(S2);
    }
}

void testParamConstructorWithVectorV4() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}
        int m_a;
        int m_b;
        int m_c;
    };
    VectorV4<S> temp;
    S           s(2, 3, 4);
    temp.push_back(s);
    VectorV4<S> temp1(temp);
    assert(temp1.size() == 1);
    assert(temp1[0].m_a == 2);
    assert(temp1[0].m_b == 3);
    assert(temp1[0].m_c == 4);
    VectorV4<S> temp2;
    for (size_t i = 0; i < 15; i++) {
        S s(i, i * 2, i * 3);
        temp2.push_back(s);
    }
    temp1 = temp2;
    for (size_t i = 0; i < 15; i++) {
        assert(temp1[i].m_a == i);
        assert(temp1[i].m_b == i * 2);
        assert(temp1[i].m_c == i * 3);
    }
}

void VectorV4Struct() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}

        // Move constructor
        S(S&& copy) : m_a(std::move(copy.m_a)), m_b(std::move(copy.m_b)), m_c(std::move(copy.m_c)) {}

        // Copy Constructor
        S(const S& copy) : m_a(copy.m_a), m_b(copy.m_b), m_c(copy.m_c) {}

        // Copy Assignment
        S& operator=(S& copy) {
            m_a = copy.m_a;
            m_b = copy.m_b;
            m_c = copy.m_c;
            return *this;
        }

        // Move Assignment Operator
        S& operator=(S&& copy) {
            m_a = std::move(copy.m_a);
            m_b = std::move(copy.m_b);
            m_c = std::move(copy.m_c);
            return *this;
        }

        int m_a;
        int m_b;
        int m_c;
    };
    VectorV4<S> temp;
    temp.push_back(S(1, 2, 3));
    temp.push_back(S(4, 5, 6));
    temp.push_back(S(5, 5, 5));
    assert(temp.size() == 3);
    VectorV4<S> temp1(temp);
    assert(temp1[0].m_a == 1);
    assert(temp1[0].m_b == 2);
    assert(temp1[0].m_c == 3);
    assert(temp1[2].m_a == 5);
    assert(temp1[2].m_b == 5);
    assert(temp1[2].m_c == 5);
    temp.pop_back();
    VectorV4<S> temp2 = temp;
    assert(temp2.size() == 2);
    assert(temp1[1].m_a == 4);
    assert(temp1[1].m_b == 5);
    assert(temp1[1].m_c == 6);
    VectorV4<S> temp3(std::move(temp)); // Move constructor
    assert(temp3.size() == 2);
    assert(temp3[1].m_a == 4);
    assert(temp3[1].m_b == 5);
    assert(temp3[1].m_c == 6);
    assert(temp.size() == 0);
    VectorV4<S> temp4 = std::move(temp3);
    assert(temp3.size() == 0);
    assert(temp4.size() == 2);
}

int main() {
    Vectorv4TestStruct();
    testVectorV4PushPopMoveSize();
    testVectorV4ResizeValueOptClear();
    // checkMemoryLeaks();
    testVectorResizeValueOptClear();
    testVectorCopyConstructorCopyAssign();
    testS();
    testParamConstructorWithVectorV4();
    VectorV4Struct();
    return 0;
}
