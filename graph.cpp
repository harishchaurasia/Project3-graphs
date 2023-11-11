// graph.cpp

#include "graph.h"
#include "heap.h"
#include "data_structures.h"
#include "stack.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

Graph::Graph(int vertices, bool directed) : numVertices(vertices), isDirected(directed)
{
    adjLists = new AdjacencyList[numVertices + 1]; // +1 for 1-based indexing
    dist.resize(numVertices + 1, std::numeric_limits<double>::max());
    pred.resize(numVertices + 1, -1);
}

Graph::~Graph()
{
    for (int i = 1; i <= numVertices; ++i) // 1-based indexing
    {
        Node *current = adjLists[i].head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjLists;
}

void Graph::addEdge(int start, int end, double weight, int flag)
{
    // Assuming start and end vertices are 1-indexed
    if (flag == 1)
    {
        insertAtFront(start, end, weight);
        if (!isDirected)
            insertAtFront(end, start, weight);
    }
    else if (flag == 2)
    {
        insertAtRear(start, end, weight);
        if (!isDirected)
            insertAtRear(end, start, weight);
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
            current = current->next;
        current->next = newNode;
    }
}

void Graph::printAdjList()
{
    bool isEmpty = true;
    for (int i = 1; i <= numVertices; ++i)
    {
        if (adjLists[i].head != nullptr)
        {
            isEmpty = false;
            break;
        }
    }

    if (!isEmpty)
    {
        for (int i = 1; i <= numVertices; ++i)
        {
            std::cout << "ADJ[" << i << "]:";
            for (Node *current = adjLists[i].head; current != nullptr; current = current->next)
            {
                std::cout << "-->[" << i << " " << current->end << ": " << std::fixed << std::setprecision(2) << current->weight << "]";
            }
            std::cout << std::endl;
        }
    }
}

void Graph::SinglePair(int source, int destination)
{
    // Perform Dijkstra's algorithm here
    dijkstra(source, destination);
}

void Graph::SingleSource(int source)
{

    // Reset dist and pred arrays for a fresh start
    fill(dist.begin(), dist.end(), std::numeric_limits<double>::max());
    fill(pred.begin(), pred.end(), -1);

    // Perform Dijkstra's algorithm here
    dijkstra(source, -1);
}

void Graph::dijkstra(int startVertex, int dest)
{
    HEAP *heap = initHeap(numVertices);

    // Initialize all vertices' distances as infinity and insert them into the heap
    for (int i = 1; i <= numVertices; i++)
    {
        dist[i] = std::numeric_limits<double>::max();
        ELEMENT *elem = new ELEMENT;
        elem->vertex = i;
        elem->key = dist[i];
        insertHeap(heap, elem);
    }

    dist[startVertex] = 0;
    decreaseKey(heap, startVertex, 0);

    while (heap->size > 0)
    {
        ELEMENT *uElem = extractMin(heap);
        if (!uElem)
        {
            cerr << "extractMin returned a null pointer" << endl;
            break;
        }

        int u = uElem->vertex;
        delete uElem;

        Node *current = adjLists[u].head;
        while (current != nullptr)
        {
            int v = current->end;
            double weight = current->weight;

            if (dist[u] != std::numeric_limits<double>::max() && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                decreaseKey(heap, v, dist[v]);
            }
            current = current->next;
        }
    }
    freeHeap(heap); // Freeing the heap after Dijkstra's algorithm is complete
}

// void Graph::dijkstra(int startVertex, int dest)
// {
//     HEAP *heap = initHeap(numVertices);

//     // Initialize all vertices' distances as infinity and insert them into the heap
//     for (int i = 1; i <= numVertices; i++)
//     {
//         dist[i] = std::numeric_limits<double>::max();
//         ELEMENT *elem = new ELEMENT;
//         elem->vertex = i;
//         elem->key = dist[i];
//         insertHeap(heap, elem);
//     }

//     dist[startVertex] = 0;
//     decreaseKey(heap, heap->H[startVertex]->key, 0); // The decreaseKey function should be called with the key

//     while (heap->size > 0)
//     {
//         ELEMENT *uElem = extractMin(heap);
//         if (!uElem)
//         {
//             cerr << "extractMin returned a null pointer" << endl;
//             break;
//         }

//         int u = uElem->vertex;
//         delete uElem;

//         if (u == dest)
//         {
//             freeHeap(heap); // Free the heap before breaking out of the loop
//             return;         // If destination is reached, end the algorithm
//         }

//         Node *current = adjLists[u].head;
//         while (current != nullptr)
//         {
//             int v = current->end;
//             double weight = current->weight;

//             if (dist[u] != std::numeric_limits<double>::max() && dist[u] + weight < dist[v])
//             {
//                 dist[v] = dist[u] + weight;
//                 pred[v] = u;
//                 decreaseKey(heap, heap->H[v]->key, dist[v]); // The decreaseKey function should be called with the key
//             }
//             current = current->next;
//         }
//     }
//     freeHeap(heap); // Freeing the heap after Dijkstra's algorithm is complete
// }

void Graph::printPath(int source, int destination)
{

    if (dist[destination] == numeric_limits<double>::max())
    {
        cout << "There is no path from " << source << " to " << destination << ".\n";
        return;
    }

    // Reconstruct the path from destination to source using the predecessor array
    vector<int> path;
    for (int at = destination; at != -1; at = pred[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Print the path
    cout << "The shortest path from " << source << " to " << destination << " is:\n";

    // The cost to reach the source from the source is always 0
    cout << "[" << source << ":    0.00]";

    double totalCost = 0.0;
    for (size_t i = 1; i < path.size(); ++i)
    {
        totalCost += getEdgeWeight(path[i - 1], path[i]);
        cout << "-->[" << path[i] << ":    " << fixed << setprecision(2) << totalCost << "]";
    }

    cout << ".\n";
}

double Graph::getEdgeWeight(int source, int destination)
{
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

void Graph::printLength(int s, int t)
{
    // Since vertices are 1-indexed, no adjustment is needed for accessing dist array
    if (dist[t] != std::numeric_limits<double>::max())
    {
        std::cout << "The length of the shortest path from " << s << " to " << t << " is:     "
                  << std::fixed << std::setprecision(2) << dist[t] << std::endl;
    }
    else
    {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}
