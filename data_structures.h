/*
Name: Harish Chaurasia
ASU ID: 1225120117
*/

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <cfloat>
#include <vector>

// Defining the Vertex structure
struct Vertex
{
    double key;
    int pi;
};

// Defining the Edge structure
struct Edge
{
    int index;
    int start;
    int end;
    double weight;
};

// Defining the Node for the adjacency list
struct Node
{
    int end;
    double weight;
    Node *next;

    Node(int e, double w, Node *n) : end(e), weight(w), next(n) {}
};

// Defining the Adjacency List structure
struct AdjacencyList
{
    Node *head;

    AdjacencyList() : head(nullptr) {}
};

// Defining the Element structure for the heap
struct ELEMENT
{
    int vertex;
    double key;
};

// Defining the Heap structure
struct HEAP
{
    int capacity;
    int size;
    ELEMENT **H;
    int *position;
};

#endif
