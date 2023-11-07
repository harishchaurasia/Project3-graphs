#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

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
    heap->H = (ELEMENT **)malloc((capacity + 1) * sizeof(ELEMENT *)); // +1 to handle 1-indexed heap
    if (!heap->H)
    {
        fprintf(stderr, "Memory error: Cannot initialize heap array.\n");
        free(heap);
        return NULL;
    }

    for (int i = 0; i <= capacity; i++)
    {
        heap->H[i] = NULL; // Initialize all elements to NULL
    }

    return heap;
}

void heapify(HEAP *heap, int i)
{
    int smallest = i;
    int left = 2 * i + 1;  // Corrected to 0-based index
    int right = 2 * i + 2; // Corrected to 0-based index

    if (left < heap->size && heap->H[left]->key < heap->H[smallest]->key)
    {
        smallest = left;
    }

    if (right < heap->size && heap->H[right]->key < heap->H[smallest]->key)
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
    { // Start from the last parent node
        heapify(heap, i);
    }
}

int insertHeap(HEAP *heap, ELEMENT *element)
{
    if (heap->size == heap->capacity)
    {
        fprintf(stderr, "Error: Heap is full.\n");
        return -1;
    }

    // Insert the element at the end of the heap array
    int position = heap->size;
    heap->H[position] = element;

    // Bubble up the element to maintain the heap property
    while (position > 0 && heap->H[(position - 1) / 2]->key > heap->H[position]->key)
    {
        ELEMENT *temp = heap->H[position];
        heap->H[position] = heap->H[(position - 1) / 2];
        heap->H[(position - 1) / 2] = temp;
        position = (position - 1) / 2;
    }

    heap->size++;
    return position; // Return the position where the element was inserted
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
    heap->size--;
    heapify(heap, 1);

    return min;
}

bool decreaseKey(HEAP *heap, int position, double newKey)
{
    if (position < 1 || position > heap->size || heap->H[position]->key < newKey)
    {
        fprintf(stderr, "Error: Invalid call to decreaseKey.\n");
        return false;
    }

    heap->H[position]->key = newKey;
    while (position > 1 && heap->H[position / 2]->key > heap->H[position]->key)
    {
        ELEMENT *temp = heap->H[position];
        heap->H[position] = heap->H[position / 2];
        heap->H[position / 2] = temp;
        position = position / 2;
    }

    return true;
}

void printHeap(HEAP *heap)
{
    printf("Heap size: %d\n", heap->size);
    for (int i = 1; i <= heap->size; i++)
    {
        printf("Key of element at position %d: %.6lf\n", i, heap->H[i]->key);
    }
}

void freeHeap(HEAP *heap)
{
    if (heap->H)
    {
        for (int i = 1; i <= heap->capacity; i++)
        {
            free(heap->H[i]); // heap->H[i] may be NULL if it was extracted
        }
        free(heap->H);
    }
    free(heap);
}

bool isMinHeap(HEAP *heap)
{
    for (int i = 1; i <= heap->size / 2; i++)
    {
        if ((2 * i <= heap->size && heap->H[i]->key > heap->H[2 * i]->key) ||
            (2 * i + 1 <= heap->size && heap->H[i]->key > heap->H[2 * i + 1]->key))
        {
            return false;
        }
    }
    return true;
}
