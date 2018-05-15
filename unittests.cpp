#include "unittests.h"
#include "tree.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

Test_Registrar<TreeTests> TreeTests::registrar;

bool TreeTests::smallPrintTest()
{
	MySearchTree<int> tree;
	VERIFY_TRUE(tree.insert(5));
	std::cout << tree;

	VERIFY_TRUE(tree.insert(8));
	VERIFY_TRUE(tree.insert(3));
	std::cout << tree;

	VERIFY_TRUE(tree.insert(2));
	VERIFY_TRUE(tree.insert(7));
	VERIFY_TRUE(tree.insert(6));
	VERIFY_TRUE(tree.insert(1));
	VERIFY_TRUE(tree.insert(4));
	VERIFY_TRUE(tree.insert(9));
	std::cout << tree;

	VERIFY_TRUE(tree.remove(5));
	VERIFY_TRUE(tree.remove(6));
	std::cout << tree;

	MySearchTree<int> t;
	VERIFY_TRUE(t.insert(5));
	VERIFY_TRUE(t.insert(8));
	VERIFY_TRUE(t.insert(3));
	VERIFY_TRUE(t.insert(2));
	VERIFY_TRUE(t.insert(9));
	std::cout << t;

	MySearchTree<int> r;
	VERIFY_TRUE(r.insert(5));
	VERIFY_TRUE(r.insert(7));
	VERIFY_TRUE(r.insert(9));
	VERIFY_TRUE(r.insert(8));
	VERIFY_TRUE(r.insert(2));
	VERIFY_TRUE(r.insert(1));
	std::cout << r;	
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
	VERIFY_TRUE(tree.insert(1));
	VERIFY_TRUE(tree.insert(400));
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
	// std::cout << "Final: " << final << "\n";
	// std::cout << "Root: " << tree.getRoot()->getVal() << "\n";
	// std::cout << "Insertion sequence: ";

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

	// std::cout << "Value of root: " << tree.getRoot()->getVal() << "\n\n";
	if (tree.getRoot()->getVal() == final)
	{
		return true;			
	}
	return false;
}

// verifies basic insert(), contain(), remove() functionality
bool TreeTests::singleElementTest(int num) 
{
	int root = num; 
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