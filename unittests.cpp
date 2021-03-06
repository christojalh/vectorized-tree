#include "unittests.h"
#include "tree.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <sstream>

Test_Registrar<TreeTests> TreeTests::registrar;

bool TreeTests::case1_PrintTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(5));
	std::stringstream printOutput;
	tree.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "5" << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << tree;
	return true; 
}

bool TreeTests::case2_PrintTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(5));
	VERIFY_TRUE(tree.insert(8));
	VERIFY_TRUE(tree.insert(3));
	std::stringstream printOutput;
	tree.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << " 5"  << std::endl;
	correctOutput << "_|_" << std::endl;
	correctOutput << "| |" << std::endl;
	correctOutput << "3 8" << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << tree;
	return true; 
}

bool TreeTests::case3_PrintTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(5));
	VERIFY_TRUE(tree.insert(8));
	VERIFY_TRUE(tree.insert(3));
	VERIFY_TRUE(tree.insert(2));
	VERIFY_TRUE(tree.insert(7));
	std::stringstream printOutput;
	tree.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "  5"   << std::endl;
	correctOutput << " _|__" << std::endl;
	correctOutput << " |  |" << std::endl;
	correctOutput << " 3  8" << std::endl;
	correctOutput << "_| _|" << std::endl;
	correctOutput << "|  | " << std::endl;
	correctOutput << "2  7 " << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << tree;
	return true; 
}

bool TreeTests::case4_PrintTest()
{
	MySearchTree<int> t;
	VERIFY_TRUE(t.insert(5));
	VERIFY_TRUE(t.insert(8));
	VERIFY_TRUE(t.insert(3));
	VERIFY_TRUE(t.insert(2));
	VERIFY_TRUE(t.insert(9));
	std::stringstream printOutput;
	t.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "  5"   << std::endl;
	correctOutput << " _|_"  << std::endl;
	correctOutput << " | |"  << std::endl;
	correctOutput << " 3 8"  << std::endl;
	correctOutput << "_| |_" << std::endl;
	correctOutput << "|   |" << std::endl;
	correctOutput << "2   9" << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << t;
	return true; 
}

bool TreeTests::case5_PrintTest()
{
	MySearchTree<int> r;
	VERIFY_TRUE(r.insert(5));
	VERIFY_TRUE(r.insert(8));
	VERIFY_TRUE(r.insert(3));
	VERIFY_TRUE(r.insert(4));
	VERIFY_TRUE(r.insert(7));
	std::stringstream printOutput;
	r.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "  5"   << std::endl;
	correctOutput << "__|__" << std::endl;
	correctOutput << "|   |" << std::endl;
	correctOutput << "3   8" << std::endl;
	correctOutput << "|_ _|" << std::endl;
	correctOutput << " | | " << std::endl;
	correctOutput << " 4 7 " << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << r;	
	return true; 
}

bool TreeTests::case6_PrintTest()
{
	MySearchTree<int> q;
	VERIFY_TRUE(q.insert(5));
	VERIFY_TRUE(q.insert(8));
	VERIFY_TRUE(q.insert(3));
	VERIFY_TRUE(q.insert(4));
	VERIFY_TRUE(q.insert(9));
	std::stringstream printOutput;
	q.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "  5"   << std::endl;
	correctOutput << "__|_"  << std::endl;
	correctOutput << "|  |"  << std::endl;
	correctOutput << "3  8"  << std::endl;
	correctOutput << "|_ |_" << std::endl;
	correctOutput << " |  |" << std::endl;
	correctOutput << " 4  9" << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << q;	
	return true; 
}

