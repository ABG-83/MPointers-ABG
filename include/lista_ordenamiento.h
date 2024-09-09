// lista_ordenamiento.h
/*
#ifndef LISTA_ORDENAMIENTO_H
#define LISTA_ORDENAMIENTO_H

#include "MPointer.h"
#include <iostream>

// Clase plantilla para lista doblemente enlazada con MPointers
template <typename T>
class lista_ordenamiento {
private:
    // Definir la estructura del nodo
    struct Node {
        MPointer<T> data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;

public:
    lista_ordenamiento() : head(nullptr), tail(nullptr) {}

    void insertar(MPointer<T> value) {
        Node* newNode = new Node{value, nullptr, tail};
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    void mostrar() {
        Node* current = head;
        while (current) {
            std::cout << *(current->data) << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Implementación del algoritmo BubbleSort
    void bubbleSort() {
        if (!head) return;
        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (*(ptr1->data) > *(ptr1->next->data)) {
                    std::swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Implementación del algoritmo QuickSort
    Node* partition(Node* low, Node* high) {
        T pivot = *(high->data);
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if (*(j->data) <= pivot) {
                i = (i == nullptr) ? low : i->next;
                std::swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? low : i->next;
        std::swap(i->data, high->data);
        return i;
    }

    void quickSort(Node* low, Node* high) {
        if (high != nullptr && low != high && low != high->next) {
            Node* p = partition(low, high);
            quickSort(low, p->prev);
            quickSort(p->next, high);
        }
    }

    void quickSort() {
        quickSort(head, tail);
    }

    // Implementación del algoritmo InsertionSort
    void insertionSort() {
        if (!head) return;
        Node* sorted = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;
            if (!sorted || *(sorted->data) >= *(current->data)) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next != nullptr && *(temp->next->data) < *(current->data)) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }
};

#endif // LISTA_ORDENAMIENTO_H
*/

#ifndef LISTA_ORDENAMIENTO_H
#define LISTA_ORDENAMIENTO_H

#include "MPointer.h"
#include <iostream>

// Clase plantilla para lista doblemente enlazada con MPointers
template <typename T>
class lista_ordenamiento {
private:
    // Definir la estructura del nodo
    struct Node {
        MPointer<T> data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;

public:
    lista_ordenamiento() : head(nullptr), tail(nullptr) {}

    // Destructor para liberar nodos al final
    ~lista_ordenamiento() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;  // liberar los MPointers
        }
    }

    // Insertar al final de la lista
    void insertar(MPointer<T> value) {
        Node* newNode = new Node{value, nullptr, tail};
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    // Mostrar la lista
    void mostrar() const {
        Node* current = head;
        while (current) {
            std::cout << *(current->data) << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Implementación de BubbleSort
    void bubbleSort() {
        if (!head) return;
        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (*(ptr1->data) > *(ptr1->next->data)) {
                    std::swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Implementación de QuickSort
    Node* partition(Node* low, Node* high) {
        T pivot = *(high->data);
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if (*(j->data) <= pivot) {
                i = (i == nullptr) ? low : i->next;
                std::swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? low : i->next;
        std::swap(i->data, high->data);
        return i;
    }

    void quickSort(Node* low, Node* high) {
        if (high != nullptr && low != high && low != high->next) {
            Node* p = partition(low, high);
            quickSort(low, p->prev);
            quickSort(p->next, high);
        }
    }

    void quickSort() {
        quickSort(head, tail);
    }

    // Implementación de InsertionSort
    void insertionSort() {
        if (!head) return;

        Node* current = head->next;  // Empezar desde el segundo nodo
        while (current != nullptr) {
            Node* next = current->next;
            Node* sorted = current->prev;

            // Reubicar el nodo actual
            while (sorted != nullptr && *(sorted->data) > *(current->data)) {
                sorted = sorted->prev;
            }

            // Extraer el nodo de su posición actual
            if (current->prev != nullptr)
                current->prev->next = current->next;
            if (current->next != nullptr)
                current->next->prev = current->prev;

            // Reinsertar el nodo en su nueva posición
            if (sorted == nullptr) {
                current->next = head;
                head->prev = current;
                head = current;
            } else {
                current->next = sorted->next;
                current->prev = sorted;
                if (sorted->next != nullptr)
                    sorted->next->prev = current;
                sorted->next = current;
            }

            current = next;  // Continuar con el siguiente nodo
        }
    }
};

#endif // LISTA_ORDENAMIENTO_H
