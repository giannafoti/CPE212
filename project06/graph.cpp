// ****************************************
// Program Title: Project06
// Project File: graph.cpp
// Name: Gianna Foti
// Course Section: CPE-212-01
// Due Date: 11/26/23
// Program description: graphs ya'll
// ****************************************


#include <iostream>
#include <new>
#include "graph.h"
using namespace std;

Graph::Graph()
// Graph()
// Constructor initializes vertices linked list to empty
{
    vertices = NULL;
}

Graph::~Graph()
// ~Graph()
// For each VertexNode in the vertices list, Destructor deallocates all EdgeNodes before
// deallocating the VertexNode itself
{
    // For each VertexNode in the vertices list, Destructor deallocates all EdgeNodes before deallocating the VertexNode itself
    VertexNode* currentVertex = vertices;

    while (currentVertex != NULL) {
        EdgeNode* currentEdge = currentVertex->edgePtr;

        while (currentEdge != NULL) {
            EdgeNode* tempEdge = currentEdge;
            currentEdge = currentEdge->nextPtr;
            delete tempEdge;
        }

        VertexNode* tempVertex = currentVertex;
        currentVertex = currentVertex->nextVertex;
        delete tempVertex;
    }
    // vertices is set to NULL 
    vertices = NULL;
}

void Graph::AddVertex(string v)
// AddVertex()
// Adds vertex to graph assuming vertex not already present
{
    // Adds vertex to the graph assuming the vertex is not already present
    // Check if the vertex is already present
    if (IsPresent(v))
    {
        return;
    }

    // Create a new vertex node
    VertexNode* newVertex = new VertexNode;
    newVertex->vname = v;
    newVertex->mark = false;
    newVertex->edgePtr = NULL;
    newVertex->nextVertex = NULL;

    // Add the new vertex to the beginning of the vertices list
    newVertex->nextVertex = vertices;
    vertices = newVertex;
}

void Graph::AddEdge(string s, string d, int w)
{	
// Adds edge from source S  to destination D with specified weight W.
// If there is not enough memory to add the edge, throw the GraphFull exception
	// initialize source, destination, and currentVertex
	VertexNode* source = NULL;
	VertexNode* destination = NULL;
	VertexNode* currentVertex = vertices;
	// traverse vertices to set source and destination
	while (currentVertex != NULL)
	{
		if (currentVertex->vname == s)
		{
			source = currentVertex;
		}
		if (currentVertex->vname == d)
		{
			destination = currentVertex;
		}
		currentVertex = currentVertex->nextVertex;
	}
	try
	{
		// create new edge
		EdgeNode* tempEdge = new EdgeNode;
		tempEdge->destination = destination;
		tempEdge->weight = w;
		tempEdge->nextPtr = NULL;

		// add edge to front of source vertex's edge list
		tempEdge->nextPtr = source->edgePtr;
		source->edgePtr = tempEdge;
	}
	catch (bad_alloc())  // exception handling 
	{
		throw GraphFull();
	}
}

bool Graph::IsPresent(string v)
// IsPresent()
// Returns true if vertex V in graph, false otherwise
{
    // Returns true if vertex V is in the graph, false otherwise
    VertexNode* currentVertex = vertices;
    while (currentVertex != NULL)
     {
        if (currentVertex->vname == v)
         {
            // Vertex found
            return true;
        }
        currentVertex = currentVertex->nextVertex;
    }
    // otherwise no match, Vertex not found
    return false;
}

VertexNode* Graph::WhereIs(string v)   /* Note: This function replaces IndexIs */
// WhereIs()
// Returns pointer to the vertex node that stores vertex v in the vertices linked list;
// Throws GraphVertexNotFound if V is not present in the vertices list
{
    // Returns pointer to the vertex node that stores vertex v in the vertices linked list;
    // Throws GraphVertexNotFound if V is not present in the vertices list
    VertexNode* currentVertex = vertices;
    while (currentVertex != NULL)
     {
        if (currentVertex->vname == v)
         {
            // Vertex found
            return currentVertex;
        }
        currentVertex = currentVertex->nextVertex;
    }
    // Vertex not found, throw GraphVertexNotFound exception
    throw GraphVertexNotFound();
}


