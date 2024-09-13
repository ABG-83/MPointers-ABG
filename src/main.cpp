#include <iostream>
#include <random>
#include "lista_ordenamiento.h"
#include "algoritmosOrdenamiento.h"

int main() {
    // Iniciar el recolector de basura
    MPointerGC::getInstance()->startGCThread();

    lista_ordenamiento<int> lista;

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 100);

    // Insertar elementos aleatorios en la lista
    for (int i = 0; i < 50; ++i) { // Inserta 50 elementos aleatorios
        int random_value = distr(gen);
        lista.insertar(random_value);  // Ahora solo insertamos el valor directamente
    }

    std::cout << "Lista antes de ordenar: ";
    lista.mostrar();

    // Ordenar usando bubbleSort
    bubbleSort(lista);

    std::cout << "Lista después de bubbleSort: ";
    lista.mostrar();

    // Ordenar usando quickSort
    quickSort(lista);

    std::cout << "Lista después de quickSort: ";
    lista.mostrar();

    // Ordenar usando insertionSort
    insertionSort(lista);

    std::cout << "Lista después de insertionSort: ";
    lista.mostrar();

    // Detener el recolector de basura
    MPointerGC::getInstance()->stopGCThread();

    return 0;
}
