// graph.cpp
#include "graph.h"
#include <vector>
#include <limits>
#include "heap.h"
#include <iostream>
#include <iomanip>
#include "data_structures.h"

Graph::Graph(int vertices, bool directed)
    : numVertices(vertices), isDirected(directed), adjLists(new AdjacencyList[vertices]), dist(vertices, std::numeric_limits<double>::max()), pred(vertices, -1)
{
    // Initialize adjacency lists
    adjLists = new AdjacencyList[numVertices]; // Correct indexing for C++
    for (int i = 0; i < numVertices; ++i)
    { // Use 0-based indexing
        adjLists[i].head = nullptr;
    }
}

Graph::~Graph()
{
    // Free adjacency lists
    for (int i = 0; i < numVertices; ++i)
    { // Use 0-based indexing
        Node *current = adjLists[i].head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] adjLists;
}

void Graph::addEdge(int start, int end, double weight, int flag)
{
    // Convert 1-indexed vertices to 0-indexed for internal representationStop

    if (flag == 1)
    {
        // Insert at the front for directed graph or both ends for undirected graph
        insertAtFront(start, end, weight);
        if (!isDirected)
        {
            insertAtFront(end, start, weight);
        }
    }
    else if (flag == 2)
    {
        // Insert at the rear for directed graph or both ends for undirected graph
        insertAtRear(start, end, weight);
        if (!isDirected)
        {
            insertAtRear(end, start, weight);
        }
    }
}

void Graph::insertAtFront(int start, int end, double weight)
{
    Node *newNode = new Node(end, weight, adjLists[start].head);
    adjLists[start].head = newNode;
}

void Graph::insertAtRear(int start, int end, double weight)
{
    Node *newNode = new Node(end, weight, nullptr);
    if (adjLists[start].head == nullptr)
    {
        adjLists[start].head = newNode;
    }
    else
    {
        Node *current = adjLists[start].head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Graph::printAdjList()
{
    for (int i = 0; i < numVertices; ++i)
    {
        std::cout << "ADJ[" << (i + 1) << "]:";
        Node *current = adjLists[i].head;
        while (current != nullptr)
        {
            std::cout << "-->[" << (i + 1) << " " << (current->end + 1) << ": " << std::fixed << std::setprecision(2) << current->weight << "]";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

// Assuming the Vertex and Graph classes are defined with necessary attributes and methods
// void Graph::singleSourceShortestPath(int source)
// {
//     // Initialize single source
//     std::vector<double> dist(numVertices, std::numeric_limits<double>::max()); // Distance from source to all vertices
//     std::vector<int> pred(numVertices, -1);                                    // Predecessors of all vertices
//     std::vector<bool> visited(numVertices, false);                             // Visited vertices

//     HEAP *minHeap = initHeap(numVertices);
//     dist[source] = 0.0; // Distance from source to itself is always 0

//     // Insert all vertices with their distances into the min-heap
//     for (int i = 0; i < numVertices; ++i)
//     {
//         ELEMENT *vertexElement = (ELEMENT *)malloc(sizeof(ELEMENT));
//         vertexElement->vertex = i;
//         vertexElement->key = dist[i];
//         insertHeap(minHeap, vertexElement->key);
//     }

//     // Main loop of Dijkstra's algorithm
//     while (minHeap->size > 0)
//     {
//         ELEMENT *uElement = extractMin(minHeap);
//         int u = uElement->vertex;
//         free(uElement);

//         if (visited[u])
//             continue;      // Skip if vertex is already visited
//         visited[u] = true; // Mark this vertex as visited

//         // Iterate through all adjacent vertices (neighbors) of u
//         for (Node *neighbor = adjLists[u].head; neighbor != nullptr; neighbor = neighbor->next)
//         {
//             int v = neighbor->end;
//             double weight = neighbor->weight;

//             // Relaxation step
//             if (!visited[v] && dist[u] + weight < dist[v])
//             {
//                 dist[v] = dist[u] + weight;       // Update distance
//                 pred[v] = u;                      // Update predecessor
//                 decreaseKey(minHeap, v, dist[v]); // Update the distance in the min-heap
//             }
//         }
//     }

//     // At this point, dist and pred arrays have the shortest distances and the predecessors
//     freeHeap(minHeap); // Don't forget to free the heap

//     // If you need to retrieve the shortest path from source to a particular vertex,
//     // you can backtrack from the destination vertex using the pred array.
//     // For example, to get the path from source to vertex 'dest':
//     // int dest = /* some destination vertex */;
//     int dest = source;
//     std::vector<int> path;
//     for (int at = dest; at != -1; at = pred[at])
//     {
//         path.push_back(at);
//     }
//     std::reverse(path.begin(), path.end()); // The path is in reverse order, from dest to source, so reverse it

//     // Now 'path' contains the shortest path from 'source' to 'dest'
//     // Do something with the 'path', like printing it or processing it further
// }

void Graph::singleSourceShortestPath(int source)
{
    // Initialize single source
    std::fill(dist.begin(), dist.end(), std::numeric_limits<double>::max());
    std::fill(pred.begin(), pred.end(), -1);
    std::vector<bool> visited(numVertices, false);

    HEAP *minHeap = initHeap(numVertices);
    dist[source - 1] = 0.0; // Assuming source is 1-indexed

    // Insert all vertices with their distances into the min-heap
    for (int i = 0; i < numVertices; ++i)
    {
        ELEMENT *vertexElement = (ELEMENT *)malloc(sizeof(ELEMENT));
        vertexElement->vertex = i;
        vertexElement->key = dist[i];
        insertHeap(minHeap, vertexElement);
    }

    // Main loop of Dijkstra's algorithm
    while (minHeap->size > 0)
    {
        ELEMENT *uElement = extractMin(minHeap);
        int u = uElement->vertex;
        free(uElement);

        if (visited[u])
            continue;      // Skip if vertex is already visited
        visited[u] = true; // Mark this vertex as visited

        // Iterate through all adjacent vertices (neighbors) of u
        for (Node *neighbor = adjLists[u].head; neighbor != nullptr; neighbor = neighbor->next)
        {
            int v = neighbor->end;
            double weight = neighbor->weight;

            // Relaxation step
            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight; // Update distance
                pred[v] = u;                // Update predecessor
                // Here, you need to find the vertex in the heap and decrease its key
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }

    freeHeap(minHeap); // Don't forget to free the heap
}

void Graph::printPath(int s, int t)
{
    // Convert 1-indexed input to 0-indexed
    s--;
    t--;

    if (s < 0 || s >= numVertices || t < 0 || t >= numVertices || pred[s] == -1 || dist[t] == DBL_MAX)
    {
        std::cout << "There is no path from " << s + 1 << " to " << t + 1 << ".\n";
        return;
    }

    std::vector<int> path;
    for (int at = t; at != -1; at = pred[at])
    {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Check if the path is valid for the source 's'
    if (path.front() != s)
    {
        std::cout << "There is no path from " << s + 1 << " to " << t + 1 << ".\n";
        return;
    }

    // Print the path
    std::cout << "Path from " << s + 1 << " to " << t + 1 << ": ";
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i] + 1; // Convert 0-indexed back to 1-indexed for output
        if (i < path.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

double Graph::getEdgeWeight(int source, int destination)
{
    // Assuming edges are stored in a list and each node in the list has a 'weight' attribute
    Node *current = adjLists[source].head;
    while (current != nullptr)
    {
        if (current->end == destination)
        {
            return current->weight;
        }
        current = current->next;
    }
    return std::numeric_limits<double>::infinity(); // Return infinity if no edge exists
}