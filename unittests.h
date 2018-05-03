#ifndef __UNITTESTS__
#define __UNITTESTS__

#include <test_helpers.h>

class TreeTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(TreeTests::prettyPrintTest);
        ADD_TEST(TreeTests::insertMany);
        ADD_TEST(TreeTests::deleteMany);
        ADD_TEST(TreeTests::singleElementTest);
        ADD_TEST(TreeTests::threeElementBalance);
        ADD_TEST(TreeTests::sevenElementBalance);
    }

private:
    static bool prettyPrintTest();
	static bool insertMany();
	static bool deleteMany();
	static bool singleElementTest();
	static bool threeElementBalance(); // height 2
	static bool sevenElementBalance(); // height 3

    static Test_Registrar<TreeTests> registrar;
};

#endif