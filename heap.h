/*
Name: Harish Chaurasia
ASU ID: 1225120117
*/

// heap.h

#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

HEAP *initHeap(int capacity);

int insertHeap(HEAP *heap, ELEMENT *element);

ELEMENT *extractMin(HEAP *heap);

void decreaseKey(HEAP *heap, int vertex, double newKey);

void buildHeap(HEAP *heap);

void printHeap(HEAP *heap);

void freeHeap(HEAP *heap);

void heapify(HEAP *heap, int index);

bool updateKey(HEAP *heap, int vertex, double newKey);

#endif // HEAP_H
