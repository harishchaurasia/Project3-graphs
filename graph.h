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
    void singleSourceShortestPath(int source);
    void printPath(int s, int t);
    double getEdgeWeight(int source, int destination);

    // Get the number of vertices in the graph
    int getNumVertices() const { return numVertices; }
    // Get the distance of a vertex from the source after running Dijkstra's algorithm
    double getDistance(int vertex) const { return dist[vertex]; }
    // Get the predecessor of a vertex in the shortest path tree
    int getPredecessor(int vertex) const { return pred[vertex]; }

private:
    int numVertices;
    bool isDirected;
    AdjacencyList *adjLists;

    // Helper methods for adding edges
    void insertAtFront(int start, int end, double weight);
    void insertAtRear(int start, int end, double weight);
    // Add additional members as needed
    std::vector<double> dist;
    std::vector<int> pred;
};

#endif // GRAPH_H
