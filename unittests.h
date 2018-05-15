#ifndef __UNITTESTS__
#define __UNITTESTS__

#include <test_helpers.h>

class TreeTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(TreeTests::smallPrintTest);
        ADD_TEST(TreeTests::largePrintTest);
        ADD_TEST(TreeTests::insertMany);
        ADD_TEST(TreeTests::deleteMany);
        ADD_TEST(TreeTests::singleElementTest, 7);
        ADD_TEST(TreeTests::threeElementBalance);
        ADD_TEST(TreeTests::sevenElementBalance);
        ADD_TEST(TreeTests::rankTest);
        ADD_TEST(TreeTests::sizeTest);
    }

private:
    static bool smallPrintTest();
    static bool largePrintTest();
	static bool insertMany();
	static bool deleteMany();
	static bool singleElementTest(int num);
	static bool threeElementBalance(); // height 2
	static bool sevenElementBalance(); // height 3
    static bool rankTest();
    static bool sizeTest();

    static Test_Registrar<TreeTests> registrar;
};

#endif