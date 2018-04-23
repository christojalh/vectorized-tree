// VECTORIZED TREE
// Any time we make a node, we access the data through our vector of m_nodePtrs
// If we want to access a child...
//	 if it's L, it's located at 2x; x is the index of the parent
// 	 if it's R, it's located at 2x + 1
// If our vector needs to be resized, we'll insert a bunch of nullptrs to increase the size
// 	 this way we can check if the spot is occupied/contains a node 
// NOTE: m_nodePtrs starts at 1 instead of 0 so that it can support this parent/child data access system

// NEW:
// 1) many things are const
// 2) the templated type is always passed by const ref

#ifndef TREE
#define TREE

#include <memory>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <functional>

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

public: 
    MySearchTree(std::function<int(T,T)> comparator = cmp): compare(comparator) 
    {
        m_nodePtrs.resize(2);
        m_nodePtrs[1] = nullptr;
    }

	bool insert(const T& value)
    {
    	int pos = findIndex(value);

    	// if the spot is empty, we can insert it
        if (!static_cast<bool>(m_nodePtrs[pos]))
        {
        	m_nodePtrs[pos] = std::make_unique<MySearchTree<T>::Node>(value);
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
	        		swap(toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}
        		else
        		{
	        		int toSwap = smallest(toRemove * 2 + 1);
	        		swap(toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}

        		while(hasChildren(toRemove))
        		{
        			int toSwap = smallest(toRemove);
        			swap(toRemove, toSwap);
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
	        		swap(toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}
        		else
        		{
	        		int toSwap = largest(toRemove * 2);
	        		swap(toRemove, toSwap); 
	        		toRemove = toSwap;        			
        		}

        		while(hasChildren(toRemove))
        		{
        			int toSwap = largest(toRemove);
        			swap(toRemove, toSwap);
	        		toRemove = toSwap;
        		}

        		// at this point the node has no children, so we can delete it
        		m_nodePtrs[toRemove].reset();
        		return true;        		
        	}
        }    	
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

private:
	std::vector<std::unique_ptr<Node> > m_nodePtrs;
	std::function<int(T,T)> compare;	

	int findIndex (const T& value)
	{
		int currentInd = 1; 

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
            throw std::invalid_argument( "Cannot find largest child of node without children" );
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

    bool withinCapacity(const int& ind) 
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
	    	m_nodePtrs.push_back(std::unique_ptr<Node>());
    	}
    }

	void swap(int lInd, int rInd)
    {
        auto temp = std::move(m_nodePtrs[lInd]);
        m_nodePtrs[lInd] = std::move(m_nodePtrs[rInd]);
        m_nodePtrs[rInd] = std::move(temp);
    } 

};

#endif