bool TreeTests::case7_PrintTest()
{
	MySearchTree<int> z;
	VERIFY_TRUE(z.insert(5));
	VERIFY_TRUE(z.insert(8));
	VERIFY_TRUE(z.insert(3));
	VERIFY_TRUE(z.insert(4));
	VERIFY_TRUE(z.insert(2));
	VERIFY_TRUE(z.insert(9));
	std::stringstream printOutput;
	z.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "   5"   << std::endl;
	correctOutput << " __|_"  << std::endl;
	correctOutput << " |  |"  << std::endl;
	correctOutput << " 3  8"  << std::endl;
	correctOutput << "_|_ |_" << std::endl;
	correctOutput << "| |  |" << std::endl;
	correctOutput << "2 4  9" << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << z;	
	return true; 
}

bool TreeTests::case8_PrintTest()
{
	MySearchTree<int> y;
	VERIFY_TRUE(y.insert(5));
	VERIFY_TRUE(y.insert(8));
	VERIFY_TRUE(y.insert(3));
	VERIFY_TRUE(y.insert(4));
	VERIFY_TRUE(y.insert(2));
	VERIFY_TRUE(y.insert(7));
	std::stringstream printOutput;
	y.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "   5"   << std::endl;
	correctOutput << " __|__" << std::endl;
	correctOutput << " |   |" << std::endl;
	correctOutput << " 3   8" << std::endl;
	correctOutput << "_|_ _|" << std::endl;
	correctOutput << "| | | " << std::endl;
	correctOutput << "2 4 7 " << std::endl;
	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << y;
	return true; 
}

bool TreeTests::largePrintTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(500));
	VERIFY_TRUE(tree.insert(7000));
	VERIFY_TRUE(tree.insert(300));
	VERIFY_TRUE(tree.insert(2));
	VERIFY_TRUE(tree.insert(8000));
	VERIFY_TRUE(tree.insert(6000));
	VERIFY_TRUE(tree.insert(4));
	VERIFY_TRUE(tree.insert(400));
	VERIFY_TRUE(tree.insert(450));
	std::stringstream printOutput;
	tree.prettyPrint(printOutput);
	std::stringstream correctOutput;
	correctOutput << "                    500"              << std::endl;
	correctOutput << "        ____________|________   "     << std::endl;
	correctOutput << "        |                   |   "     << std::endl;
	correctOutput << "        300                 7000"     << std::endl;
	correctOutput << "________|____           ____|____   " << std::endl;
	correctOutput << "|           |           |       |   " << std::endl;
	correctOutput << "2           400         6000    8000" << std::endl;
	correctOutput << "|____       |____   "                 << std::endl;
	correctOutput << "    |           |   "                 << std::endl;
	correctOutput << "    4           450 "                 << std::endl;

	VERIFY_EQ(printOutput.str(), correctOutput.str());

	std::cout << tree;

	return true; 
}

bool TreeTests::sizeTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(10));
	VERIFY_EQ(tree.size(10), 1);	
	VERIFY_TRUE(tree.insert(20));
	VERIFY_EQ(tree.size(20), 1);	
	VERIFY_TRUE(tree.insert(5));
	VERIFY_EQ(tree.size(20), 1);	
	VERIFY_TRUE(tree.insert(15));
	VERIFY_EQ(tree.size(15), 1);	
	VERIFY_EQ(tree.size(20), 2);	
	VERIFY_TRUE(tree.insert(17));
	VERIFY_EQ(tree.size(5), 1);		
	VERIFY_EQ(tree.size(10), 5);		
	VERIFY_EQ(tree.size(15), 2);	
	VERIFY_EQ(tree.size(17), 1);	
	VERIFY_EQ(tree.size(20), 3);	

	return true;
}

bool TreeTests::rankTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(10));
	VERIFY_EQ(tree.rank(10), 0);	
	VERIFY_TRUE(tree.insert(20));
	VERIFY_EQ(tree.rank(20), 1);	
	VERIFY_TRUE(tree.insert(5));
	VERIFY_EQ(tree.rank(20), 2);	
	VERIFY_TRUE(tree.insert(15));
	VERIFY_EQ(tree.rank(15), 2);	
	VERIFY_EQ(tree.rank(20), 3);	
	VERIFY_TRUE(tree.insert(17));
	VERIFY_EQ(tree.rank(5), 0);		
	VERIFY_EQ(tree.rank(10), 1);		
	VERIFY_EQ(tree.rank(15), 2);	
	VERIFY_EQ(tree.rank(17), 3);	
	VERIFY_EQ(tree.rank(20), 4);	

	return true;
}

