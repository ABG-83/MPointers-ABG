//
// Created by aldo-bagliano on 25/08/24.
//
#include "MPointer.h"

// Inicializa el garbage collector
template <typename T>
MPointerGC* MPointer<T>::gc = MPointerGC::getInstance();

template <typename T>
MPointer<T>::MPointer() {
    ptr = new T();  // Reserva memoria para T
    id = gc->registerPointer(this); // Registra el puntero en el GC
}

template <typename T>
MPointer<T>::~MPointer() {
    gc->deregisterPointer(id); // Indica al GC que la referencia se ha destruido
    delete ptr;  // Libera la memoria
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;
    return *this;
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();
}
