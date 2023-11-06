// graph.cpp
#include "graph.h"
#include <iostream>
#include <iomanip>
#include "data_structures.h"

Graph::Graph(int vertices, bool directed) : numVertices(vertices), isDirected(directed)
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

// void Graph::addEdge(int start, int end, double weight, int flag)
// {
//     // Convert 1-indexed vertices to 0-indexed for internal representation

//     if (flag == 1)
//     {
//         // Insert at the front for directed graph or both ends for undirected graph
//         insertAtFront(start, end, weight);
//         if (!isDirected)
//         {
//             insertAtFront(end, start, weight);
//         }
//     }
//     else if (flag == 2)
//     {
//         // Insert at the rear for directed graph or both ends for undirected graph
//         insertAtRear(start, end, weight);
//         if (!isDirected)
//         {
//             insertAtRear(end, start, weight);
//         }
//     }
// }

void Graph::addEdge(int start, int end, double weight, int flag)
{
    // Convert 1-indexed vertices to 0-indexed for internal representation
    // start -= 1;
    // end -= 1;

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