int Graph::WeightIs(string s, string d)
// WeightIs()
// Returns weight of edge (s,d).  Throws GraphEdgeNotFound if edge not present.
{
    // Returns weight of edge (s,d). Throws GraphEdgeNotFound if edge not present.
    // Find the source vertex
    VertexNode* sourceVertex = WhereIs(d);
    // Search for the edge in the outgoing edges of the source vertex
    EdgeNode* edgePtr = sourceVertex->edgePtr;
    while (edgePtr != NULL) 
    {
        if (edgePtr->destination->vname == s) 
        {
            return edgePtr->weight;
        }
        edgePtr = edgePtr->nextPtr;
    }
    throw GraphEdgeNotFound();
}

void Graph::ClearMarks()
// ClearMarks()
// Clears all vertex marks
{
    // Clears all vertex marks

    VertexNode* currentVertex = vertices;

    while (currentVertex != NULL) 
    {
        currentVertex->mark = false;
        currentVertex = currentVertex->nextVertex;
    }
}

void Graph::MarkVertex(string v)
{
// MarkVertex()
// Marks vertex V as visited
	// look for vertex by name in vertices and mark as visited
	VertexNode* currentVertex = vertices;
	while (currentVertex != NULL)
	{
		if (currentVertex->vname == v)
		{
			currentVertex->mark = true;
			return;
		}
		currentVertex = currentVertex->nextVertex;
	}
}

bool Graph::IsMarked(string v)
// IsMarked()
// Returns true if vertex V is marked, false otherwise
{
    // Returns true if vertex V is marked, false otherwise
    VertexNode* vertex = WhereIs(v);
    if (vertex != NULL) {
        // Return the marked status of the vertex
        return vertex->mark;
    }
    // If the vertex is not found, consider it unmarked
    return false;
}

void Graph::GetToVertices(string V, queue<string>& q)
// GetToVertices()
// Returns queue Q of vertex names of those vertices adjacent to vertex V
// The queue here is from the Standard Template Library
{
    // Returns queue Q of vertex names of those vertices adjacent to vertex V
    VertexNode* sourceVertex = WhereIs(V);
    if (sourceVertex != NULL)
     {
        EdgeNode* edgePtr = sourceVertex->edgePtr;
        while (edgePtr != NULL)
         {
            q.push(edgePtr->destination->vname);
            edgePtr = edgePtr->nextPtr;
        }
    }
}

void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path)
{
// DepthFirstSearch()
// Uses the DFS algorithm from the CPE 212 textbook to determine a path from the
// startVertex to the endVertex.  If a path is found, the path vertices should
// be in the path queue.  If no path is found, the path queue should be emptied
// as a signal to the client code that no path exists between the start and
// end vertices.
//
// Notes:
// (1) This algorithm is flawed in that as it searches for a path, it may
// output some additional vertices that it visited but were not part
// of the actual path.  Implement the algorithm just as it appears in the textbook.
// 
// (2) This algorithm requires use of the stack and queue containers from the
// Standard Template Library.  The STL stack and queue interfaces may require
// minor modifications to the DFS code from the textbook.

	// first check if both start and end vertices exist
	if(IsPresent(startVertex) == false || IsPresent(endVertex) == false)
	{
		throw GraphVertexNotFound();
	}
	
	// declare queue to hold adjacent vertices and stack to hold possible paths
	queue <string> adjacentVertices;
	stack <string> stack;
	string currentVertex;
	string adjacentVertex;

	ClearMarks();
	stack.push(startVertex);  // push start position

	// while stack not empty and path not found, iterate through stack for path
	while (!stack.empty())
	{
		currentVertex = stack.top();  // set current vertex
		stack.pop();  // pop off element
		// if current vertex is the end vertex, path has been found
		if(currentVertex == endVertex)
		{
			path.push(currentVertex);  // push final vertex to path
			return;  // terminate function
		}
		else
		{
			// if the vertex has not yet been visited
			if(!IsMarked(currentVertex))
			{
				MarkVertex(currentVertex);  // mark vertex as visited
				path.push(currentVertex);  // push to path
				
				// get queue of adjacent vertices, possible next moves
				GetToVertices(currentVertex, adjacentVertices);

				// sort through adjacent vertices
				while(!adjacentVertices.empty())
				{
					adjacentVertex = adjacentVertices.front();
					adjacentVertices.pop();
					// push unvisited adjacent vertices to stack
					if(!IsMarked(adjacentVertex))
					{
						stack.push(adjacentVertex);
					}
				}
			}
		}

	}
	// if no path found, empty path
	while(!path.empty())
	{
		path.pop();
	}
}
