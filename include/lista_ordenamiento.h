#ifndef LISTA_ORDENAMIENTO_H
#define LISTA_ORDENAMIENTO_H

#include <iostream>
#include "MPointer.h"

template <typename T>
class lista_ordenamiento {
public:
    struct Nodo {
        T dato;  // Almacena el valor de tipo T directamente
        MPointer<Nodo> siguiente;
        MPointer<Nodo> anterior;

        // Constructor por defecto
        Nodo() : dato(T()), siguiente(nullptr), anterior(nullptr) {}

        // Constructor con valor
        Nodo(const T& val) : dato(val), siguiente(nullptr), anterior(nullptr) {}
    };

    MPointer<Nodo> cabeza;
    MPointer<Nodo> cola;

public:
    lista_ordenamiento() : cabeza(nullptr), cola(nullptr) {}

    ~lista_ordenamiento() {
        MPointer<Nodo> actual = cabeza;
        while (actual != nullptr) {
            MPointer<Nodo> temp = actual;
            actual = actual->siguiente;
            // No es necesario eliminar manualmente, MPointer se encarga de la memoria
        }
    }

    // Modificación para aceptar un valor de tipo T directamente
    void insertar(const T& valor) {
        MPointer<Nodo> nuevoNodo = MPointer<Nodo>::New(valor);  // Nodo almacena directamente T
        if (cabeza == nullptr) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    // Mostrar la lista
    void mostrar() const {
        MPointer<Nodo> actual = cabeza;
        while (actual != nullptr) {
            std::cout << actual->dato << " ";  // Imprimir el dato de tipo T
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    // Obtener la cabeza de la lista
    MPointer<Nodo> getHead() const { return cabeza; }

    // Obtener la cola de la lista
    MPointer<Nodo> getTail() const { return cola; }
};

#endif // LISTA_ORDENAMIENTO_H
