//
// Created by aldo-bagliano on 8/09/24.
//
/*
#include "algoritmosOrdenamiento.h"

// Implementación de QuickSort
template <typename T>
void quickSortHelper(lista_ordenamiento<T>& lista, int inicio, int fin);

template <typename T>
int partition(lista_ordenamiento<T>& lista, int inicio, int fin);

template <typename T>
void quickSort(lista_ordenamiento<T>& lista) {
    quickSortHelper(lista, 0, lista.obtenerTamano() - 1);
}

template <typename T>
void quickSortHelper(lista_ordenamiento<T>& lista, int inicio, int fin) {
    if (inicio < fin) {
        int pivotIndex = partition(lista, inicio, fin);
        quickSortHelper(lista, inicio, pivotIndex - 1);
        quickSortHelper(lista, pivotIndex + 1, fin);
    }
}

template <typename T>
int partition(lista_ordenamiento<T>& lista, int inicio, int fin) {
    MPointer<T> pivot = lista.obtener(fin);
    int i = inicio - 1;

    for (int j = inicio; j < fin; ++j) {
        if (*(lista.obtener(j)) <= *pivot) {
            i++;
            std::swap(lista.obtener(i), lista.obtener(j));
        }
    }
    std::swap(lista.obtener(i + 1), lista.obtener(fin));
    return i + 1;
}

// Implementación de BubbleSort
template <typename T>
void bubbleSort(lista_ordenamiento<T>& lista) {
    int n = lista.obtenerTamano();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (*(lista.obtener(j)) > *(lista.obtener(j + 1))) {
                std::swap(lista.obtener(j), lista.obtener(j + 1));
            }
        }
    }
}

// Implementación de InsertionSort
template <typename T>
void insertionSort(lista_ordenamiento<T>& lista) {
    int n = lista.obtenerTamano();
    for (int i = 1; i < n; ++i) {
        MPointer<T> key = lista.obtener(i);
        int j = i - 1;
        while (j >= 0 && *(lista.obtener(j)) > *key) {
            lista.obtener(j + 1) = lista.obtener(j);
            j--;
        }
        lista.obtener(j + 1) = key;
    }
}

// Explicit template instantiation
template void quickSort<int>(lista_ordenamiento<int>& lista);
template void bubbleSort<int>(lista_ordenamiento<int>& lista);
template void insertionSort<int>(lista_ordenamiento<int>& lista);
*/