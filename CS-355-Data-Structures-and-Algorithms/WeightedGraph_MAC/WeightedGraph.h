//-----------------------------------------------------------------------------
// Donald Lee Beadle
// WeightedGraph.h
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <queue>
using namespace std;

#ifndef WEIGHTEDGRAPH
#define WEIGHTEDGRAPH

class WeightedGraph
{
public:
	class Vertex 
	{
	public:
		void setLabel(string& label);
		string getLabel() const;
		void setDist(int dist);
		int getDist();
		void setPredecessorLabel(string label);
		string getPredecessorLabel() const;
		friend bool operator < (const Vertex& left, const Vertex& right)
		{
			return left.dist > right.dist;
		}

	private:
		string label;
		string predLabel;
		int dist;
		
	};

    // Constructors
    WeightedGraph();
    WeightedGraph(int maxSize);
    WeightedGraph(WeightedGraph& other);
    
    // Overload assignment operator
    WeightedGraph& operator=(const WeightedGraph& other); 

    // Destructor
    ~WeightedGraph();  

    // Insertion Functions:
	void insertVertex(Vertex& vertex);
	void insertEdge(const string& from, const string& to, int wt);

    // Retrieval Functions:
    bool retrieveVertex(string& label, Vertex& foundVertex);
    bool getEdgeWeight(string u, string v, int& w);

    // Removal Functions:
    void removeEdge(string& u, string& v);
    void removeVertex(string& label);

    void clear();  // Clears the graph

    // Capacity Functions:
    bool isEmpty();
    bool isFull();

	void showStructure();
	void showShortestPaths();
	
private:	
	int getIndex(const string& v);
	bool vertexVisited(Vertex& v, deque<Vertex> d);

	Vertex* vertices;
	int** adjMatrix;
	int used;
	int max;

};

#endif // WEIGHTEDGRAPH_H
