#include <string>
#include <iostream>
#include <queue>
//-----------------------------------------------------------------------------
// Donald Lee Beadle
// WeightedGraph.cpp
//-----------------------------------------------------------------------------
#include <climits> //INT_MAX
#include <iomanip>
#include "stdlib.h"
#include "WeightedGraph.h"

using namespace std;

//-----------------------------------------------------------------------------
// CLass Vertex:
//-----------------------------------------------------------------------------
// Mutator Function: setLabel()
// Changes the value of member variable label.
void WeightedGraph::Vertex::setLabel(string& label) 
{

	this->label = label; 

}
//-----------------------------------------------------------------------------	
// Accessor Function: getLabel()
// Returns the value of the member variable label. 	
string WeightedGraph::Vertex::getLabel() const 
{ 

	return label; 

}
//-----------------------------------------------------------------------------	
// Mutator Function:
// Sets the distance variable of Class Vertex to the intger value passed as 
// a parameter. 
void WeightedGraph::Vertex::setDist(int dist) 
{ 

	this->dist = dist; 

}
//-----------------------------------------------------------------------------	
// Accessor Function:
// Retrieves the Class Vertex distance variable. 	
int WeightedGraph::Vertex::getDist() 
{ 

	return dist; 

}
//-----------------------------------------------------------------------------
// Mutator Function:
// Sets PredLabel.
void WeightedGraph::Vertex::setPredecessorLabel (string label)
{

	this->label = predLabel;

}
//-----------------------------------------------------------------------------
// Accessor Function:
// Returns PredLabel.
string WeightedGraph::Vertex::getPredecessorLabel() const
{
	return predLabel;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Class WeightedGraph:
//-----------------------------------------------------------------------------
// Default Constructor:
// Initializes WeightedGraph with enough memory to store 10 vertices. 
WeightedGraph::WeightedGraph() 
{

	max = 10; 
	vertices = new Vertex[10];
	adjMatrix = new int*[10];
	
	for (int i = 0; i < 10; i++)
	{
		adjMatrix[i] = new int[10];
		
		for (int j = 0; j < 10; j++)
		{
			adjMatrix[i][j] = INT_MAX;
		}
	}

	used = 0;

}
//-----------------------------------------------------------------------------
// Constructor: One parameter
// Creates a WeightedGraph object with memory indicated by the variable maxSize.
WeightedGraph::WeightedGraph(int maxSize) 
{

	max = maxSize;
	vertices = new Vertex[max];
	adjMatrix = new int*[max];
	
	for (int i = 0; i < max; i++)
	{
		adjMatrix[i] = new int[max];
		
		for (int j = 0; j < max; j++)
		{
			adjMatrix[i][j] = INT_MAX;
		}
	}

	used = 0;

}
//-----------------------------------------------------------------------------
// Copy Constructor:
WeightedGraph::WeightedGraph(WeightedGraph& other)
{

	max = other.max;
	used = other.used;
	vertices = new Vertex[max];
	adjMatrix = new int*[max];
	
	for( int i=0; i<used; i++ ) 
	{
		vertices[i] = other.vertices[i];
	}
	
	for( int i=0; i<used; i++ ) 
	{
		for( int j=0; j<used; j++) 
		{
			adjMatrix[i][j] = other.adjMatrix[i][j];
		}
	}
	
}
//-----------------------------------------------------------------------------
// Overloaded Assignemnt Operator:
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
{
	if( this == &other ) 
	{
		return *this;
	}

	delete [] vertices;
	
	for (int i = 0; i < max; i++) 
	{
		delete adjMatrix[i];
	}
	
	delete [] adjMatrix;

	vertices = new Vertex [other.max];
	adjMatrix = new int*[other.max];
	max = other.max;
	used = other.used;

	for( int i=0; i<used; i++ ) 
	{
		vertices[i] = other.vertices[i];
	}

	for( int i=0; i<used; i++ ) 
	{
		for( int j=0; j<used; j++ ) 
		{
			adjMatrix[i][j] = other.adjMatrix[i][j];
		}
	}
	
	return*this;
	
} 
//-----------------------------------------------------------------------------
// Destructor: 
// Deallocates the memory created to store data of WeightedGraph.
WeightedGraph::~WeightedGraph()
{

	delete [] vertices;
	
	for (int i = 0; i < max; i++) 
	{
		delete adjMatrix[i];
	}
	
	delete [] adjMatrix;

}
//-----------------------------------------------------------------------------
//  Vertex Insertion:
// Inserts a vertex into the graph. 
void WeightedGraph::insertVertex(Vertex& vertex)
{

	if(!isFull())
	{
		string s(vertex.getLabel());
		vertices[used++].setLabel(s);
	}
	
	else
	{
		cout << endl;
		cout << "Cannot Add Vertex! Graph Full!";
		cout << endl;
	}

}
//-----------------------------------------------------------------------------
// Edge Insertion:
// Inserts an edge with a designated weight (wt) between two vertices (string
// v1 and string v2).
void WeightedGraph::insertEdge(const string& v1, const string& v2, int wt)
{

	int from = getIndex(v1); // return index
	int to = getIndex(v2);

	if (from < 0 || to < 0)
		return;
	
	adjMatrix[from][to] = wt;
	adjMatrix[to][from] = wt;

}
//-----------------------------------------------------------------------------
// Boolean Function: retriveVertex
// Searches the graph to find a specified vertex. Returns true if vertex is 
// found. 
bool WeightedGraph::retrieveVertex(string& label, Vertex& searchVertex)
{

    int target = getIndex(label);
 
    if(target == -1)
    {
    	return false;
	}
	
	else
	{	
		return true;
	}
    
}
//-----------------------------------------------------------------------------
// Boolean Function: getEdgeWeight
// Returns true if the weight from string u to string v is not equal to 
// INT_MAX.
bool WeightedGraph::getEdgeWeight(string u, string v, int& w)
{

	int to = getIndex(u);
	int from = getIndex(v);
	
	w = adjMatrix[to][from];
	
	if(w != INT_MAX)
	{
		return true;
	}
	
	else
	{
		return false; 
	}

}
//-----------------------------------------------------------------------------
// Remove Edge Function:
// Removes an edge from two vertices. 
void WeightedGraph::removeEdge(string& u, string& v)
{
	
	int from = getIndex(u); 
	int to = getIndex(v);   

	if ( from >= used || to >= used )
	{
		cout << endl;
		cout << "Edge does not exist!";
		cout << endl;
	}

	else
	{
		adjMatrix[to][from] = 0;
		adjMatrix[from][to] = 0;
	}

} 
//-----------------------------------------------------------------------------
// Remove Vertex:
// Removes a vertex from the graph. 
void WeightedGraph::removeVertex(string& label)
{

	int target = getIndex(label);
	
	if(target < 0 || target > used)
	{
		cout << endl;
		cout << "Vertex " << label << " not in graph!";
		cout << endl;
	}
	
	else
	{
		for(int i = target; i<(used-1);i++)
		{
			vertices[i] = vertices[i+1];
		}
	
		for(int i = target; i < (used-1); i++)
		{
			for(int j = target; j < used; j++)
			{
				adjMatrix[i][j]= adjMatrix[i+1][j];
			}
		}
		
		for(int i = target; i < (used-1); i++)
		{
			for(int j = target; j < used; j++)
			{
				adjMatrix[i][j]= adjMatrix[i][j+1];
			}
	
		}
		
		used--;
	}
	
}
//-----------------------------------------------------------------------------
// Clear Function:
// Clears the graph of previously entered values.
void WeightedGraph::clear()
{

	if(!isEmpty() )
	{
		for (int i = 0; i < max; i++)
		{
			for (int j = 0; j < max; j++)
			{
				adjMatrix[i][j] = 0;
			}
		}

		used = 0;
	}	
	
	else
	{	
		cout << endl;
		cout << "Cannot clear empty graph!";
		cout << endl;
	}

}
//-----------------------------------------------------------------------------
// Boolean Function: isEmpty()
// Tests the capacity of the graph. If empty, returns true. 
bool WeightedGraph::isEmpty()
{

	if( used == 0)
	{
		return true;
	}
	
	else
	{
		return false; 
	}

}
//-----------------------------------------------------------------------------
// Boolean Function: isFull()
// Tests the capacity of the graph. If full, returns true. 
bool WeightedGraph::isFull()
{

	if(used == max)
	{
		return true;
	}
	
	else
	{
		return false;
	}

}
//-----------------------------------------------------------------------------
// Output Function: 
// Shows the WeightedGraph structure. Also, displays the capacity of the graph
// as the variable "used". For debugging purposes.
void WeightedGraph::showStructure()
{
	
	for (int i = 0; i < used; i++)
	{
		cout << "\t";
		cout << vertices[i].getLabel();	  
	}
	
	cout <<  endl << endl;

	for (int i = 0; i < max; i++)
	{
		cout << vertices[i].getLabel();
		
		for (int j = 0; j < max; j++)
		{
			cout << "\t";
			
			if(adjMatrix[i][j] != INT_MAX)
			{
				cout << adjMatrix[i][j];
			}
			
			else
			{
				cout << "-";
			}
		}
		
		cout << endl << endl;
	
	}

	cout << endl << endl << "used: " << used;

}
//-----------------------------------------------------------------------------
void WeightedGraph::showShortestPaths() 
{
	cout << "Dijkstra's Shortest Path" << endl;

	// set all distances to infinity (except our first node, the 
	// starting point)
	for (int i = 1; i < used; i++) 
    {
		vertices[i].setDist(INT_MAX);
	}
		
    vertices[0].setDist(0);

	// collections to manage vertices
	priority_queue<Vertex> toBeChecked;
	priority_queue<Vertex> unmodified;
	deque<Vertex> visited;
	deque<Vertex> modified;

	// put all vertices into the primary collection
	for (int i = 0; i < used; i++) 
    {
		toBeChecked.push(vertices[i]);
	}

	while (!toBeChecked.empty()) 
    {

	   // get the vertex with the shortest distances
	   Vertex v = toBeChecked.top();
	   toBeChecked.pop();

	   // add v to the collection of vertices that have already been processed
	   visited.push_back(v);

		// For each vertex (u) connected to v, that is in toBeChecked 
		// (in other words, not in visited), update u's distance if the sum 
		// of v's distance and the edge weight (w) are less.
		int vIndex = getIndex(v.getLabel());
		for (int i = 0; i < used; i++) 
        {
		
            if (vIndex != i && adjMatrix[vIndex][i] != INT_MAX 
						&& !vertexVisited(vertices[i], visited)) 
            {

                if (vertices[i].getDist() > vertices[vIndex].getDist() 
							+ adjMatrix[vIndex][i]) 
                {
			
                    // update u's distance with the new value (v + w)
                    vertices[i].setDist(vertices[vIndex].getDist() 
			         + adjMatrix[vIndex][i]);

			        // since our primary collection is immutable, we need 
			        // to keep track of vertices with changed distances
			         modified.push_back(vertices[i]);

			         vertices[i].setPredecessorLabel(v.getLabel());
			    }
		    }
        }

        // take all of the vertices out of toBeChecked and put those 
        // that are not already in modified into unmodified
		while (!toBeChecked.empty()) 
        {
		  
            Vertex save = toBeChecked.top();
			bool found = false;
			toBeChecked.pop();
			
            for (deque<Vertex>::iterator it = modified.begin(); 
						it != modified.end(); ++it) 
			{
			
                Vertex current = *it;
			
                if (current.getLabel() == save.getLabel()) 
                {
				    found = true;
					break;
				}
			}
				
            if (!found) 
            {
				unmodified.push(save);
			}
		}

		// move all of the vertices from unmodified to toBeChecked
		while (!unmodified.empty()) 
        {
			Vertex save = unmodified.top();
			unmodified.pop();
			toBeChecked.push(save);
		}

		// move all of the vertices from modified to toBeChecked
		while (!modified.empty()) 
        {
			Vertex save = modified.front();
			toBeChecked.push(save);
			modified.pop_front();
		}

	}
		
	// display the final results
	for (int i = 1; i < used; i++) 
    {
	   cout << vertices[i].getLabel() << " [" << vertices[i].getDist() 
				<< "] " << vertices[i].getPredecessorLabel() << endl;
	}

}
//-----------------------------------------------------------------------------
// Index Function:
// Returns the index integer value of a specific vertex.
int WeightedGraph::getIndex(const string& v)
{

	for (int i = 0; i < used; i++)
	{
		if (v == vertices[i].getLabel())
			return i;
	}
	
	return -1;
	
}
//-----------------------------------------------------------------------------	
// Boolean Function: vertexVisited
bool WeightedGraph::vertexVisited(Vertex& v, deque<Vertex> d)
{

	for (deque<Vertex>::iterator it = d.begin(); it != d.end(); ++it)
	{
		Vertex current = *it;
		if (current.getLabel() == v.getLabel())
		{
			return true;
		}
	}

	return false; 

}
//-----------------------------------------------------------------------------
