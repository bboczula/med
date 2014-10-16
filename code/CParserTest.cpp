#include "gtest/gtest.h"
#include "CParser.h"
#include <string>

class CParserTest : public ::testing::Test
{
public:
    CParser parser;
    CCommandMetadata* result;
    void assertCommandPresent(std::string expCmd)
    {
        ASSERT_TRUE(result->command.isPresent);
        ASSERT_EQ(result->command.value, expCmd);
    }
    void assertCommandNotPresent()
    {
        ASSERT_FALSE(result->command.isPresent);
    }
    void parseCommand(std::string cmd)
    {
        result = parser.parse(cmd);
    }
protected:
    virtual void SetUp()
    {
    }
};

TEST_F(CParserTest, emptyCommand)
{
    parseCommand("");
    ASSERT_TRUE(result == 0);
}

TEST_F(CParserTest, oneDigitOnly)
{
    parseCommand("1");
    assertCommandPresent("p");
    ASSERT_TRUE(result->startAddress.isPresent);
    ASSERT_EQ(result->startAddress.value, 0);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, twoDigitOnly)
{
    parseCommand("12");
    assertCommandPresent("p");
    ASSERT_TRUE(result->startAddress.isPresent);
    ASSERT_EQ(result->startAddress.value, 11);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, singlePrint)
{
    parseCommand("p");
    assertCommandPresent("p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, startRangeOnlyPrint)
{
    parseCommand("2p");
    assertCommandPresent("p");
    ASSERT_TRUE(result->startAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->startAddress.value, 1);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, endRangeOnlyPrint)
{
    parseCommand(",5p");
    assertCommandPresent("p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_TRUE(result->endAddress.isPresent);
    ASSERT_EQ(result->endAddress.value, 4);
}

TEST_F(CParserTest, fullRangeOnlyPrint)
{
    parseCommand("2,3p");
    assertCommandPresent("p");
    ASSERT_TRUE(result->startAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->startAddress.value, 1);
    ASSERT_TRUE(result->endAddress.isPresent);
    // Orginal line is decreased by one (addressing in storage)
    ASSERT_EQ(result->endAddress.value, 2);
}

TEST_F(CParserTest, separatorRangeOnlyPrint)
{
    parseCommand(",p");
    assertCommandPresent("p");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_FALSE(result->endAddress.isPresent);
}

TEST_F(CParserTest, singlePrintWithLineNum)
{
    parseCommand("n");
    assertCommandPresent("n");
    ASSERT_FALSE(result->startAddress.isPresent);
    ASSERT_FALSE(result->endAddress.isPresent);
}

int main(int argc, char* argv[])
{
    int i = 1;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
