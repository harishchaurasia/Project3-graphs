// // heap.cpp
// #include "heap.h"
// #include <algorithm>
// #include <stdexcept>

// Heap::Heap(int capacity) : capacity(capacity), size(0), heapArray(capacity + 1), keys(capacity + 1), positions(capacity + 1, -1) {}

// void Heap::insert(int element, double key)
// {
//     if (size == capacity)
//     {
//         throw std::overflow_error("Heap capacity exceeded");
//     }
//     // Insert new element at the end of the heap
//     size++;
//     heapArray[size] = element;
//     keys[element] = key;
//     positions[element] = size;
//     // Fix the min-heap property if it is violated
//     int i = size;
//     while (i != 1 && keys[heapArray[parent(i)]] > keys[heapArray[i]])
//     {
//         swap(i, parent(i));
//         i = parent(i);
//     }
// }

// void Heap::decreaseKey(int element, double newKey)
// {
//     // Decrease the value of key for element
//     if (!contains(element))
//     {
//         throw std::invalid_argument("Element not found in heap");
//     }
//     keys[element] = newKey;
//     int i = positions[element];
//     while (i != 1 && keys[heapArray[parent(i)]] > keys[heapArray[i]])
//     {
//         swap(i, parent(i));
//         i = parent(i);
//     }
// }

// int Heap::extractMin()
// {
//     if (size == 0)
//     {
//         throw std::underflow_error("Heap is empty");
//     }
//     // The root of the heap is the minimum element
//     int minElement = heapArray[1];
//     heapArray[1] = heapArray[size];
//     positions[heapArray[1]] = 1;
//     size--;
//     heapify(1);                 // Heapify the root
//     positions[minElement] = -1; // Mark the extracted element as not in heap
//     return minElement;
// }

// bool Heap::isEmpty() const
// {
//     return size == 0;
// }

// bool Heap::contains(int element) const
// {
//     return positions[element] != -1;
// }

// int Heap::parent(int index) const
// {
//     return index / 2;
// }

// int Heap::leftChild(int index) const
// {
//     return 2 * index;
// }

// int Heap::rightChild(int index) const
// {
//     return 2 * index + 1;
// }

// void Heap::heapify(int index)
// {
//     int left = leftChild(index);
//     int right = rightChild(index);
//     int smallest = index;
//     if (left <= size && keys[heapArray[left]] < keys[heapArray[index]])
//     {
//         smallest = left;
//     }
//     if (right <= size && keys[heapArray[right]] < keys[heapArray[smallest]])
//     {
//         smallest = right;
//     }
//     if (smallest != index)
//     {
//         swap(index, smallest);
//         heapify(smallest);
//     }
// }

// void Heap::swap(int index1, int index2)
// {
//     std::swap(positions[heapArray[index1]], positions[heapArray[index2]]);
//     std::swap(heapArray[index1], heapArray[index2]);
//     std::swap(keys[heapArray[index1]], keys[heapArray[index2]]);
// }
