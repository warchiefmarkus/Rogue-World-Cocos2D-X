//--------------------------------------FSA---------------------------------------------//
/*
A* Algorithm Implementation using STL is
Copyright (C)2001-2005 Justin Heyes-Jones

Permission is given by the author to freely redistribute and 
include this code in any program as long as this credit is 
given where due.
 
  COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, 
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
  INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE COVERED CODE 
  IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
  OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND 
  PERFORMANCE OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED 
  CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL 
  DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY 
  NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
  WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE 
  OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
  THIS DISCLAIMER.
 
  Use at your own risk!

*/


#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
/* 

A* Algorithm Implementation using STL is
Copyright (C)2001-2005 Justin Heyes-Jones

Permission is given by the author to freely redistribute and 
include this code in any program as long as this credit is 
given where due.
 
  COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, 
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
  INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE COVERED CODE 
  IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
  OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND 
  PERFORMANCE OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED 
  CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL 
  DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY 
  NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
  WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE 
  OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
  THIS DISCLAIMER.
 
  Use at your own risk!



  FixedSizeAllocator class
  Copyright 2001 Justin Heyes-Jones

  This class is a constant time O(1) memory manager for objects of 
  a specified type. The type is specified using a template class.

  Memory is allocated from a fixed size buffer which you can specify in the
  class constructor or use the default.

  Using GetFirst and GetNext it is possible to iterate through the elements
  one by one, and this would be the most common use for the class. 

  I would suggest using this class when you want O(1) add and delete
  and you don't do much searching, which would be O(n). Structures such as binary 
  trees can be used instead to get O(logn) access time.

*/


#include <string.h>
#include <stdio.h>

template <class USER_TYPE> class FixedSizeAllocator
{

public: 
	// Constants
	enum
	{
		FSA_DEFAULT_SIZE = 100
	};

	// This class enables us to transparently manage the extra data 
	// needed to enable the user class to form part of the double-linked
	// list class
	struct FSA_ELEMENT
	{
		USER_TYPE UserType;
		
		FSA_ELEMENT *pPrev;
		FSA_ELEMENT *pNext;
	};

public: // methods
	FixedSizeAllocator( unsigned int MaxElements = FSA_DEFAULT_SIZE ) :
	m_MaxElements( MaxElements ),
	m_pFirstUsed( NULL )
	{
		// Allocate enough memory for the maximum number of elements

		m_pMemory = (FSA_ELEMENT *) (new char[ m_MaxElements * sizeof(FSA_ELEMENT) ]); 

		// Set the free list first pointer
		m_pFirstFree = m_pMemory;

		// Clear the memory
		memset( m_pMemory, 0, sizeof( FSA_ELEMENT ) * m_MaxElements );

		// Point at first element
		FSA_ELEMENT *pElement = m_pFirstFree;

		// Set the double linked free list
		for( unsigned int i=0; i<m_MaxElements; i++ )
		{
			pElement->pPrev = pElement-1;
			pElement->pNext = pElement+1;

			pElement++;
		}

		// first element should have a null prev
		m_pFirstFree->pPrev = NULL;
		// last element should have a null next
		(pElement-1)->pNext = NULL;

	}


	~FixedSizeAllocator()
	{
		// Free up the memory
		delete [] (char *) m_pMemory;
	}

	// Allocate a new USER_TYPE and return a pointer to it 
	USER_TYPE *alloc()
	{

		FSA_ELEMENT *pNewNode = NULL;

		if( !m_pFirstFree )
		{
			return NULL;
		}
		else
		{
			pNewNode = m_pFirstFree;
			m_pFirstFree = pNewNode->pNext;

			// if the new node points to another free node then
			// change that nodes prev free pointer...
			if( pNewNode->pNext )
			{
				pNewNode->pNext->pPrev = NULL;
			}

			// node is now on the used list

			pNewNode->pPrev = NULL; // the allocated node is always first in the list

			if( m_pFirstUsed == NULL )
			{
				pNewNode->pNext = NULL; // no other nodes
			}
			else
			{
				m_pFirstUsed->pPrev = pNewNode; // insert this at the head of the used list
				pNewNode->pNext = m_pFirstUsed;
			}

			m_pFirstUsed = pNewNode;
		}	
		
		return reinterpret_cast<USER_TYPE*>(pNewNode);
	}

	// Free the given user type
	// For efficiency I don't check whether the user_data is a valid
	// pointer that was allocated. I may add some debug only checking
	// (To add the debug check you'd need to make sure the pointer is in 
	// the m_pMemory area and is pointing at the start of a node)
	void free( USER_TYPE *user_data )
	{
		FSA_ELEMENT *pNode = reinterpret_cast<FSA_ELEMENT*>(user_data);

		// manage used list, remove this node from it
		if( pNode->pPrev )
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
		else
		{
			// this handles the case that we delete the first node in the used list
			m_pFirstUsed = pNode->pNext;
		}

		if( pNode->pNext )
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		// add to free list
		if( m_pFirstFree == NULL ) 
		{
			// free list was empty
			m_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		}
		else
		{
			// Add this node at the start of the free list
			m_pFirstFree->pPrev = pNode;
			pNode->pNext = m_pFirstFree;
			m_pFirstFree = pNode;
		}

	}

	// For debugging this displays both lists (using the prev/next list pointers)
	void Debug()
	{
		printf( "free list " );

		FSA_ELEMENT *p = m_pFirstFree;
		while( p )
		{
			printf( "%x!%x ", p->pPrev, p->pNext );
			p = p->pNext;
		}
		printf( "\n" );

		printf( "used list " );

		p = m_pFirstUsed;
		while( p )
		{
			printf( "%x!%x ", p->pPrev, p->pNext );
			p = p->pNext;
		}
		printf( "\n" );
	}

	// Iterators

	USER_TYPE *GetFirst()
	{
		return reinterpret_cast<USER_TYPE *>(m_pFirstUsed);
	}

	USER_TYPE *GetNext( USER_TYPE *node )
	{
		return reinterpret_cast<USER_TYPE *>
			(
				(reinterpret_cast<FSA_ELEMENT *>(node))->pNext
			);
	}

public: // data

private: // methods

private: // data

	FSA_ELEMENT *m_pFirstFree;
	FSA_ELEMENT *m_pFirstUsed;
	unsigned int m_MaxElements;
	FSA_ELEMENT *m_pMemory;

};

