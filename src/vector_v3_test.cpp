#include <cassert>
#include <vector_v3.hpp>

void Vectorv3TestStruct() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}
        int m_a;
        int m_b;
        int m_c;
    };
    VectorV3<S> temp;
    temp.push_back(4, 5, 6);
    temp.push_back(43, 52, 61);
    assert(temp.size() == 2);
    VectorV3<S> temp1(temp);
    assert(temp1.size() == 2);
    assert(temp1[0].m_a == 4);
    assert(temp1[0].m_b == 5);
    assert(temp1[0].m_c == 6);
    assert(temp1[1].m_a == 43);
    assert(temp1[1].m_b == 52);
    assert(temp1[1].m_c == 61);
    VectorV3<S> temp3;
    temp3.push_back(5, 6, 7);
    temp3.push_back(7, 8, 9);
    temp3.push_back(27, 28, 29);
    temp = temp3;
    assert(temp.size() == 3);
    assert(temp[0].m_a == 5);
    assert(temp[0].m_b == 6);
    assert(temp[0].m_c == 7);
    assert(temp3.size() == 3);
    VectorV3<S>temp4(std::move(temp3));
    assert(temp4.size() == 3);
    assert(temp3.size() == 0);
    assert(temp[2].m_a == 27);
    assert(temp[2].m_b == 28);
    assert(temp[2].m_c == 29);
    temp4 = std::move(temp1);
    assert(temp4.size() == 2);
    assert(temp1.size() == 0);

    
}