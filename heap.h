/*
Name: Harish Chaurasia
ASU ID: 1225120117
*/

#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

// To initialize a new heap with the given capacity
HEAP *initHeap(int capacity);

// To insert a new element with the given key into the heap
int insertHeap(HEAP *heap, ELEMENT *element);

// To extract the minimum element from the heap
ELEMENT *extractMin(HEAP *heap);

// To decrease the key of an element at a given position in the heap
bool decreaseKey(HEAP *heap, int position, double newKey);

// To build a min heap from an unsorted array
void buildHeap(HEAP *heap);

// To Print the current heap
void printHeap(HEAP *heap);

// To free the memory allocated for the heap
void freeHeap(HEAP *heap);

bool isMinHeap(HEAP *heap);
#endif
