#include <cassert>
#include <vector_v4.hpp>
#include <iostream>


void Vectorv4TestPushPop(){
    VectorV4<int> temp;
    temp.push_back(1);
    temp.push_back(2);
    assert(temp.size() == 2);
    assert(temp[0] == 1);
    assert(temp[1] == 2);
}

void VectorV4Struct(){
    struct S{
        S(int a, int b, int c):m_a(a), m_b(b), m_c(c)
        {
            std::cout << "constructor called" << std::endl;
        }
        ~S()
        {
            std::cout << "destructor called" << std::endl;
        }
        int m_a;
        int m_b;
        int m_c;
    };
    //std::cout << "size of T is " << sizeof(S) << std::endl;
  //  S* temp = (S*)(new char[sizeof(S)*10]);
  //  VectorV4<S> temp;
  //  S obj(1,2,3);
   // S obj1(4,5,6);
    // temp.push_back(obj);
    // temp.push_back(obj1);
    // assert(temp.size() == 2);
}

