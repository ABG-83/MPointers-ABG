#include "MPointer.h"
#include <iostream>
/*
int main() {
    // Iniciar el recolector de basura
    MPointerGC::getInstance()->startGCThread();

    // Crear un MPointer para un entero
    MPointer<int> myPointer = MPointer<int>::New();

    // Asignar un valor al MPointer
    *myPointer = 42;

    // Mostrar el valor almacenado en el MPointer
    std::cout << "El valor almacenado en myPointer es: " << *myPointer << std::endl;

    // Probar asignación directa
    myPointer = 100;
    std::cout << "Nuevo valor en myPointer es: " << *myPointer << std::endl;

    // probar eliminando mypointer
    //myPointer = nullptr;

    // Crear un segundo MPointer
    MPointer<int> anotherPointer = MPointer<int>::New();
    *anotherPointer = 123;

    std::cout << "El valor almacenado en anotherPointer es: " << *anotherPointer << std::endl;

    // Crear muchos objetos de corta duración
    for (int i = 0; i < 100; ++i) {
        MPointer<int> temp = MPointer<int>::New();
        *temp = i; // Asignar un valor solo para asegurarnos de que se asigne memoria
    }

    // Esperar un tiempo para que el GC tenga oportunidad de ejecutarse
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Detener el recolector de basura
    MPointerGC::getInstance()->stopGCThread();

    return 0;
}
*/
#include "MPointer.h"
/*
int main() {
    {
        MPointer<int> ptr1 = MPointer<int>::New();
        *ptr1 = 10;
        std::cout << "Valor en ptr1: " << *ptr1 << std::endl;

        MPointer<int> ptr2 = ptr1; // ptr2 y ptr1 apuntan al mismo lugar
    } // Aquí, ambos ptr1 y ptr2 deberían ser eliminados por el GC

    // Esperar un poco para permitir que el GC realice su trabajo
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    return 0;
}
*/

#include <iostream>
#include "MPointer.h"

int main() {
    // Caso 1: Crear un MPointer y asignar un valor
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10;
    std::cout << "Valor en ptr1: " << *ptr1 << std::endl;

    // Caso 2: Crear otro MPointer y copiar el valor de ptr1
    MPointer<int> ptr2 = ptr1;
    std::cout << "Valor en ptr2 (después de copiar ptr1): " << *ptr2 << std::endl;

    // Caso 3: Modificar el valor de ptr2 y ver que ptr1 también cambia
    *ptr2 = 20;
    std::cout << "Valor en ptr1 (después de modificar ptr2): " << *ptr1 << std::endl;
    std::cout << "Valor en ptr2: " << *ptr2 << std::endl;

    // Caso 4: Crear un nuevo MPointer y asignar un nuevo valor
    MPointer<int> ptr3 = MPointer<int>::New();
    *ptr3 = 30;
    std::cout << "Valor en ptr3: " << *ptr3 << std::endl;

    // Caso 5: Asignar ptr3 a ptr1 y verificar el cambio
    ptr1 = ptr3;
    std::cout << "Valor en ptr1 (después de asignar ptr3): " << *ptr1 << std::endl;
    std::cout << "Valor en ptr3: " << *ptr3 << std::endl;

    // Caso 6: Crear un MPointer para un tipo diferente (double)
    MPointer<double> ptr4 = MPointer<double>::New();
    *ptr4 = 50.5;
    std::cout << "Valor en ptr4: " << *ptr4 << std::endl;

    // Caso 7: Crear un MPointer para un tipo de datos complejo (struct)
    struct MyStruct {
        int a;
        double b;
    };

    MPointer<MyStruct> ptr5 = MPointer<MyStruct>::New();
    ptr5->a = 5;
    ptr5->b = 10.5;
    std::cout << "Valor en ptr5->a: " << ptr5->a << std::endl;
    std::cout << "Valor en ptr5->b: " << ptr5->b << std::endl;

    // Caso 8: Comprobar que el GC elimina los punteros no referenciados
    {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = 100;
        std::cout << "Valor en tempPtr: " << *tempPtr << std::endl;
    } // tempPtr se sale del scope aquí

    std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Espera para que el GC recoja el puntero

    return 0;
}

