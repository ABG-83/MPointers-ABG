#include <iostream>
#include <vector>
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::random_device y std::mt19937
#include "MPointer.h"
#include "lista_ordenamiento.h"

int main() {
    lista_ordenamiento<int> lista;

    // Crear una lista de valores del 0 al 9
    std::vector<int> valores;
    for (int i = 0; i < 10; ++i) {
        valores.push_back(i);
    }

    // hacer los valores aleatorios
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(valores.begin(), valores.end(), g);

    // Insertar valores en la lista usando MPointer
    for (int valor : valores) {
        MPointer<int> mp = MPointer<int>::New(); // Crear un nuevo MPointer<int>
        *mp = valor;  // Asignar el valor a cada MPointer
        std::cout << "Insertando MPointer con valor: " << *mp << " en dirección: " << mp.get() << std::endl;
        lista.insertar(mp); // Insertar en la lista
    }

    std::cout << "Lista original (desordenada):" << std::endl;
    lista.mostrar(); // Mostrar la lista desordenada

    // Probar el algoritmo BubbleSort
    lista.bubbleSort();
    std::cout << "Lista después de BubbleSort:" << std::endl;
    lista.mostrar();

    // Probar el algoritmo QuickSort
    lista.quickSort();
    std::cout << "Lista después de QuickSort:" << std::endl;
    lista.mostrar();

    // Probar el algoritmo InsertionSort
    lista.insertionSort();
    std::cout << "Lista después de InsertionSort:" << std::endl;
    lista.mostrar();

    std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Espera para que el GC recoja el puntero

    return 0;
}
