// VECTORIZED TREE
// -Implemented as a vector of Node pointers
// -To access a child...
//	 if it's L, it's located at 2x where x is the index of the parent
// 	 if it's R, it's located at 2x + 1
// -Pointers are used because they can be set to null when the vector is resized. Null values indicate
//      the index is 'open' and can be filled with a new child node
// -The tree starts at index 1 instead of 0 so that it can support this parent/child data access system
// 
// Functions
//    1) insert
//    2) remove
//    3) contains
//    4) balance
//    5) rank
//    6) size
//    7) prettyPrint (or overloaded <<)
// 
// NEW PATTERNS IMPLEMENTED
// 1) many things are const
// 2) the templated type is always passed by const ref so it is only ever copied once
// 
// Author: Chris Lee
// Date: April 22nd, 2018
// Last edited: May 15th, 2018
#ifndef __TREE__
#define __TREE__

#include <memory>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>

#define ROOT_INDEX 1

template<typename T> 
class MySearchTree 
{
private:
	class Node
	{
	public:
		Node(const T& value): m_data(value) {}
		const T& getVal() const { return m_data; }

	private:
		const T m_data;
	};
    struct ValStruct
    {
        ValStruct(std::shared_ptr<Node>& ptr): m_data(ptr->getVal()), m_ptr(ptr) {}
        const T& m_data;
        std::shared_ptr<Node> m_ptr;
    };

public: 
    MySearchTree(std::function<int(T,T)> comparator = cmp): compare(comparator) 
    {
        m_nodePtrs.resize(2);
        m_nodePtrs[ROOT_INDEX] = nullptr;
    }

