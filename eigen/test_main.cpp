#include <gtest/gtest.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    srand((unsigned)time(NULL));
    int rt = RUN_ALL_TESTS();
    return rt;
}