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
            //se elimina en hace en collectGarbage para evitar double free
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




void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    MPointerNode* current = pointersList.getHead();
    while (current != nullptr) {
        if (current->refCount == 0) {
            MPointerNode* toDelete = current;
            current = current->next;
            // Solo elimina el nodo, no el puntero
            delete static_cast<char*>(toDelete->ptr);
            pointersList.remove(toDelete->id);
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
    while (!stopFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        collectGarbage();
    }
}
