// heap.cpp

#include "heap.h"
#include "data_structures.h"
#include <iostream>
#include <cstdio>
#include <cfloat> // For DBL_MAX
#include <cstdlib>
using namespace std;

HEAP *initHeap(int capacity)
{
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (!heap)
    {
        fprintf(stderr, "Memory error: Cannot initialize heap.\n");
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (ELEMENT **)malloc((capacity + 1) * sizeof(ELEMENT *)); // +1 for 1-based indexing
    if (!heap->H)
    {
        fprintf(stderr, "Memory error: Cannot initialize heap array.\n");
        free(heap);
        return NULL;
    }

    heap->position = (int *)malloc((capacity + 1) * sizeof(int)); // +1 for 1-based indexing
    if (!heap->position)
    {
        fprintf(stderr, "Memory error: Cannot initialize heap position array.\n");
        free(heap->H);
        free(heap);
        return NULL;
    }

    return heap;
}

void heapify(HEAP *heap, int i)
{
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= heap->size && heap->H[left]->key < heap->H[smallest]->key)
    {
        smallest = left;
    }

    if (right <= heap->size && heap->H[right]->key < heap->H[smallest]->key)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        ELEMENT *temp = heap->H[i];
        heap->H[i] = heap->H[smallest];
        heap->H[smallest] = temp;
        heapify(heap, smallest);
    }
}

void buildHeap(HEAP *heap)
{
    for (int i = heap->size / 2; i >= 1; i--)
    {
        heapify(heap, i);
    }
}

int insertHeap(HEAP *heap, ELEMENT *element)
{
    if (heap->size >= heap->capacity)
    {
        fprintf(stderr, "Error: Heap is full.\n");
        return -1;
    }

    heap->size++;
    int position = heap->size;
    heap->H[position] = element;

    while (position > 1 && heap->H[position / 2]->key > heap->H[position]->key)
    {
        ELEMENT *temp = heap->H[position];
        heap->H[position] = heap->H[position / 2];
        heap->H[position / 2] = temp;
        position /= 2;
    }

    return position;
}

ELEMENT *extractMin(HEAP *heap)
{
    if (heap->size < 1)
    {
        fprintf(stderr, "Error: Heap is empty.\n");
        return NULL;
    }

    ELEMENT *min = heap->H[1];
    heap->H[1] = heap->H[heap->size];
    heap->H[heap->size] = NULL;
    heap->size--;
    if (heap->size > 0)
    {
        heapify(heap, 1);
    }

    return min;
}

void decreaseKey(HEAP *heap, int vertex, double newKey)
{
    int index = heap->position[vertex];
    if (index == 0 || heap->H[index]->key <= newKey)
    {
        return;
    }

    heap->H[index]->key = newKey;
    while (index > 1 && heap->H[index / 2]->key > heap->H[index]->key)
    {
        ELEMENT *temp = heap->H[index];
        heap->H[index] = heap->H[index / 2];
        heap->H[index / 2] = temp;

        // Update the position mapping
        heap->position[heap->H[index]->vertex] = index;
        heap->position[heap->H[index / 2]->vertex] = index / 2;

        index /= 2;
    }
}

void printHeap(HEAP *heap)
{
    printf("Heap size: %d\n", heap->size);
    for (int i = 1; i <= heap->size; i++)
    {
        printf("Key of element at position %d: %.2f\n", i, heap->H[i]->key);
    }
}
void freeHeap(HEAP *heap)
{
    if (!heap)
        return;

    if (heap->H)
    {
        for (int i = 1; i <= heap->capacity; i++) // Assuming 1-based indexing
        {
            if (heap->H[i]) // Check if the element exists before freeing
            {
                free(heap->H[i]);
            }
        }
        free(heap->H);
    }
    if (heap->position)
    {
        free(heap->position);
    }
    free(heap);
}

bool updateKey(HEAP *heap, int vertex, double newKey)
{
    int index = heap->position[vertex];

    // If the vertex is not in the heap or the new key is not smaller, return false
    if (index == 0 || heap->H[index]->key <= newKey)
    {
        return false;
    }

    heap->H[index]->key = newKey;

    while (index > 1 && heap->H[index / 2]->key > heap->H[index]->key)
    {
        ELEMENT *temp = heap->H[index];
        heap->H[index] = heap->H[index / 2];
        heap->H[index / 2] = temp;

        heap->position[heap->H[index]->vertex] = index;
        heap->position[heap->H[index / 2]->vertex] = index / 2;

        index /= 2;
    }

    return true;
}
