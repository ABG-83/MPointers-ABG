//
// Created by aldo-bagliano on 25/08/24.
//
#include "MPointer.h"
#include <iostream>

int main() {
    // Crear un MPointer para un entero
    MPointer<int> myPointer = MPointer<int>::New();

    // Asignar un valor al MPointer
    *myPointer = 42;

    // Mostrar el valor almacenado en el MPointer
    std::cout << "El valor almacenado en myPointer es: " << *myPointer << std::endl;

    // Probar asignación directa
    myPointer = 100;
    std::cout << "Nuevo valor en myPointer es: " << *myPointer << std::endl;

    // Crear un segundo MPointer
    MPointer<int> anotherPointer = MPointer<int>::New();
    *anotherPointer = 123;

    std::cout << "El valor almacenado en anotherPointer es: " << *anotherPointer << std::endl;

    // Probar la recolección de basura
    MPointerGC::getInstance()->collectGarbage();

    return 0;
}
