#include <cassert>
#include "vector_v4.hpp"
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
        }
        ~S()
        {
        }

        //Move constructor 
        S(S&& copy): m_a(std::move(copy.m_a)), m_b(std::move(copy.m_b)), m_c(std::move(copy.m_c))
        {

        }

        //Copy Constructor
        S(const S& copy): m_a(copy.m_a), m_b(copy.m_b), m_c(copy.m_c)
        {

        }

        //Copy Assignment
        S& operator=(S& copy)
        {
            m_a = copy.m_a;
            m_b = copy.m_b;
            m_c = copy.m_c;
            return *this;
        }

        //Move Assignment Operator
        S& operator=(S&& copy){
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
   temp.push_back(S(1,2,3));
   temp.push_back(S(4,5,6));
   temp.push_back(S(5,5,5));
   assert(temp.size() == 3);
   VectorV4<S>temp1(temp);
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
   VectorV4<S>temp3(std::move(temp));  // Move constructor
   assert(temp3.size() == 2);
   assert(temp3[1].m_a == 4);
   assert(temp3[1].m_b == 5);
   assert(temp3[1].m_c == 6);
   assert(temp.size() == 0);
   VectorV4<S> temp4 = std::move(temp3);
   assert(temp3.size() == 0);
   assert(temp4.size() == 2);
}

void testResize()
{
    VectorV4<int> temp;
    for(size_t i=0; i<20; i++)
    {
        temp.push_back(i);
    }
    assert(temp.size() == 20);
    for(size_t i=0; i<20; i++)
    {
        assert(temp[i] == i);
    }
}

int main(){
    Vectorv4TestPushPop();
    VectorV4Struct();
    testResize();
    return 0;
}

