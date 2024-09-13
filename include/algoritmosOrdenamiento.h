#ifndef ALGORITMOS_ORDENAMIENTO_H
#define ALGORITMOS_ORDENAMIENTO_H

#include "lista_ordenamiento.h"

// Implementación del BubbleSort
template <typename T>
void bubbleSort(lista_ordenamiento<T>& lista) {
    typename lista_ordenamiento<T>::Nodo* actual;
    typename lista_ordenamiento<T>::Nodo* siguiente;
    bool swapped;

    do {
        swapped = false;
        actual = lista.getHead().get();
        while (actual != nullptr && actual->siguiente.get() != nullptr) {
            siguiente = actual->siguiente.get();
            if (actual->dato > siguiente->dato) {
                std::swap(actual->dato, siguiente->dato);
                swapped = true;
            }
            actual = siguiente;
        }
    } while (swapped);
}

// Implementación del QuickSort
template <typename T>
typename lista_ordenamiento<T>::Nodo* partition(typename lista_ordenamiento<T>::Nodo* low, typename lista_ordenamiento<T>::Nodo* high) {
    T pivot = high->dato;
    typename lista_ordenamiento<T>::Nodo* i = low->anterior.get();

    for (typename lista_ordenamiento<T>::Nodo* j = low; j != high; j = j->siguiente.get()) {
        if (j->dato < pivot) {
            i = (i == nullptr) ? low : i->siguiente.get();
            std::swap(i->dato, j->dato);
        }
    }
    i = (i == nullptr) ? low : i->siguiente.get();
    std::swap(i->dato, high->dato);
    return i;
}

template <typename T>
void quickSortRec(typename lista_ordenamiento<T>::Nodo* low, typename lista_ordenamiento<T>::Nodo* high) {
    if (high != nullptr && low != high && low != high->siguiente.get()) {
        typename lista_ordenamiento<T>::Nodo* pi = partition<T>(low, high);
        quickSortRec<T>(low, pi->anterior.get());
        quickSortRec<T>(pi->siguiente.get(), high);
    }
}

template <typename T>
void quickSort(lista_ordenamiento<T>& lista) {
    quickSortRec<T>(lista.getHead().get(), lista.getTail().get());
}

// Implementación del InsertionSort
template <typename T>
void insertionSort(lista_ordenamiento<T>& lista) {
    typename lista_ordenamiento<T>::Nodo* actual = lista.getHead().get()->siguiente.get();

    while (actual != nullptr) {
        T key = actual->dato;
        typename lista_ordenamiento<T>::Nodo* prev = actual->anterior.get();

        while (prev != nullptr && prev->dato > key) {
            prev->siguiente->dato = prev->dato;
            prev = prev->anterior.get();
        }

        if (prev == nullptr) {
            lista.getHead().get()->dato = key;
        } else {
            prev->siguiente->dato = key;
        }

        actual = actual->siguiente.get();
    }
}

#endif // ALGORITMOS_ORDENAMIENTO_H
