// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include <string>

class Graph
{
public:
    Graph(int vertices, bool directed);
    ~Graph();
    void addEdge(int start, int end, double weight, int flag);
    void printAdjList();
    // Add additional methods as needed

private:
    int numVertices;
    bool isDirected;
    AdjacencyList *adjLists;
    // Helper methods for adding edges
    void insertAtFront(int start, int end, double weight);
    void insertAtRear(int start, int end, double weight);
    // Add additional members as needed
};

#endif // GRAPH_H
