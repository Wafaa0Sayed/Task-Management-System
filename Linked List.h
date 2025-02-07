#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;

        Node(const T& newData) : data(newData), next(nullptr) {}
    };

    Node* head;
    int size;

    LinkedList();
    ~LinkedList();

    void addItem(const T& item);
    bool isEmpty() const;
    int getSize() const;

    Node* getHead() const ;
    void setHead(Node* newHead) { head = newHead; }
};
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::addItem(const T& item) {
    Node* newNode = new Node(item);
    newNode->next = head;
    head = newNode;
    size++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

#endif // LINKEDLIST_H
