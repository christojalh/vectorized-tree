#ifndef __UNITTESTS__
#define __UNITTESTS__

#include <test_helpers.h>

class TreeTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(TreeTests::case1_PrintTest);
        ADD_TEST(TreeTests::case2_PrintTest);
        ADD_TEST(TreeTests::case3_PrintTest);
        ADD_TEST(TreeTests::case4_PrintTest);
        ADD_TEST(TreeTests::case5_PrintTest);
        ADD_TEST(TreeTests::case6_PrintTest);
        ADD_TEST(TreeTests::case7_PrintTest);
        ADD_TEST(TreeTests::case8_PrintTest);
        ADD_TEST(TreeTests::largePrintTest);
        ADD_TEST(TreeTests::insertMany);
        ADD_TEST(TreeTests::deleteMany);
        ADD_TEST(TreeTests::singleElementTest);
        ADD_TEST(TreeTests::threeElementBalance);
        ADD_TEST(TreeTests::sevenElementBalance);
        ADD_TEST(TreeTests::rankTest);
        ADD_TEST(TreeTests::sizeTest);
    }

private:
    static bool case1_PrintTest();
    static bool case2_PrintTest();
    static bool case3_PrintTest();
    static bool case4_PrintTest();
    static bool case5_PrintTest();
    static bool case6_PrintTest();
    static bool case7_PrintTest();
    static bool case8_PrintTest();
    static bool largePrintTest();
	static bool insertMany();
	static bool deleteMany();
	static bool singleElementTest();
	static bool threeElementBalance(); // height 2
	static bool sevenElementBalance(); // height 3
    static bool rankTest();
    static bool sizeTest();

    static Test_Registrar<TreeTests> registrar;
};

#endif