#include<iostream>
#include "vector.hpp"



struct S{

    S(int val)
    {
        m_val = val;
    }
    ~S()
    {

    }
    int m_val;
};

int main()
{
    std::cout << "Creating vector" ;
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
   Vector<S> s_v;
    s_v.push_back(S(5));
}

