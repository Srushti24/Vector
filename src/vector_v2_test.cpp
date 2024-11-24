#include <cassert>
#include <iostream>
#include "vector_v2.hpp"

void testParamConstructorWithVectorV2() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}
        int m_a;
        int m_b;
        int m_c;
    };
    VectorV2<S> temp;
    temp.push_back(2, 3, 4);
    VectorV2<S> temp1(temp);
    assert(temp1.size() == 1);
    assert(temp1[0].m_a == 2);
    assert(temp1[0].m_b == 3);
    assert(temp1[0].m_c == 4);
    VectorV2<S> temp2;
    for (size_t i = 0; i < 15; i++) {
        temp2.push_back(i, i * 2, i * 3);
    }
    temp1 = temp2;
    for (size_t i = 0; i < 15; i++) {
        assert(temp1[i].m_a == i);
        assert(temp1[i].m_b == i * 2);
        assert(temp1[i].m_c == i * 3);
    }
}

void testVectorV2PushPopMoveSize() {
    VectorV2<int> temp;
    temp.push_back(3);
    temp.push_back(5);
    assert(temp.size() == 2);
    VectorV2<int> temp1;
    temp1 = std::move(temp);
    assert(temp1.size() == 2);
    assert(temp1[0] == 3);
    assert(temp1[1] == 5);
    assert(temp.size() == 0);
    VectorV2<int> temp2(std::move(temp1));
    assert(temp1.size() == 0);
    assert(temp2[0] == 3);
    assert(temp2[1] == 5);
    temp2.pop_back();
    assert(temp2.size() == 1);
}

void testVectorV2ResizeValueOptClear() {
    VectorV2<int> temp;
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

int main(){
    testParamConstructorWithVectorV2();
    testVectorV2PushPopMoveSize();
    testVectorV2ResizeValueOptClear();
    return 0;
}
