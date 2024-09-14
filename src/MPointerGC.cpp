#include <iostream>
#include "MPointerGC.h"

MPointerGC* MPointerGC::getInstance() {
    static MPointerGC instance;
    return &instance;
}

MPointerGC::MPointerGC() : nextId(0), stopFlag(false), interval(1000) {}

MPointerGC::~MPointerGC() {
    stopGCThread();
}

int MPointerGC::registerPointer(void* ptr) {
    std::lock_guard<std::mutex> lock(mtx);
    int id = nextId++;
    pointersList.add(id, ptr);
    return id;
}

void MPointerGC::deregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    MPointerNode* node = pointersList.find(id);
    if (node) {
        if (--node->refCount == 0) {
            pointersList.remove(id); // Primero, elimina el nodo de la lista
            //se elimina en hace en collectGarbage para evitar el double free
        }
    }
}

void MPointerGC::incrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    MPointerNode* node = pointersList.find(id);
    if (node) {
        node->refCount++;
    }
}

int MPointerGC::getRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    MPointerNode* node = pointersList.find(id);
    if (node) {
        return node->refCount;
    }
    return 0;
}

void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    MPointerNode* current = pointersList.getHead();
    while (current != nullptr) {
        if (current->refCount == 0) {
            MPointerNode* toDelete = current;
            current = current->next;
            // Elimina el puntero, el tipo es conocido solo en el contexto de MPointer
            delete static_cast<char*>(toDelete->ptr);
            pointersList.remove(toDelete->id); // Elimina el nodo de la lista
            delete toDelete; // Elimina el nodo
            std::cout << "Puntero " << toDelete->id << " recolectado por el GC" << std::endl;
        } else {
            current = current->next;
        }
    }
}

void MPointerGC::startGCThread() {
    stopFlag = false;
    gcThread = std::thread(&MPointerGC::garbageCollectionThread, this);
}

void MPointerGC::stopGCThread() {
    stopFlag = true;
    if (gcThread.joinable()) {
        gcThread.join();
    }
}



void MPointerGC::garbageCollectionThread() {
    std::cout << "Hilo de GC iniciado." << std::endl;
    try {
        while (!stopFlag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));

            if (stopFlag) {
                std::cout << "Deteniendo hilo de GC." << std::endl;
                break;
            }

            std::cout << "Recolectando basura..." << std::endl;
            collectGarbage();
        }
    } catch (const std::exception& e) {
        std::cerr << "Excepción en el hilo de GC: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida en el hilo de GC" << std::endl;
    }
    std::cout << "Hilo de GC finalizado." << std::endl;
}


