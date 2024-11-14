#include <cassert>
#include <vector_v3.hpp>

void Vectorv3TestStruct() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {

        }
        ~S() {

        }
        int m_a;
        int m_b;
        int m_c;
    };
    VectorV3<S> temp;
    temp.push_back(S(4, 5, 6));  // push_back
    temp.push_back(S(43, 52, 61));
    assert(temp.size() == 2);
    VectorV3<S> temp1(temp);   // Copy constructor
    assert(temp1.size() == 2);
    assert(temp1[0].m_a == 4);
    assert(temp1[0].m_b == 5);
    assert(temp1[0].m_c == 6);
    assert(temp1[1].m_a == 43);
    assert(temp1[1].m_b == 52);
    assert(temp1[1].m_c == 61);
    VectorV3<S> temp3;
    temp3.push_back(S(5, 6, 7));
    temp3.push_back(S(7, 8, 9));
    temp3.push_back(S(27, 28, 29));
    temp = temp3;     // Copy Assign
    assert(temp.size() == 3);
    assert(temp[0].m_a == 5);
    assert(temp[0].m_b == 6);
    assert(temp[0].m_c == 7);
    assert(temp3.size() == 3);
    VectorV3<S> temp4(std::move(temp3));  // Move constructor
    assert(temp4.size() == 3);
    assert(temp3.size() == 0);
    assert(temp[2].m_a == 27);
    assert(temp[2].m_b == 28);
    assert(temp[2].m_c == 29);
    temp4 = std::move(temp1); // Move Assign
    assert(temp4.size() == 2);
    assert(temp1.size() == 0);  // Size
}

void testVectorV3PushPopMoveSize() {
    VectorV3<int> temp;
    temp.push_back(3);
    temp.push_back(5);
    assert(temp.size() == 2);
    VectorV3<int> temp1;
    temp1 = std::move(temp);
    assert(temp1.size() == 2);
    assert(temp1[0] == 3);
    assert(temp1[1] == 5);
    assert(temp.size() == 0);
    VectorV3<int> temp2(std::move(temp1));
    assert(temp1.size() == 0);
    assert(temp2[0] == 3);
    assert(temp2[1] == 5);
    temp2.pop_back();
    assert(temp2.size() == 1);
}

void testVectorV3ResizeValueOptClear() {
    VectorV3<int> temp;
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


void checkMemoryLeaks(){
    int constructor =0;
    int destructor =0;
    struct S{
        S(int& constructor, int& destructor): m_constructor(constructor), m_destructor(destructor){
            m_constructor++;
        }

        ~S(){
            m_destructor++;
        }

        int& m_constructor;
        int& m_destructor;
    };

    {
        VectorV3<S> temp;
        for(int i =0; i<4; i++)
        {
            temp.push_back(S(constructor, destructor));
        }
        assert(constructor == 4);
    }
    assert(destructor ==4);

}