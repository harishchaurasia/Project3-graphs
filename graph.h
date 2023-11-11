// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include <string>
#include <vector>
#include <limits>

class Graph
{
public:
    Graph(int vertices, bool directed);
    ~Graph();
    AdjacencyList *adjLists;
    void addEdge(int start, int end, double weight, int flag);
    void printAdjList();

    void dijkstra(int source, int dest);
    void SinglePair(int source, int destination);
    void SingleSource(int source);
    void printPath(int s, int t);
    void printLength(int s, int t);
    double getEdgeWeight(int source, int destination);

    int getNumVertices() const { return numVertices; }
    double getDistance(int vertex)
    {
        return dist[vertex];
    }
    int getPredecessor(int vertex) const { return pred[vertex]; }

    int numVertices;
    bool isDirected;

    std::vector<double> dist;
    std::vector<int> pred;
    std::vector<int> shortestPath;

    void insertAtFront(int start, int end, double weight);
    void insertAtRear(int start, int end, double weight);
};

#endif // GRAPH_H
