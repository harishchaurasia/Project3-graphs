// data_structures.h
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <cfloat>
#include <vector>

// Define the Vertex structure
struct Vertex
{
    double key;
    int pi;
};

// Define the Edge structure
struct Edge
{
    int index;
    int start;
    int end;
    double weight;
};

// Define the Node for the adjacency list
struct Node
{
    int end;
    double weight;
    Node *next;

    Node(int e, double w, Node *n) : end(e), weight(w), next(n) {}
};

// Define the Adjacency List structure
struct AdjacencyList
{
    Node *head;

    AdjacencyList() : head(nullptr) {}
};

// Define the Element structure for the heap
struct ELEMENT
{
    int vertex;
    double key;
};

// Define the Heap structure
struct HEAP
{
    int capacity;
    int size;
    ELEMENT **H;
    int *position;
};

#endif // DATA_STRUCTURES_H
