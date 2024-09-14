//
// Created by aldo-bagliano on 13/09/24.
//
#include "gtest/gtest.h"
#include "lista_ordenamiento.h"
#include "algoritmosOrdenamiento.h"

// Prueba del algoritmo BubbleSort
TEST(AlgoritmosOrdenamientoTest, BubbleSortOrdenaCorrectamente) {
    lista_ordenamiento<int> lista;

    lista.insertar(3);
    lista.insertar(1);
    lista.insertar(2);

    bubbleSort(lista);

    ASSERT_EQ(lista.getHead()->dato, 1);
    ASSERT_EQ(lista.getHead()->siguiente->dato, 2);
    ASSERT_EQ(lista.getTail()->dato, 3);
}

// Prueba del algoritmo QuickSort
TEST(AlgoritmosOrdenamientoTest, QuickSortOrdenaCorrectamente) {
    lista_ordenamiento<int> lista;

    lista.insertar(9);
    lista.insertar(4);
    lista.insertar(7);

    quickSort(lista);

    ASSERT_EQ(lista.getHead()->dato, 4);
    ASSERT_EQ(lista.getHead()->siguiente->dato, 7);
    ASSERT_EQ(lista.getTail()->dato, 9);
}

// Prueba del algoritmo InsertionSort
TEST(AlgoritmosOrdenamientoTest, InsertionSortOrdenaCorrectamente) {
    lista_ordenamiento<int> lista;

    lista.insertar(12);
    lista.insertar(3);
    lista.insertar(5);

    insertionSort(lista);

    ASSERT_EQ(lista.getHead()->dato, 3);
    ASSERT_EQ(lista.getHead()->siguiente->dato, 5);
    ASSERT_EQ(lista.getTail()->dato, 12);
}
