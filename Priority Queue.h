#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <functional>
#include <string>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    T* items;
    int size;
    int capacity;

    void resize();
    void heapifyUp(int index);
    void heapifyDown(int index);

    function<bool( T&,  T&)> compare;

public:
    PriorityQueue(function<bool( T&,  T&)> compareFunc);
    ~PriorityQueue();

    PriorityQueue(const PriorityQueue& other) {
        size = other.size;
        capacity = other.capacity;
        compare = other.compare;
        items = new T[capacity];
        for (int i = 0; i < size; ++i) {
            items[i] = other.items[i];
        }
    }

    void addItem(const T& item);
    void removeItem(const T& item);
    const T& getTopItem() const;

    bool isEmpty() const;
    int getSize() const;

    void sort();
};


template <typename T>
PriorityQueue<T>::PriorityQueue(function<bool( T&,  T&)> compareFunc)
    : size(0), capacity(10), compare(compareFunc) {
    items = new T[capacity];
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
    delete[] items;
}



template <typename T>
void PriorityQueue<T>::resize() {
    capacity *= 2;
    T* newItems = new T[capacity];

    for (int i = 0; i < size; ++i) {
        newItems[i] = items[i];
    }

    delete[] items;
    items = newItems;
}


template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;

        if (compare(items[index], items[parentIndex])) {
            swap(items[index], items[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && compare(items[leftChild], items[smallest])) {
            smallest = leftChild;
        }
        if (rightChild < size && compare(items[rightChild], items[smallest])) {
            smallest = rightChild;
        }
        if (smallest == index) break;

        swap(items[index], items[smallest]);
        index = smallest;
    }
}


template <typename T>
void PriorityQueue<T>::addItem(const T& item) {
    if (size == capacity) {
        resize();
    }
    items[size++] = item;
    heapifyUp(size - 1);
}

template <typename T>
void PriorityQueue<T>::removeItem(const T& item) {
    if (size == 0) {
        cout << "Priority queue is empty!" << endl;
        return;
    }

    int indexToRemove = -1;
    for (int i = 0; i < size; i++) {
        if (items[i] == item) {
            indexToRemove = i;
            break;
        }
    }

    items[indexToRemove] = items[size - 1];
    size--;

    if (indexToRemove > 0 && compare(items[indexToRemove], items[(indexToRemove - 1) / 2])) {
        heapifyUp(indexToRemove);
    } else {
        heapifyDown(indexToRemove);
    }
}

template <typename T>
const T& PriorityQueue<T>::getTopItem() const {
    if (size > 0) {
        return items[0];
    } else {
        throw out_of_range("Priority queue is empty");
    }
}



template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int PriorityQueue<T>::getSize() const {
    return size;
}

template <typename T>
void PriorityQueue<T>::sort() {
    int originalSize = size;

    for (int i = originalSize / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }

    for (int i = originalSize - 1; i > 0; --i) {
        swap(items[0], items[i]);
        size--;
        heapifyDown(0);
    }

    size = originalSize;
}

#endif // PRIORITYQUEUE_H
