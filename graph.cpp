// graph.cpp
#include "graph.h"
#include <iostream>
#include <iomanip>
#include "data_structures.h"

Graph::Graph(int vertices, bool directed) : numVertices(vertices), isDirected(directed)
{
    // Initialize adjacency lists
    adjLists = new AdjacencyList[numVertices + 1]; // Assuming 1-indexed vertices
    for (int i = 1; i <= numVertices; ++i)
    {
        adjLists[i].head = nullptr;
    }
}

Graph::~Graph()
{
    // Free adjacency lists
    for (int i = 1; i <= numVertices; ++i)
    {
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

// Add edge
void Graph::addEdge(int start, int end, double weight, int flag)
{
    // Create a new node for the edge (u, v)
    Node *newNode = new Node(end, weight, nullptr);

    if (flag == 1)
    {
        // Insert at the front of the list for ADJ[start]
        newNode->next = adjLists[start].head;
        adjLists[start].head = newNode;
    }
    else
    { // flag == 2
        // Insert at the rear of the list for ADJ[start]
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

    // If the graph is undirected, add an edge in the other direction (v, u)
    if (!isDirected)
    {
        Node *newNode2 = new Node(start, weight, nullptr);
        if (flag == 1)
        {
            // Insert at the front for ADJ[end]
            newNode2->next = adjLists[end].head;
            adjLists[end].head = newNode2;
        }
        else
        { // flag == 2
            // Insert at the rear for ADJ[end]
            if (adjLists[end].head == nullptr)
            {
                adjLists[end].head = newNode2;
            }
            else
            {
                Node *current = adjLists[end].head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newNode2;
            }
        }
    }
}

// Print adjacency list
void Graph::printAdjList()
{
    for (int i = 1; i <= numVertices; ++i)
    {
        std::cout << "ADJ[" << i << "]:";
        Node *current = adjLists[i].head;
        while (current != nullptr)
        {
            std::cout << "-->[" << i << " " << current->end << ": " << std::fixed << std::setprecision(2) << current->weight << "]";
            current = current->next;
        }
        std::cout << std::endl;
    }
}
