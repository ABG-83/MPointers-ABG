//
// Created by aldo-bagliano on 25/08/24.
//

#ifndef MPOINTER_H
#define MPOINTER_H
#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* ptr;                // Puntero encapsulado
    int id;                // Identificador único para el GC
    static MPointerGC* gc; // Referencia al garbage collector

public:
    // Constructor y Destructor
    MPointer();
    ~MPointer();

    // Sobrecarga de operadores
    T& operator*();   // Dereference operator
    T* operator&();   // Address operator
    MPointer<T>& operator=(const T& value); // Assignment operator

    // Método estático para crear nuevos MPointers
    static MPointer<T> New();
};

//#include "MPointer.cpp" // Incluye la implementación template

#endif //MPOINTER_H
