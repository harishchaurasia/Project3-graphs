#include "graph.h"
#include "heap.h"
#include <iostream>
#include "data_structures.h"
#include "stack.h"
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

int lastSingleSource;

Graph::Graph(int vertices, bool directed) : numVertices(vertices), isDirected(directed)
{
    adjLists = new AdjacencyList[numVertices + 1]; // using +1 for 1-based indexing
    dist.resize(numVertices + 1, std::numeric_limits<double>::max());
    pred.resize(numVertices + 1, -2);
}

Graph::~Graph()
{
    for (int i = 1; i <= numVertices; ++i) // using 1-based indexing
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
    // start and end vertices are 1-indexed
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

    lastSingleSource = source;
    // Ensuring dist and pred arrays are resized and initialized
    dist.resize(numVertices + 1, numeric_limits<double>::max());
    pred.resize(numVertices + 1, -1);

    // Performing Dijkstra's algorithm to compute the shortest paths
    dijkstra(source, destination);
}

void Graph::SingleSource(int source)
{
    lastSingleSource = source;
    for (int i = 1; i <= numVertices; i++) // since vertices are 1-indexed
    {
        dist[i] = std::numeric_limits<double>::max();
        pred[i] = -1;
    }

    dist[source] = 0;

    dijkstra(source);
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

void Graph::printPath(int source, int destination)
{

    if (source != lastSingleSource && pred[destination] == -2)
    {
        // do nothing
        return;
    }
    else
    {
        if (dist[destination] == std::numeric_limits<double>::max() || (pred[destination] == -1))
        {
            // If there's no path at all, we print this

            std::cout << "There is no path from " << source << " to " << destination << ".\n";
        }
    }
    if (source != lastSingleSource || pred[destination] == -2)
    {
        // do nothing
        // std::cout << "";
        return;
    }

    std::vector<int> path;
    for (int at = destination; at != -1; at = pred[at])
    {
        path.push_back(at);
        if (at == source)
        {
            break; // Break if the source is reached
        }
    }

    // If the path does not start from the specified source, print nothing
    if (path.empty() || path.back() != source)
    {
        return;
    }

    std::reverse(path.begin(), path.end());

    // Print the path starting from the source
    std::cout << "The shortest path from " << source << " to " << destination << " is:\n";
    double totalCost = 0.0;
    std::cout << "[" << path[0] << ":    " << std::fixed << std::setprecision(2) << totalCost << "]";
    for (size_t i = 1; i < path.size(); ++i)
    {
        int from = path[i - 1];
        int to = path[i];
        double weight = getEdgeWeight(from, to);
        totalCost += weight;
        std::cout << "-->"
                  << "[" << std::setw(1) << to << ":" << std::fixed << std::setw(8) << std::setprecision(2) << totalCost << "]";
    }

    std::cout << ".\n";
}

double Graph::getEdgeWeight(int source, int destination)
{
    for (Node *current = adjLists[source].head; current != nullptr; current = current->next)
    {
        if (current->end == destination)
        {
            return current->weight;
        }
    }
    return std::numeric_limits<double>::infinity();
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
