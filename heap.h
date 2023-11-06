// // heap.h
// #ifndef HEAP_H
// #define HEAP_H

// #include <vector>

// class Heap
// {
// public:
//     Heap(int capacity);
//     void insert(int element, double key);
//     void decreaseKey(int element, double newKey);
//     int extractMin();
//     bool isEmpty() const;
//     bool contains(int element) const;

// private:
//     std::vector<int> heapArray; // This stores the elements of the heap
//     std::vector<double> keys;   // This parallel array stores the keys of the elements
//     std::vector<int> positions; // This array stores the positions of elements in the heapArray for O(1) access
//     int size;                   // Current size of the heap
//     int capacity;               // Maximum capacity of the heap

//     int parent(int index) const;
//     int leftChild(int index) const;
//     int rightChild(int index) const;
//     void heapify(int index);
//     void swap(int index1, int index2);
// };

// #endif // HEAP_H
