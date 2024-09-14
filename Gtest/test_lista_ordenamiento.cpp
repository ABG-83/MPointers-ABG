#include "gtest/gtest.h"
#include "lista_ordenamiento.h"

// Prueba de insertar elementos en la lista
TEST(ListaOrdenamientoTest, InsertaElemento) {
    lista_ordenamiento<int> lista;

    lista.insertar(5);
    ASSERT_EQ(lista.getHead()->dato, 5);
    ASSERT_EQ(lista.getTail()->dato, 5);

    lista.insertar(10);
    ASSERT_EQ(lista.getTail()->dato, 10);
    ASSERT_EQ(lista.getHead()->siguiente->dato, 10);
}

// Prueba de una lista vacía
TEST(ListaOrdenamientoTest, ListaVacia) {
    lista_ordenamiento<int> lista;

    // Asegurarse de que la lista esté vacía
    ASSERT_EQ(lista.getHead(), nullptr);
    ASSERT_EQ(lista.getTail(), nullptr);
}

// Prueba de una lista con un solo elemento
TEST(ListaOrdenamientoTest, ListaUnElemento) {
    lista_ordenamiento<int> lista;

    lista.insertar(10);

    // Asegurarse de que el único elemento no cambie
    ASSERT_EQ(lista.getHead()->dato, 10);
    ASSERT_EQ(lista.getTail()->dato, 10);
}
