#include<iostream>
#include "vector.hpp"



struct S{
    S(int val1, int val2)
    {
        m_val = val1;
        n_val = val2;
    }
    ~S()
    {

    }
    int m_val;
    int n_val;
};

int main()
{
    std::cout << "Creating vector" ;
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    Vector<S> s_v;
    std::cout << "Initialized vector of type S." << std::endl;
    s_v.emplace_back(5, 6);
}

