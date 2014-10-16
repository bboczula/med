#include "gtest/gtest.h"
#include "CParser.h"

class CParserTest : public ::testing::Test
{
public:
    CParser parser;
protected:
    virtual void SetUp()
    {
    }
};

TEST_F(CParserTest, singlePrint)
{
    CCommandMetadata* result = parser.parse("p");
    ASSERT_TRUE(result->command.isPresent);
    ASSERT_EQ(result->command.value, "p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, startRangeOnlyPrint)
{
    CCommandMetadata* result = parser.parse("2p");
    ASSERT_TRUE(result->command.isPresent);
    ASSERT_EQ(result->command.value, "p");
    ASSERT_TRUE(result->startAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->startAddress.value, 1);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, endRangeOnlyPrint)
{
    CCommandMetadata* result = parser.parse(",5p");
    ASSERT_TRUE(result->command.isPresent);
    ASSERT_EQ(result->command.value, "p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_TRUE(result->endAddress.isPresent);
    ASSERT_EQ(result->endAddress.value, 4);
}

TEST_F(CParserTest, fullRangeOnlyPrint)
{
    CCommandMetadata* result = parser.parse("2,3p");
    ASSERT_TRUE(result->command.isPresent);
    ASSERT_EQ(result->command.value, "p");
    ASSERT_TRUE(result->startAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->startAddress.value, 1);
    ASSERT_TRUE(result->endAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->endAddress.value, 2);
}

TEST_F(CParserTest, separatorRangeOnlyPrint)
{
    CCommandMetadata* result = parser.parse(",p");
    ASSERT_TRUE(result->command.isPresent);
    ASSERT_EQ(result->command.value, "p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_FALSE(result->endAddress.isPresent);
}

int main(int argc, char* argv[])
{
    int i = 1;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
