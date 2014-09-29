#include "gtest/gtest.h"
#include "CStorageHandler.h"

TEST(testStorageHandler, MyFirstTest)
{
    CStorageHandler storageHandler;
}

int main(int argc, char* argv[])
{
    int i = 1;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
