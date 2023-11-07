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
    // Add additional members as needed
};

// Define the Edge structure
struct Edge
{
    int index;
    int start;
    int end;
    double weight;
    // Add additional members as needed
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
    // Add methods as needed
};

// Define the Heap structure
typedef struct
{
    int vertex; // This might be needed to keep track of the vertex number in Dijkstra's algorithm
    double key;
    // Any other information that might be needed for the heap elements
} ELEMENT;

typedef struct
{
    int capacity;
    int size;
    ELEMENT **H; // Array of pointers to ELEMENT
    // You may need a heapify count if you're keeping track of the number of heapify operations
} HEAP;

#endif // DATA_STRUCTURES_H
