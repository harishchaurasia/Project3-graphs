// graph.cpp

#include "graph.h"
#include "heap.h"
#include "data_structures.h"
#include "stack.h"
#include <iostream>
#include <iomanip>

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
    for (int i = 1; i <= numVertices; ++i) // 1-based indexing
    {
        cout << "ADJ[" << i << "]:";
        Node *current = adjLists[i].head;
        while (current != nullptr)
        {
            cout << "-->[" << i << " " << current->end << ": " << fixed << setprecision(2) << current->weight << "]";
            current = current->next;
        }
        cout << endl;
    }
}

void Graph::SinglePair(int source, int destination)
{
    // Perform Dijkstra's algorithm here
    dijkstra(source, destination);
}

void Graph::dijkstra(int startVertex, int dest)
{
    HEAP *heap = initHeap(numVertices);
    if (!heap)
    {
        cerr << "Failed to initialize heap" << endl;
        return;
    }

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

void Graph::printPath(int source, int destination)
{
    // Adjust the indices to be 1-based for internal vector access
    // cout << "Distances in printPath function:" << endl;
    // for (int i = 1; i <= numVertices; ++i)
    // {
    //     cout << "Vertex " << i << ": " << dist[i] << " (pred: " << pred[i] << ")" << endl;
    // }

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
    if (dist[t] != std::numeric_limits<double>::max())
    {
        std::cout << "Shortest path length from " << s << " to " << t << " is: " << dist[t] << std::endl;
    }
    else
    {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}

// void Graph::printShortestPath(int source, int destination)
// {
//     // Adjust the indices to be 0-based for internal vector access
//     source--;
//     destination--;

//     if (dist[destination] == numeric_limits<double>::max())
//     {
//         cout << "There is no path from " << source + 1 << " to " << destination + 1 << ".\n";
//         return;
//     }

//     // Print the path
//     cout << "The shortest path from " << source + 1 << " to " << destination + 1 << " is:\n";
//     cout << "[" << source + 1 << ": 0.00]"; // The cost to reach the source from the source is always 0

//     // Initialize the total cost from source
//     double totalCost = 0.0;

//     for (size_t i = 1; i < shortestPath.size(); ++i)
//     {
//         // The cost to reach the current vertex from the source is the distance to the predecessor plus the edge weight
//         totalCost += getEdgeWeight(shortestPath[i - 1], shortestPath[i]);

//         // Print the current vertex and the total cost to reach it from the source
//         cout << "-->[" << shortestPath[i] + 1 << ": " << fixed << setprecision(2) << totalCost << "]";
//     }

//     cout << ".\n";
// }