//---------------------------------------------------------------------------------------//





//------------------------------------------STL-A-STAR-------------------------------------------//

#include <set>
#include <vector>

using namespace std;



// Fixed size memory allocator can be disabled to compare performance
// Uses std new and delete instead if you turn it off
#define USE_FSA_MEMORY 1

// disable warning that debugging information has lines that are truncated
// occurs in stl headers
#pragma warning( disable : 4786 )

// The AStar search class. UserState is the users state space type
template <class UserState> class AStarSearch
{

public: // data

	enum
	{
		SEARCH_STATE_NOT_INITIALISED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};


	// A node represents a possible state in the search
	// The user provided state type is included inside this type

	public:

	class Node
	{
		public:

			Node *parent; // used during the search to record the parent of successor nodes
			Node *child; // used after the search for the application to view the search in reverse
			
			float g; // cost of this node + it's predecessors
			float h; // heuristic estimate of distance to goal
			float f; // sum of cumulative cost of predecessors and self and heuristic

			Node() :
				parent( 0 ),
				child( 0 ),
				g( 0.0f ),
				h( 0.0f ),
				f( 0.0f )
			{			
			}

			UserState m_UserState;
	};


	// For sorting the heap the STL needs compare function that lets us compare
	// the f value of two nodes

	class HeapCompare_f 
	{
		public:

			bool operator() ( const Node *x, const Node *y ) const
			{
				return x->f > y->f;
			}
	};


public: // methods


	// constructor just initialises private data
	AStarSearch( int MaxNodes = 1000 ) :
		m_AllocateNodeCount(0),
#if USE_FSA_MEMORY
		m_FixedSizeAllocator( MaxNodes ),
#endif
		m_State( SEARCH_STATE_NOT_INITIALISED ),
		m_CurrentSolutionNode( NULL ),
		m_CancelRequest( false )
	{
	}

	// call at any time to cancel the search and free up all the memory
	void CancelSearch()
	{
		m_CancelRequest = true;
	}

	// Set Start and goal states
	void SetStartAndGoalStates( UserState &Start, UserState &Goal )
	{
		m_CancelRequest = false;

		m_Start = AllocateNode();
		m_Goal = AllocateNode();

		assert((m_Start != NULL && m_Goal != NULL));
		
		m_Start->m_UserState = Start;
		m_Goal->m_UserState = Goal;

		m_State = SEARCH_STATE_SEARCHING;
		
		// Initialise the AStar specific parts of the Start Node
		// The user only needs fill out the state information

		m_Start->g = 0; 
		m_Start->h = m_Start->m_UserState.GoalDistanceEstimate( m_Goal->m_UserState );
		m_Start->f = m_Start->g + m_Start->h;
		m_Start->parent = 0;

		// Push the start node on the Open list

		m_OpenList.push_back( m_Start ); // heap now unsorted

		// Sort back element into heap
		push_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );

		// Initialise counter for search steps
		m_Steps = 0;
	}

	// Advances search one step 
	unsigned int SearchStep()
	{
		// Firstly break if the user has not initialised the search
		assert( (m_State > SEARCH_STATE_NOT_INITIALISED) &&
				(m_State < SEARCH_STATE_INVALID) );

		// Next I want it to be safe to do a searchstep once the search has succeeded...
		if( (m_State == SEARCH_STATE_SUCCEEDED) ||
			(m_State == SEARCH_STATE_FAILED) 
		  )
		{
			return m_State; 
		}

		// Failure is defined as emptying the open list as there is nothing left to 
		// search...
		// New: Allow user abort
		if( m_OpenList.empty() || m_CancelRequest )
		{
			FreeAllNodes();
			m_State = SEARCH_STATE_FAILED;
			return m_State;
		}
		
		// Incremement step count
		m_Steps ++;

		// Pop the best node (the one with the lowest f) 
		Node *n = m_OpenList.front(); // get pointer to the node
		pop_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
		m_OpenList.pop_back();

		// Check for the goal, once we pop that we're done
		if( n->m_UserState.IsGoal( m_Goal->m_UserState ) )
		{
			// The user is going to use the Goal Node he passed in 
			// so copy the parent pointer of n 
			m_Goal->parent = n->parent;

			// A special case is that the goal was passed in as the start state
			// so handle that here
			if( false == n->m_UserState.IsSameState( m_Start->m_UserState ) )
			{
				FreeNode( n );

				// set the child pointers in each node (except Goal which has no child)
				Node *nodeChild = m_Goal;
				Node *nodeParent = m_Goal->parent;

				do 
				{
					nodeParent->child = nodeChild;

					nodeChild = nodeParent;
					nodeParent = nodeParent->parent;
				
				} 
				while( nodeChild != m_Start ); // Start is always the first node by definition

			}

			// delete nodes that aren't needed for the solution
			FreeUnusedNodes();

			m_State = SEARCH_STATE_SUCCEEDED;

			return m_State;
		}
		else // not goal
		{

			// We now need to generate the successors of this node
			// The user helps us to do this, and we keep the new nodes in
			// m_Successors ...

			m_Successors.clear(); // empty vector of successor nodes to n

			// User provides this functions and uses AddSuccessor to add each successor of
			// node 'n' to m_Successors
			bool ret = n->m_UserState.GetSuccessors( this, n->parent ? &n->parent->m_UserState : NULL ); 

			if( !ret )
			{

			    typename vector< Node * >::iterator successor;

				// free the nodes that may previously have been added 
				for( successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
				{
					FreeNode( (*successor) );
				}

				m_Successors.clear(); // empty vector of successor nodes to n

				// free up everything else we allocated
				FreeAllNodes();

				m_State = SEARCH_STATE_OUT_OF_MEMORY;
				return m_State;
			}
			
			// Now handle each successor to the current node ...
			for( typename vector< Node * >::iterator successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
			{

				// 	The g value for this successor ...
				float newg = n->g + n->m_UserState.GetCost( (*successor)->m_UserState );

				// Now we need to find whether the node is on the open or closed lists
				// If it is but the node that is already on them is better (lower g)
				// then we can forget about this successor

				// First linear search of open list to find node

				typename vector< Node * >::iterator openlist_result;

				for( openlist_result = m_OpenList.begin(); openlist_result != m_OpenList.end(); openlist_result ++ )
				{
					if( (*openlist_result)->m_UserState.IsSameState( (*successor)->m_UserState ) )
					{
						break;					
					}
				}

				if( openlist_result != m_OpenList.end() )
				{

					// we found this state on open

					if( (*openlist_result)->g <= newg )
					{
						FreeNode( (*successor) );

						// the one on Open is cheaper than this one
						continue;
					}
				}

				typename vector< Node * >::iterator closedlist_result;

				for( closedlist_result = m_ClosedList.begin(); closedlist_result != m_ClosedList.end(); closedlist_result ++ )
				{
					if( (*closedlist_result)->m_UserState.IsSameState( (*successor)->m_UserState ) )
					{
						break;					
					}
				}

				if( closedlist_result != m_ClosedList.end() )
				{

					// we found this state on closed

					if( (*closedlist_result)->g <= newg )
					{
						// the one on Closed is cheaper than this one
						FreeNode( (*successor) );

						continue;
					}
				}

				// This node is the best node so far with this particular state
				// so lets keep it and set up its AStar specific data ...

				(*successor)->parent = n;
				(*successor)->g = newg;
				(*successor)->h = (*successor)->m_UserState.GoalDistanceEstimate( m_Goal->m_UserState );
				(*successor)->f = (*successor)->g + (*successor)->h;

				// Remove successor from closed if it was on it

				if( closedlist_result != m_ClosedList.end() )
				{
					// remove it from Closed
					FreeNode(  (*closedlist_result) ); 
					m_ClosedList.erase( closedlist_result );

					// Fix thanks to ...
					// Greg Douglas <gregdouglasmail@gmail.com>
					// who noticed that this code path was incorrect
					// Here we have found a new state which is already CLOSED
					// anus
					
				}

				// Update old version of this node
				if( openlist_result != m_OpenList.end() )
				{	   

					FreeNode( (*openlist_result) ); 
			   		m_OpenList.erase( openlist_result );

					// re-make the heap 
					// make_heap rather than sort_heap is an essential bug fix
					// thanks to Mike Ryynanen for pointing this out and then explaining
					// it in detail. sort_heap called on an invalid heap does not work
					make_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
			
				}

				// heap now unsorted
				m_OpenList.push_back( (*successor) );

				// sort back element into heap
				push_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );

			}

			// push n onto Closed, as we have expanded it now

			m_ClosedList.push_back( n );

		} // end else (not goal so expand)

 		return m_State; // Succeeded bool is false at this point. 

	}

	// User calls this to add a successor to a list of successors
	// when expanding the search frontier
	bool AddSuccessor( UserState &State )
	{
		Node *node = AllocateNode();

		if( node )
		{
			node->m_UserState = State;

			m_Successors.push_back( node );

			return true;
		}

		return false;
	}

	// Free the solution nodes
	// This is done to clean up all used Node memory when you are done with the
	// search
	void FreeSolutionNodes()
	{
		Node *n = m_Start;

		if( m_Start->child )
		{
			do
			{
				Node *del = n;
				n = n->child;
				FreeNode( del );

				del = NULL;

			} while( n != m_Goal );

			FreeNode( n ); // Delete the goal

		}
		else
		{
			// if the start node is the solution we need to just delete the start and goal
			// nodes
			FreeNode( m_Start );
			FreeNode( m_Goal );
		}

	}

	// Functions for traversing the solution

	// Get start node
	UserState *GetSolutionStart()
	{
		m_CurrentSolutionNode = m_Start;
		if( m_Start )
		{
			return &m_Start->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	
	// Get next node
	UserState *GetSolutionNext()
	{
		if( m_CurrentSolutionNode )
		{
			if( m_CurrentSolutionNode->child )
			{

				Node *child = m_CurrentSolutionNode->child;

				m_CurrentSolutionNode = m_CurrentSolutionNode->child;

				return &child->m_UserState;
			}
		}

		return NULL;
	}
	
	// Get end node
	UserState *GetSolutionEnd()
	{
		m_CurrentSolutionNode = m_Goal;
		if( m_Goal )
		{
			return &m_Goal->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	
	// Step solution iterator backwards
	UserState *GetSolutionPrev()
	{
		if( m_CurrentSolutionNode )
		{
			if( m_CurrentSolutionNode->parent )
			{

				Node *parent = m_CurrentSolutionNode->parent;

				m_CurrentSolutionNode = m_CurrentSolutionNode->parent;

				return &parent->m_UserState;
			}
		}

		return NULL;
	}

	// For educational use and debugging it is useful to be able to view
	// the open and closed list at each step, here are two functions to allow that.

	UserState *GetOpenListStart()
	{
		float f,g,h;
		return GetOpenListStart( f,g,h );
	}

	UserState *GetOpenListStart( float &f, float &g, float &h )
	{
		iterDbgOpen = m_OpenList.begin();
		if( iterDbgOpen != m_OpenList.end() )
		{
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->m_UserState;
		}

		return NULL;
	}

	UserState *GetOpenListNext()
	{
		float f,g,h;
		return GetOpenListNext( f,g,h );
	}

	UserState *GetOpenListNext( float &f, float &g, float &h )
	{
		iterDbgOpen++;
		if( iterDbgOpen != m_OpenList.end() )
		{
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->m_UserState;
		}

		return NULL;
	}

	UserState *GetClosedListStart()
	{
		float f,g,h;
		return GetClosedListStart( f,g,h );
	}

	UserState *GetClosedListStart( float &f, float &g, float &h )
	{
		iterDbgClosed = m_ClosedList.begin();
		if( iterDbgClosed != m_ClosedList.end() )
		{
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;

			return &(*iterDbgClosed)->m_UserState;
		}

		return NULL;
	}

	UserState *GetClosedListNext()
	{
		float f,g,h;
		return GetClosedListNext( f,g,h );
	}

	UserState *GetClosedListNext( float &f, float &g, float &h )
	{
		iterDbgClosed++;
		if( iterDbgClosed != m_ClosedList.end() )
		{
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;

			return &(*iterDbgClosed)->m_UserState;
		}

		return NULL;
	}

	// Get the number of steps

	int GetStepCount() { return m_Steps; }

	void EnsureMemoryFreed()
	{
#if USE_FSA_MEMORY
		assert(m_AllocateNodeCount == 0);
#endif

	}

private: // methods

	// This is called when a search fails or is cancelled to free all used
	// memory 
	void FreeAllNodes()
	{
		// iterate open list and delete all nodes
		typename vector< Node * >::iterator iterOpen = m_OpenList.begin();

		while( iterOpen != m_OpenList.end() )
		{
			Node *n = (*iterOpen);
			FreeNode( n );

			iterOpen ++;
		}

		m_OpenList.clear();

		// iterate closed list and delete unused nodes
		typename vector< Node * >::iterator iterClosed;

		for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
		{
			Node *n = (*iterClosed);
			FreeNode( n );
		}

		m_ClosedList.clear();

		// delete the goal

		FreeNode(m_Goal);
	}


	// This call is made by the search class when the search ends. A lot of nodes may be
	// created that are still present when the search ends. They will be deleted by this 
	// routine once the search ends
	void FreeUnusedNodes()
	{
		// iterate open list and delete unused nodes
		typename vector< Node * >::iterator iterOpen = m_OpenList.begin();

		while( iterOpen != m_OpenList.end() )
		{
			Node *n = (*iterOpen);

			if( !n->child )
			{
				FreeNode( n );

				n = NULL;
			}

			iterOpen ++;
		}

		m_OpenList.clear();

		// iterate closed list and delete unused nodes
		typename vector< Node * >::iterator iterClosed;

		for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
		{
			Node *n = (*iterClosed);

			if( !n->child )
			{
				FreeNode( n );
				n = NULL;

			}
		}

		m_ClosedList.clear();

	}

	// Node memory management
	Node *AllocateNode()
	{

#if !USE_FSA_MEMORY
		Node *p = new Node;
		return p;
#else
		Node *address = m_FixedSizeAllocator.alloc();

		if( !address )
		{
			return NULL;
		}
		m_AllocateNodeCount ++;
		Node *p = new (address) Node;
		return p;
#endif
	}

	void FreeNode( Node *node )
	{

		m_AllocateNodeCount --;

#if !USE_FSA_MEMORY
		delete node;
#else
		m_FixedSizeAllocator.free( node );
#endif
	}

private: // data

	// Heap (simple vector but used as a heap, cf. Steve Rabin's game gems article)
	vector< Node *> m_OpenList;

	// Closed list is a vector.
	vector< Node * > m_ClosedList; 

	// Successors is a vector filled out by the user each type successors to a node
	// are generated
	vector< Node * > m_Successors;

	// State
	unsigned int m_State;

	// Counts steps
	int m_Steps;

	// Start and goal state pointers
	Node *m_Start;
	Node *m_Goal;

	Node *m_CurrentSolutionNode;

#if USE_FSA_MEMORY
	// Memory
 	FixedSizeAllocator<Node> m_FixedSizeAllocator;
#endif
	
	//Debug : need to keep these two iterators around
	// for the user Dbg functions
	typename vector< Node * >::iterator iterDbgOpen;
	typename vector< Node * >::iterator iterDbgClosed;

	// debugging : count memory allocation and free's
	int m_AllocateNodeCount;
	
	bool m_CancelRequest;

};

//---------------------------------------------------------------------------------------//

   
