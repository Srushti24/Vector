#include "vector_v2_test.cpp"
#include "vector_v3_test.cpp"
#include "vector_test.cpp"
#include <iostream>


void testVector() {
    testVectorPushPopMoveSize();
    testVectorResizeValueOptClear();
    testVectorCopyConstructorCopyAssign();

}

void testVectorV2() {
    testParamConstructorWithVectorV2();
    testVectorV2PushPopMoveSize();
    testVectorV2ResizeValueOptClear();
}

void testVectorV3() { 
    Vectorv3TestStruct();
    testVectorV3PushPopMoveSize();
    testVectorV3ResizeValueOptClear();
    checkMemoryLeaks();
}


int main(int argc, const char* argv[]) {
    testVector();
    testVectorV2();
    testVectorV3();
}