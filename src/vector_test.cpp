#include <cassert>
#include <iostream>
#include <vector.hpp>

void testVectorPushPopSize() {
    Vector<int> temp;
    temp.push_back(3);
    temp.push_back(5);
    assert(temp.size() == 2);
    temp.pop_back();
    assert(temp.size() == 1);
}

void testVectorResizeValueOptClear() {
    Vector<int> temp;
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

void testVectorCopyConstrCopyAssignOpt() {
    Vector<int> temp;
    temp.push_back(4);
    temp.push_back(6);
    Vector<int> vectorOne(temp);
    assert(vectorOne.size() == 2);
    assert(vectorOne[0] == 4);
    assert(vectorOne[1] == 6);
    Vector<int> vectorTwo;
    vectorTwo.push_back(10);
    vectorTwo.push_back(20);
    vectorTwo.push_back(30);
    vectorOne = vectorTwo;
    assert(vectorOne[0] == 10);
    assert(vectorOne[1] == 20);
    assert(vectorOne[2] == 30);
}

void testVectorMoveConstructor() {
    Vector<int> temp;
    temp.push_back(4);
    temp.push_back(6);
    Vector<int> temp1(std::move(temp));
    assert(temp1.size() == 2);
    assert(temp1[0] == 4);
    assert(temp1[1] == 6);
    assert(temp.size() == 0);
}

void testVectorMoveAssignOpt() {
    Vector<int> temp;
    temp.push_back(4);
    temp.push_back(6);
    Vector<int> temp1;
    temp1.push_back(40);
    temp1.push_back(60);
    temp1.push_back(32);
    temp1.push_back(64);
    temp1 = std::move(temp);
    assert(temp1.size() == 2);
    assert(temp1[0] == 4);
    assert(temp1[1] == 6);
    assert(temp.size() == 0);
}