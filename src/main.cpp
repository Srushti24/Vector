#include "vector_test.cpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    testVectorPushPopSize();
    testVectorResizeValueOptClear();
    testVectorCopyConstrCopyAssignOpt();
    testVectorMoveConstructor();
    testVectorMoveAssignOpt();
    return 0;
}
