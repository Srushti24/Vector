#include "vector.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    Vector<int> temp;
   // std::cout << temp.m_array << std::endl;
    temp.push_back(10);
    temp.push_back(2);
    // std::cout << temp.m_array << std::endl;
    for(size_t i=0; i<2; i++)
    {
        std::cout << temp[i] << std::endl;
    }
    return 0;
}