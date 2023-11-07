// util.cpp
#include "util.h"
#include "heap.h"
#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>

void dijkstra(Graph &graph, int source)
{
    graph.singleSourceShortestPath(source);
}

void printPath(Graph &graph, int source, int destination)
{
    // The 'graph' should contain the necessary information from the last run of dijkstra
    graph.printPath(source, destination);
}

void printLength(Graph &graph, int source, int destination)
{
    // The 'graph' should contain the necessary information from the last run of dijkstra
    if (source < 1 || source > graph.getNumVertices() || destination < 1 || destination > graph.getNumVertices())
    {
        std::cout << "Path does not exist.\n";
        return;
    }

    // Convert to 0-based indexing for internal representation
    source--;
    destination--;

    if (graph.getDistance(destination) == DBL_MAX)
    {
        std::cout << "There is no path from " << source + 1 << " to " << destination + 1 << ".\n";
    }
    else
    {
        std::cout << "The length from " << source + 1 << " to " << destination + 1 << " is " << graph.getDistance(destination) << ".\n";
    }
}

// double getEdgeWeight(const Graph &graph, int source, int destination)
// {
//     // This should call a method from the Graph class that retrieves the edge weight
//     return graph.getEdgeWeight(source - 1, destination - 1); // Assuming 1-based input
// }
