#include "unittests.h"
#include "tree.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

// Test_Registrar<TreeTests> TreeTests::registrar;

// bool TreeTests::threeElementBalance()
// {
// 	MySearchTree<int> tree;
// 	tree.insert(1);
// 	tree.insert(2);
// 	tree.insert(3);

// 	if (tree.balance() == 0)
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }

// bool TreeTests::sevenElementBalance()
// {
// 	MySearchTree<int> tree;
// 	tree.insert(1);
// 	tree.insert(2);
// 	tree.insert(3);
// 	tree.insert(4);
// 	tree.insert(5);
// 	tree.insert(6);
// 	tree.insert(7);

// 	if (tree.balance() == 0)
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }

// inserts 10k shuffled integers, checks if it contains() all of them
bool TreeTests::insertMany()
{
	std::srand ( unsigned ( std::time(0) ) );
	int numInts = 1000;
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
	int numInts = 100;
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

	for (int ii = 0; ii < vec.size(); ++ii)
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
bool TreeTests::singleElementTest() 
{
	int root = 2; 
	MySearchTree<int> tree; 
	if (tree.insert(root))
	{
		// continue
	}
	if ( !( tree.getRoot()->getVal() == root ) )
	{
		return false;
	} 

	if ( !tree.contains(root) )
	{
		return false;
	}

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