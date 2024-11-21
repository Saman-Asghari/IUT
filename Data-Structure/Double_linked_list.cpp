#include "Double_linked_list.h"
template<class T>
Double_linked_list<T>::Double_linked_list() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}
template<class T>
Double_linked_list<T>::~Double_linked_list() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}
template<class T>
int Double_linked_list<T>::get_size() const {
    return size;
}
template<class T>
void Double_linked_list<T>::push_back(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}
template<class T>
void Double_linked_list<T>::push_front(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}
template<class T>
T Double_linked_list<T>::pop_back() {
    if (tail == nullptr) {
        return;
    }

    Node<T>* temp = tail;
    tail = tail->prev;

    if (tail != nullptr) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    size--;
    return temp->data;
}
template<class T>
T Double_linked_list<T>::pop_front() {
    if (head == nullptr) {
        return NULL;
    }

    Node<T>* temp = head;
    head = head->next;

    if (head != nullptr) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    size--;
    return temp->data;
}
template<class T>
T Double_linked_list<T>::find_on_index(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->data;
}
template<class T>
void Double_linked_list<T>::display()const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
template<class T>
int Double_linked_list<T>::does_exist(T data2)const {
    Node<T>* temp = head;
    int index=0;
    for (;temp->next!=NULL;) {
        if (temp->data == data2)
            return index;
        temp = temp->next;
        index++;
    }
    return -1;
}
template<typename T>
int Double_linked_list<T>::does_exist(T data2, bool(*predicate)(T, T)) const
{
    Node<T>* temp = head;
    int index = 0;
    for (; temp != NULL;) {
        if (predicate(temp->data, data2))
            return index;
        temp = temp->next;
        index++;
    }
    return -1;
}
template<class T>
T Double_linked_list<T>::operator[](int index) {
    return find_on_index(index);
}
