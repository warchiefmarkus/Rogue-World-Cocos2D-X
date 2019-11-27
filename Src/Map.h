////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "A-Star.h" 
#include <iostream>
#include <math.h>
#include <Utils.h>

using namespace std;

// Cell Array
class Cells{
public:
	// Constructor
	Cells(int width, int height){
		m_width = width;
		m_height = height;
		// Initialize fill map
		for (int i=0; i<width; i++){
			std::vector<Cell*> vec;
			for (int k=0; k<height; k++){				
				vec.push_back(new Cell);
			}
			cells.push_back(vec);
		}
	}

	// FindPath function
	int GetCell(int x, int y)
	{		
		if( x < 0 || x >= m_width || y < 0 ||	y >= m_height)
		{
			return 9;	 
		}
		return this->cells[x][y]->Cost;
		
	}

	// Cell array
	std::vector<std::vector<Cell*> > cells;
protected:
	int m_width;
	int m_height;
};

// Search Node
class MapSearchNode
{
public:
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;	
	
	

	MapSearchNode() { x = y = 0; }
	MapSearchNode( unsigned int px, unsigned int py ) { x=px; y=py; }

	float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = fabs(float(((float)x - (float)nodeGoal.x)));
	float yd = fabs(float(((float)y - (float)nodeGoal.y)));

	return xd + yd;
}
    bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

	
	bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;
	NewNode.setMap(m_cells);

	// push each possible move except allowing the search to go backwards

	if( (m_cells->GetCell( x-1, y ) < 9) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		NewNode.setMap(m_cells);
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (m_cells->GetCell( x, y-1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		NewNode.setMap(m_cells);
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (m_cells->GetCell( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		NewNode.setMap(m_cells);
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (m_cells->GetCell( x, y+1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		NewNode.setMap(m_cells);
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

	
    float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) m_cells->GetCell( x, y );

}

	bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

    void MapSearchNode::PrintNodeInfo()
{
	cout << "Node position : (" << x << ", " << y << ")" << endl;
}

	
	void setMap(Cells* m){m_cells = m;}
protected:
	Cells* m_cells;

};

// Map class
class Map{
public:
	// Constructor
	Map(int width, int height)
	{
		m_width = width; 
		m_height = height;
		m_cells = new Cells(width, height);
	}
	
	// Find Path
    std::vector<Point> findPath(int start_x, int start_y, int end_x, int end_y)
	{
		// returned result
		std::vector<Point> find_steps;

		// Create an instance of the search class...
		AStarSearch<MapSearchNode> astarsearch;
		unsigned int SearchCount = 0;
		const unsigned int NumSearches = 1;

		while(SearchCount < NumSearches)
		{
			// Create a start state
			MapSearchNode nodeStart;
			nodeStart.setMap(m_cells);

			nodeStart.x = start_x;
			nodeStart.y = start_y; 

			// Define the goal state
			MapSearchNode nodeEnd;
			nodeStart.setMap(m_cells);

			nodeEnd.x = end_x;						
			nodeEnd.y = end_y; 

			// Set Start and goal states		
			astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

			unsigned int SearchState;
			unsigned int SearchSteps = 0;

			do
			{
				SearchState = astarsearch.SearchStep();

				SearchSteps++;
/*
#if DEBUG_LISTS
				int len = 0;
				MapSearchNode *p = astarsearch.GetOpenListStart();
				while( p )
				{
					len++;

					p = astarsearch.GetOpenListNext();

				}
				len = 0;
				p = astarsearch.GetClosedListStart();
				while( p )
				{
					len++;
					p = astarsearch.GetClosedListNext();
				}
#endif
*/
			}
			while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

			if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
			{
				MapSearchNode *node = astarsearch.GetSolutionStart();

				int steps = 0;
											
				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}
					
					find_steps.push_back(Point(node->x,node->y));

					node->PrintNodeInfo();
					steps ++;

				};


				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();


			}
			else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
			{
				cout << "Search terminated. Did not find goal state\n";

			}

			// Display the number of loops the search went through
			cout << "SearchSteps : " << SearchSteps << "\n";

			SearchCount ++;

			astarsearch.EnsureMemoryFreed();
		}
		return find_steps;
	}
	
	// Add Object to map
	void addObj(Object* obj, Point pos, Layer layer)
	{		
		switch(layer){
		case GROUND:{
			m_cells->cells[pos.X][pos.Y]->ground = obj;
			obj->setPos(pos.X,pos.Y);
					}
		case ENIVORMENT:{
			m_cells->cells[pos.X][pos.Y]->eniv = obj;
			obj->setPos(pos.X,pos.Y);
						}
		case NPC:{
			m_cells->cells[pos.X][pos.Y]->npc = obj;		
			obj->setPos(pos.X,pos.Y);			
				 }
		}
		std::cout << m_cells->cells[pos.X][pos.Y]->npc->type;
	}

	// Get Object by cell and layer
	Object* getObject(int CellX, int CellY, Layer layer)
	{
		
		switch(layer)
		{
		case GROUND:{			
			return m_cells->cells[CellX][CellY]->ground;
					}
		case ENIVORMENT:{			
			return m_cells->cells[CellX][CellY]->eniv;
						}
		case NPC:{			
			return m_cells->cells[CellX][CellY]->npc;			
				 }
		}
	}

protected:
	int m_width;
	int m_height;
	Cells* m_cells;
};
