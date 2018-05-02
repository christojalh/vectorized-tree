#ifndef UNITTESTS
#define UNITTESTS

#include <map>
#include "tree.h"
#include <iostream>

class TreeTests
{
	public:
	  void Run()
	  {
  	    m_results["insertMany:\t"] = insertMany();
	    m_results["deleteMany:\t"] = deleteMany();
	    m_results["singleElementTest:"] = singleElementTest();
	    // m_results["threeElementBalance:"] = threeElementBalance();
	    m_results["sevenElementBalance:"] = sevenElementBalance();
	    
	    std::cout << "Running tree tests...\n";
	    for (auto& it : m_results)
	    {
	      std::cout << it.first << "\t" << (it.second ? "PASSED" : "\033[1;31mFAILED\033[0m") << std::endl;
	    }	  
	    std::cout << "\n";
	  }

	private:
	  static bool insertMany();
	  static bool deleteMany();
	  static bool singleElementTest();
	  static bool threeElementBalance(); // height 2
	  static bool sevenElementBalance(); // height 3

	  std::map<std::string, bool> m_results;
};

#endif