    // NOTE: This only works with integers because of the charWidth calculation
    // This function prints all rows of the tree beginning at the root. It divides the area into 
    // preCharSpace and branchSpace. preCharSpace is any part of the row that doesn't contain branching.
    // For example, the space before printing the root is the preCharSpace because there are no branches
    // above the root. For two L/R child pairs, the space before the first L is preCharSpace along with 
    // the space between the pairs. branchSpace is the space from child to parent for each node, inclusive.
    void prettyPrint()
    {
        // print nothing if tree is empty
        if (!exists(m_nodePtrs[ROOT_INDEX]))
        {
            return;
        }

        std::vector<int> printOrder;
        int h = getHeight(ROOT_INDEX);
        int totalLines = h + 1;
        int line = 1; 
        printOrder.clear();
        printOrder.push_back(ROOT_INDEX);
        int preCharSpace;
        int parentCurrent;
        int parentPrevious;
        std::string valLine;
        std::string midLine;
        std::string loLine;
        int charWidth = 0;
        int largestVal = m_nodePtrs[largest(ROOT_INDEX)]->getVal();
        while (largestVal > 0)
        {
            largestVal = largestVal / 10;
            ++charWidth;
        }

        while (line <= totalLines)
        {
            if (line == 1)
            {
                valLine = "";
                preCharSpace = nodeRank(ROOT_INDEX);
                preCharSpace = preCharSpace * charWidth;
                addSpaces(valLine, preCharSpace);
                std::string currentVal = std::to_string(m_nodePtrs[ROOT_INDEX]->getVal());
                valLine += currentVal;
                std::cout << valLine << std::endl;
            }

            else
            {
                valLine = "";
                midLine = "";
                loLine = "";
                for (int ii = 0; ii < printOrder.size(); ++ii)
                {
                    if (isRightChild(printOrder[ii]))
                    {
                        if (ii == 0) // first value on line
                        {
                            parentCurrent = printOrder[ii] / 2;
                            preCharSpace = nodeRank(parentCurrent);
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceRight(printOrder[ii], charWidth, midLine, loLine, valLine);                            
                        }
                        else if ((printOrder[ii-1] + 1) == printOrder[ii]) // has sibling
                        {
                            // no preCharSpace necessary, because there is only branchingSpace between siblings
                            addBranchSpaceRight(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                        else if (isRightChild(printOrder[ii-1])) // previous val is right child
                        {
                            // subtract 1 character width because we printed the parent column already
                            parentCurrent = printOrder[ii] / 2;
                            preCharSpace = nodeRank(parentCurrent) - (1 + nodeRank(printOrder[ii-1]));
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceRight(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                        else // previous val is left child
                        {
                            parentCurrent = printOrder[ii] / 2;
                            parentPrevious = printOrder[ii - 1] / 2;
                            preCharSpace = nodeRank(parentCurrent) - (1 + nodeRank(parentPrevious));
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceRight(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                    }

                    else // left child
                    {
                        if (ii == 0) // first value on line
                        {
                            preCharSpace = nodeRank(printOrder[ii]);
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceLeft(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                        else if (isRightChild(printOrder[ii-1])) // previous val is a right child
                        {
                            preCharSpace = nodeRank(printOrder[ii]) - (1 + nodeRank(printOrder[ii-1]));
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceLeft(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                        else // previous val is a left child
                        {
                            parentPrevious = printOrder[ii - 1] / 2;
                            preCharSpace = nodeRank(printOrder[ii]) - (1 + nodeRank(parentPrevious));
                            preCharSpace = preCharSpace * charWidth;
                            addSpaces(midLine, loLine, valLine, preCharSpace);
                            addBranchSpaceLeft(printOrder[ii], charWidth, midLine, loLine, valLine);
                        }
                    }
                }
                std::cout << midLine << std::endl;
                std::cout << loLine << std::endl;
                std::cout << valLine << std::endl;
            }
            getNextRow(printOrder);
            ++line;
        }
    }

    int balance()
    {
        getSortedVals(1);
    	// reset tree to empty vector of size 2
    	m_nodePtrs.clear();
    	m_nodePtrs.push_back(std::shared_ptr<Node>());
    	m_nodePtrs.push_back(std::shared_ptr<Node>());

    	medianBalance(m_sortedVals, 0, m_sortedVals.size());

        return getNumBarren(1);
    }

	bool insert(const T& value)
    {
    	int pos = findIndex(value);

    	// if the spot is empty, we can insert it
        if (!static_cast<bool>(m_nodePtrs[pos]))
        {
        	m_nodePtrs[pos] = std::make_shared<MySearchTree<T>::Node>(value);
        	// balance();
        	return true; 
        }
        // if the spot is taken, it means this is a duplicate
        else
        {
        	return false;
        }
    }

	bool remove(const T& value)
    {
    	int toRemove = findIndex(value);

    	// if the spot is empty, we can't remove anything
        if (!static_cast<bool>(m_nodePtrs[toRemove]))
        {
        	return false;
        }

        // if the node has no children, we can safely remove it
        if (!hasChildren(toRemove))
        {
        	m_nodePtrs[toRemove].reset();
        	return true; 
        }

        else
        {
        	if (hasR(toRemove))
        	{
        		// if R doesn't have a left child, we need to manually swap it. Otherwise
        		// smallest() will find the smallest of R rather than toRemove
        		if (!hasL(toRemove * 2 + 1))
        		{
        			int toSwap = toRemove * 2 + 1;
	        		swap(m_nodePtrs, toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}
        		else
        		{
	        		int toSwap = smallest(toRemove * 2 + 1);
	        		swap(m_nodePtrs, toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}

        		while(hasChildren(toRemove))
        		{
        			int toSwap = smallest(toRemove);
        			swap(m_nodePtrs, toRemove, toSwap);
	        		toRemove = toSwap;
        		}

        		// at this point the node has no children, so we can delete it
        		m_nodePtrs[toRemove].reset();
        		return true;
        	}
        	else if (hasL(toRemove))
        	{
        		if (!hasR(toRemove * 2))
        		{
        			int toSwap = toRemove * 2;
	        		swap(m_nodePtrs, toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}
        		else
        		{
	        		int toSwap = largest(toRemove * 2);
	        		swap(m_nodePtrs, toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}

        		while(hasChildren(toRemove))
        		{
        			int toSwap = largest(toRemove);
        			swap(m_nodePtrs, toRemove, toSwap);
	        		toRemove = toSwap;
        		}

        		// at this point the node has no children, so we can delete it
        		m_nodePtrs[toRemove].reset();
        		return true;        		
        	}
        }  
        return false;   	
    }



	bool contains(const T& value)
    {
    	int pos = findIndex(value);

    	// if the spot is empty, our tree doesn't contain the value
        if (!static_cast<bool>(m_nodePtrs[pos]))
        {
        	return false;
        }
        // otherwise it contains the value
        else
        {
        	return true;
        }        	
    }

	MySearchTree::Node* getRoot()
    {
        return m_nodePtrs[1].get();
    }

    int rank(const T& value)
    {
        if (!contains(value))
        {
            return 0;
        }

        int pos = findIndex(value);
        return nodeRank(pos);
    }

    int size(const T& value)
    {
        if (!contains(value))
        {
            return 0;
        }

        int pos = findIndex(value);
        return nodeSize(pos);
    }

private:
	std::vector<std::shared_ptr<Node> > m_nodePtrs;
	std::function<int(T,T)> compare;
	std::vector<ValStruct> m_sortedVals;

    bool isRightChild(int index)
    {
        if (index == ROOT_INDEX)
        {
            return false;
        }
        if (index == ((index / 2) * 2 + 1))
        {
            return true;
        }
        return false; 
    }

    bool areSiblings(int lhs, int rhs)
    {
        if ((lhs/2) * 2 + 1 == rhs)
        {
            return true;
        }
        if ((lhs/2) * 2 == rhs)
        {
            return true;
        }
        return false;
    }

    void addSpaces(std::string& line, int spaces)
    {
        for (int ii = 0; ii < spaces; ++ii)
        {
            line += " ";
        }
    }

    void addSpaces(std::string& line1, std::string& line2, std::string& line3, int spaces)
    {
        for (int ii = 0; ii < spaces; ++ii)
        {
            line1 += " ";
            line2 += " ";
            line3 += " ";
        }
    }

    // this assumes index != root 
    // branch space is from the parent twig to the child twig, inclusive
    void addBranchSpaceLeft(int index, int charWidth, std::string& midLine, std::string& loLine, std::string& valLine)
    {
        int parent = index / 2;
        // add 1 here because we want to include the parent column
        int branchSpace = 1 + nodeRank(parent) - nodeRank(index); 
        branchSpace = branchSpace * charWidth;

        addUnderscores(midLine, branchSpace - charWidth);
        midLine += "|";
        if (exists(m_nodePtrs[index + 1])) // check whether this is a sibling
        {
            addUnderscores(midLine, charWidth - 1); // subtract 1 because we added a "|" already
        }
        else
        {
            addSpaces(midLine, charWidth - 1); // subtract 1 because we added a "|" already
        }

        loLine += "|";
        addSpaces(loLine, branchSpace - 1); // subtract 1 to make space for the "|"

        std::string currentVal = std::to_string(m_nodePtrs[index]->getVal());
        valLine += currentVal;
        addSpaces(valLine, branchSpace - currentVal.size());
    }

    // this assumes index != root 
    // branch space is from the parent twig to the child twig, inclusive
    void addBranchSpaceRight(int index, int charWidth, std::string& midLine, std::string& loLine, std::string& valLine)
    {
        int parent = index / 2;
        int branchSpace = 1 + nodeRank(index) - nodeRank(parent);  
        branchSpace = branchSpace * charWidth;
        std::string currentVal = std::to_string(m_nodePtrs[index]->getVal());    
        int missingSpace = charWidth - currentVal.size();    

        if (exists(m_nodePtrs[index - 1])) // check if previous is its sibling
            // if the sibling exists, it is guaranteed to be the previous value in the print order because
            // the print function prints from left to right in the tree 
        {
            // No midLine "|" necessary because the left sibling should have printed it already
            // Subtracting charWidth because the parent column is accounted for already
            addUnderscores(midLine, branchSpace - charWidth - charWidth + 1);
            addSpaces(midLine, charWidth - 1);

            addSpaces(loLine, branchSpace - charWidth - charWidth);
            loLine += "|";
            addSpaces(loLine, charWidth - 1);

            addSpaces(valLine, branchSpace - charWidth - charWidth);
            valLine += currentVal;
            addSpaces(valLine, missingSpace);
        }

        else
        {
            midLine += "|";
            addUnderscores(midLine, branchSpace - charWidth);
            addSpaces(midLine, charWidth - 1);

            addSpaces(loLine, branchSpace - charWidth);
            loLine += "|";
            addSpaces(loLine, charWidth - 1);            

            std::string currentVal = std::to_string(m_nodePtrs[index]->getVal());    
            int missingSpace = charWidth - currentVal.size();    
            addSpaces(valLine, branchSpace - charWidth);
            valLine += currentVal;
            addSpaces(valLine, missingSpace);
        }
    }

    void addUnderscores(std::string& line, int underscores)
    {
        for (int ii = 0; ii < underscores; ++ii)
        {
            line += "_";
        }
    }

    int getHeight(int index)
    {
        if (!exists(m_nodePtrs[index]))
        {
            return 0;
        }

        if (!withinCapacity(index * 2 + 1))
        {
            incCapacity();
        }

        int sizeL = getHeight(index * 2);
        int sizeR = getHeight(index * 2 + 1);

        if (index == 1)
        {
            // height starts at 0 for the first line 
            --sizeL;
            --sizeR;
        }

        if ( sizeL > sizeR )
        {
            return 1 + sizeL;
        }
        else
        {
            return 1 + sizeR;
        }
    }

    int nodeRank(int index)
    {
        // verify the node is not null 
        if (!exists(m_nodePtrs[index]))
        {
            return 0;
        }

        int current{ROOT_INDEX};
        int rankSum{0};

        while(true)
        {
            if (!withinCapacity(current * 2 + 1))
            {
                incCapacity();
            }

            if (index == current)
            {
                return rankSum + nodeSize(current * 2);
            }
            else if (m_nodePtrs[index]->getVal() > m_nodePtrs[current]->getVal())
            {
                rankSum += nodeSize(current * 2) + 1; // add 1 to include the parent in the rank
                current = current * 2 + 1; 
            }
            else // index val < current val
            {
                current = current * 2;
            }
        }
    }

    int nodeSize(int index)
    {
        if (!exists(m_nodePtrs[index]))
        {
            return 0;
        }

        if (!withinCapacity(index * 2 + 1))
        {
            incCapacity();
        }

        getSortedVals(index);
        return m_sortedVals.size();
    }

    void getNextRow(std::vector<int>& vec)
    {
        std::vector<int> newVec;
        for (int ii : vec)
        {
            if (ii == 0)
            {
                continue;
            }
            else
            {
                if (!withinCapacity(ii * 2 + 1))
                {
                    incCapacity();
                }

                if (exists(m_nodePtrs[ii * 2]))
                {
                    newVec.push_back(ii * 2);
                }
                if (exists(m_nodePtrs[ii * 2 + 1]))
                {
                    newVec.push_back(ii * 2 + 1);
                }
            }
        }
        std::swap(vec, newVec);
    }

    bool exists(std::shared_ptr<Node>& ptr)
    {
        return static_cast<bool>(ptr);
    }

    // Makes m_sortedVals a sorted vector of the subtree denoted by startingIndex in linear time
    // 1) goes to minimum value (leftmost node)
    // 2) checks left; if left exists and is not already in m_sortedVals it travels there
    // 3) checks current node; if current is not in m_sortedVals it adds it
    // 4) checks right; if right is not in m_sortedVals it travels there
    // 5) travels upwards. if the current node is our starting node we stop here rather than traveling upwards
    void getSortedVals(int startingIndex)
    {
        m_sortedVals.clear();
        int currentInd = startingIndex;

        // base case: wants to climb above the starting index
        while (true)
        {
            if (!withinCapacity(currentInd * 2 + 1))
            {
                incCapacity();
            }
            // check left
            if (static_cast<bool>(m_nodePtrs[currentInd * 2]))
            {
                if ((!m_sortedVals.empty()) && (compare(m_nodePtrs[currentInd * 2]->getVal(), m_sortedVals.back().m_data) <= 0))
                {
                    // ignore, since the value is already in m_sortedVals if it's less than the end element. m_sortedVals
                    // will only be empty when we're finding the leftmost node to start, and we don't want to do comparisons
                    // if it's empty. 
                }
                else
                {
                    currentInd = currentInd * 2; // go left
                    continue;
                }
            }

            // check current
            if (m_sortedVals.empty())
            {
                m_sortedVals.push_back(ValStruct(m_nodePtrs[currentInd]));
            }
            else if ( compare(m_nodePtrs[currentInd]->getVal(), m_sortedVals.back().m_data) == 1 )
            {
                m_sortedVals.push_back(ValStruct(m_nodePtrs[currentInd]));
            }

            // check right
            if (static_cast<bool>(m_nodePtrs[currentInd * 2 + 1]))
            {
                if ( compare(m_nodePtrs[currentInd * 2 + 1]->getVal(), m_sortedVals.back().m_data) == 1)
                {
                    currentInd = currentInd * 2 + 1; // go right
                    continue;
                }
                else
                {
                    // ignore
                }
            }

            // check stop condition
            if ( currentInd == startingIndex )
            {
                break;
            }
            else
            {
                currentInd = currentInd / 2; // climb up
            }
        }
    }

    // where barren = no children
    // Note: this algorithm is nearly identical to getSortedVals()
    int getNumBarren(int startingIndex)
    {
        m_sortedVals.clear();
        int currentInd = startingIndex;
        int numChildren = 0;
        int numBarren = 0;

        while (true)
        {
            if (!withinCapacity(currentInd * 2 + 1))
            {
                incCapacity();
            }
            numChildren = 0;

            // check left
            if (static_cast<bool>(m_nodePtrs[currentInd * 2]))
            {
                numChildren++;
                if ((!m_sortedVals.empty()) && (compare(m_nodePtrs[currentInd * 2]->getVal(), m_sortedVals.back().m_data) <= 0))
                {
                    // ignore, since the value is already in m_sortedVals if it's less than the end element. m_sortedVals
                    // will only be empty when we're finding the leftmost node to start, and we don't want to do comparisons
                    // if it's empty. 
                }
                else
                {
                    currentInd = currentInd * 2; // go left
                    continue;
                }
            }

            // check current
            if (m_sortedVals.empty())
            {
                m_sortedVals.push_back(ValStruct(m_nodePtrs[currentInd]));
            }
            else if ( compare(m_nodePtrs[currentInd]->getVal(), m_sortedVals.back().m_data) == 1 )
            {
                m_sortedVals.push_back(ValStruct(m_nodePtrs[currentInd]));
            }

            // check right
            if (static_cast<bool>(m_nodePtrs[currentInd * 2 + 1]))
            {
                numChildren++;
                if ( compare(m_nodePtrs[currentInd * 2 + 1]->getVal(), m_sortedVals.back().m_data) == 1)
                {
                    currentInd = currentInd * 2 + 1; // go right
                    continue;
                }
                else
                {
                    // ignore
                }
            }

            if (numChildren == 0)
            {
                // std::cout << "barren found at index " << currentInd << "\n";
                numBarren++;
            }

            // check stop condition
            if ( currentInd == startingIndex )
            {
                return numBarren;
            }
            else
            {
                currentInd = currentInd / 2; // climb up
            }
        }

    }

    void medianBalance(const std::vector<ValStruct>& vals, int beg, int end)
    {
    	// Base cases: subarray of size 0 or 1
    	if (end - beg == 1)
    	{
    		medianInsert(vals, beg);
    		return;
    	}
    	else if (end - beg == 0)
    	{
    		return;
    	}
    	else
    	{
    		int mid = beg + (end - beg) / 2;
    		medianInsert(vals, mid);
    		medianBalance(vals, beg, mid);
    		medianBalance(vals, mid+1, end);
    	}
    }

    void medianInsert(const std::vector<ValStruct>& vals, int valPos)
    {
    	int treePos = findIndex(vals[valPos].m_data);
    	m_nodePtrs[treePos] = vals[valPos].m_ptr;
    }

	int findIndex (const T& value)
	{
		int currentInd = ROOT_INDEX; 

        // we'll continue traversing the tree until the value's location is found
        while (true)
        {
        	// if the spot is empty, return the index
        	if (!static_cast<bool>(m_nodePtrs[currentInd]))
        	{
        		return currentInd;
        	}

        	// if the value is already in the tree, return the index 
            else if (compare(value, m_nodePtrs[currentInd]->getVal()) == 0)
            {
                return currentInd;
            }

            else
            {
            	currentInd = getNext(value, currentInd);
            }   
        }
	}

	int getNext (const T& value, int currentInd)
	{
    	if (!withinCapacity(currentInd * 2 + 1))
    	{
    		incCapacity();
    	}

		if (compare(value, m_nodePtrs[currentInd]->getVal()) == 1)
		{
			return currentInd * 2 + 1; // go right
		}

		else if (compare(value, m_nodePtrs[currentInd]->getVal()) == -1)
		{
			return currentInd * 2; // go left 
		}

        return 0;
	}

    static int cmp(const T& val1,const T& val2)
    {
        if (val1 < val2) 
        {
            return -1;
        }
        else if (val1 > val2) 
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }

	int largest(int currentInd)
    {
        if ( !hasChildren(currentInd) )
        {
            return currentInd;
        }

		if (hasR(currentInd))
		{
			while (hasR(currentInd))
			{
				currentInd = currentInd * 2 + 1;
			}
			return currentInd;
		}
		else
		{
			currentInd = currentInd * 2;
			while (hasR(currentInd))
			{
				currentInd = currentInd * 2 + 1;
			}
			return currentInd;			
		}
        
    }

	int smallest(int currentInd)
    {
        if ( !hasChildren(currentInd) )
        {
            throw std::invalid_argument( "Cannot find largest child of node without children" );
        }

		if (hasL(currentInd))
		{
			while (hasL(currentInd))
			{
				currentInd = currentInd * 2;
			}
			return currentInd;
		}  
		else
		{
			currentInd = currentInd * 2 + 1;
			while (hasL(currentInd))
			{
				currentInd = currentInd * 2;
			}
			return currentInd;			
		}      
    }

    bool hasChildren(const int& currentInd)
    {
    	if (!withinCapacity(currentInd * 2 + 1))
    	{
    		incCapacity();
    	}

    	if (static_cast<bool>(m_nodePtrs[currentInd * 2]) || static_cast<bool>(m_nodePtrs[currentInd * 2 + 1]))
    	{
    		return true;
    	}
    	return false;
    }

    bool hasR(const int& currentInd)
    {
    	if (!withinCapacity(currentInd * 2 + 1))
    	{
    		incCapacity();
    	}

    	if (static_cast<bool>(m_nodePtrs[currentInd * 2 + 1]))
    	{
    		return true;
    	}
    	return false;
    }

    bool hasL(const int& currentInd)
    {
    	if (!withinCapacity(currentInd * 2 + 1))
    	{
    		incCapacity();
    	}

    	if (static_cast<bool>(m_nodePtrs[currentInd * 2]))
    	{
    		return true;
    	}
    	return false;
    }

    bool withinCapacity(const uint32_t ind) 
    {
    	if (ind < m_nodePtrs.size())
    	{
    		return true;
    	}
    	return false; 
    }

    void incCapacity()
    {
    	// double the size of our vector (and add 1) and insert a bunch of nullptrs
    	int newSize = m_nodePtrs.size() + 1;
    	for (int i = 0; i < newSize; ++i)
    	{
	    	m_nodePtrs.push_back(std::shared_ptr<Node>());
    	}
    }

	void swap(std::vector<std::shared_ptr<Node> >& vec, int lInd, int rInd)
    {
        auto temp = vec[lInd];
        vec[lInd] = vec[rInd];
        vec[rInd] = temp;
    } 

};

template<typename T>
std::ostream& operator<< (std::ostream& os, MySearchTree<T>& tree) 
{
    tree.prettyPrint();

    return os;
}

#endif