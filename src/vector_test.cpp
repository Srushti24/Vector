#include "vector.hpp"
#include <cassert>
#include <iostream>

void testVectorPushPopMoveSize() {
    Vector<int> temp;
    temp.push_back(3);
    temp.push_back(5);
    assert(temp.size() == 2);
    Vector<int> temp1;
    temp1 = std::move(temp); // Move Assignment constructor tested
    assert(temp1.size() == 2);
    assert(temp1[0] == 3);
    assert(temp1[1] == 5);
    assert(temp.size() == 0);
    Vector<int> temp2(std::move(temp1)); // Move constructor tested
    assert(temp1.size() == 0);
    assert(temp2[0] == 3);
    assert(temp2[1] == 5);
    temp2.pop_back(); // Pop back tested
    assert(temp2.size() == 1);
}

void testVectorResizeValueOptClear() {
    Vector<int> temp;
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
    Vector<int> temp;
    for (size_t i = 0; i < 15; i++) {
        temp.push_back(i * 2);
    }
    Vector<int> temp1 = temp; // Copy Assign
    Vector<int> temp2(temp);  // Copy constructor
    assert(temp1.size() == 15);
    assert(temp2.size() == 15);
    for (size_t i = 0; i < temp.size(); i++) {
        assert(temp2[i] == i * 2);
        assert(temp1[i] == i * 2);
    }
}

int main() {
    testVectorPushPopMoveSize();
    testVectorResizeValueOptClear();
    testVectorCopyConstructorCopyAssign();
    return 0;
}
