#include "vector_test.cpp"
#include "vector_v3_test.cpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    testParamConstructorSWithVector();
    testVectorPushPopMoveSize();
    testVectorResizeValueOptClear();
    Vectorv3TestStruct();
}