bool TreeTests::threeElementBalance()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(1));
	VERIFY_EQ(tree.balance(), 1);	
	VERIFY_TRUE(tree.insert(2));
	VERIFY_EQ(tree.balance(), 1);	
	VERIFY_TRUE(tree.insert(3));
	VERIFY_EQ(tree.balance(), 2);	

	return true;
}

bool TreeTests::sevenElementBalance()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(1));
	VERIFY_TRUE(tree.insert(2));
	VERIFY_TRUE(tree.insert(3));
	VERIFY_TRUE(tree.insert(4));
	VERIFY_TRUE(tree.insert(5));
	VERIFY_TRUE(tree.insert(6));
	VERIFY_TRUE(tree.insert(7));
	VERIFY_EQ(tree.balance(), 4);

	return true;
}

// inserts 10k shuffled integers, checks if it contains() all of them
bool TreeTests::insertMany()
{
	std::srand ( unsigned ( std::time(0) ) );
	int numInts = 10;
	std::vector<int> vec;
	for (int ii = 0; ii < numInts; ++ii)
	{
		vec.push_back(ii);
	}
	std::random_shuffle(vec.begin(), vec.end());

	int root = rand() % numInts;
	MySearchTree<int> tree;
	if (tree.insert(root))
	{
		// continue
	}
	for (int ii = 0; ii < numInts; ++ii)
	{
		if (tree.insert(vec[ii])) 
		{
			// successful insert
		}
		else
		{
			// ignore duplicate 
		}
	}

	for (int ii = 0; ii < numInts; ++ii)
	{
		if (tree.contains(ii))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

// inserts 10k shuffled integers, chooses a random integer to leave alone, deletes the rest in a random fashion. Returns true if the value of the root is the chosen integer
bool TreeTests::deleteMany()
{
	int numInts = 10;
	std::srand ( unsigned ( std::time(0) ) );

	std::vector<int> vec;
	for (int ii = 0; ii < numInts; ++ii)
	{
		vec.push_back(ii);
	}
	std::random_shuffle(vec.begin(), vec.end());

	int root = rand() % numInts;
	int final = rand() % numInts; 

	while (root == final) 
	{
		final = rand() % numInts;
	}

	MySearchTree<int> tree;
	if (tree.insert(root))
	{
		// continue
	}

	for (int ii = 0; ii < numInts; ++ii)
	{
		if (tree.insert(vec[ii])) 
		{
			// successful insert
		}
		else
		{
			// ignore duplicate 
		}
	}

	std::random_shuffle(vec.begin(), vec.end());
	for (int ii = 0; ii < numInts; ++ii) 
	{
		if (final == vec[ii])
		{
			continue;
		}
		else if (tree.remove(vec[ii]))
		{

		}
		else
		{
			return false; // signifies we have somehow removed something twice
		}
	}

	if (tree.getRoot()->getVal() == final)
	{
		return true;			
	}
	return false;
}

// verifies basic insert(), contain(), remove() functionality
bool TreeTests::singleElementTest() 
{
	int root = 7; 
	MySearchTree<int> tree; 
	VERIFY_TRUE(tree.insert(root));
	VERIFY_EQ( tree.getRoot()->getVal(), root );
	VERIFY_TRUE( tree.contains(root) );
	if ( !( tree.insert(5) ) )
	{
		return false;
	}

	// inserting duplicate here
	if ( tree.insert(5) ) 
	{
		return false;
	}

	if ( !tree.contains(5) )
	{
		return false;
	}

	if ( !tree.remove(5) )
	{
		return false;
	}

	if ( tree.contains(5) )
	{
		return false; 
	}

	// remove a nonexistent value
	if ( tree.remove(5) ) 
	{
		return false;
	}

	return true;
}