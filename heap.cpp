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
    heap->position = (int *)malloc((capacity + 1) * sizeof(int));     // +1 for 1-based indexing

    if (!heap->H || !heap->position)
    {
        fprintf(stderr, "Memory error: Cannot initialize heap structures.\n");
        free(heap->H);
        free(heap->position);
        free(heap);
        return NULL;
    }

    for (int i = 0; i <= capacity; i++)
    {
        heap->H[i] = NULL;     // Initialize all elements to NULL
        heap->position[i] = 0; // Initialize position mapping
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

        // Update position mapping
        heap->position[heap->H[i]->vertex] = i;
        heap->position[heap->H[smallest]->vertex] = smallest;

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
    heap->position[element->vertex] = position;

    while (position > 1 && heap->H[position / 2]->key > heap->H[position]->key)
    {
        ELEMENT *temp = heap->H[position];
        heap->H[position] = heap->H[position / 2];
        heap->H[position / 2] = temp;

        heap->position[heap->H[position]->vertex] = position;
        heap->position[heap->H[position / 2]->vertex] = position / 2;

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
    heap->position[min->vertex] = 0;
    heap->H[1] = heap->H[heap->size];
    heap->position[heap->H[1]->vertex] = 1;
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

        heap->position[heap->H[index]->vertex] = index;
        // Continue updating the position mapping
        heap->position[heap->H[index / 2]->vertex] = index / 2;

        index /= 2;
    }
}

void printHeap(HEAP *heap)
{
    printf("Heap size: %d\n", heap->size);
    for (int i = 1; i <= heap->size; i++)
    {
        printf("Vertex: %d, Key: %.2f\n", heap->H[i]->vertex, heap->H[i]->key);
    }
}

void freeHeap(HEAP *heap)
{
    if (!heap)
        return;

    if (heap->H)
    {
        for (int i = 1; i <= heap->capacity; i++)
        {
            if (heap->H[i])
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
