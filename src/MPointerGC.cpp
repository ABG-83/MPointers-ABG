#include "MPointerGC.h"

#include <iostream>
#include <ostream>

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
    pointers[id] = std::make_pair(ptr, 1);
    return id;
}

void MPointerGC::deregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (pointers.count(id) > 0 && pointers[id].second > 0) {
        if (--pointers[id].second == 0)
        {
            delete static_cast<char*>(pointers[id].first);  // se usa char* para asegurar el delete
            std::cout <<"Puntero " << id << " eliminado por el GC" << std::endl;
            pointers.erase(id);
        }else {
            std::cout << "Puntero " << id << " tiene ahora " << pointers[id].second << " referencias" << std::endl;

        }
    }
}

void MPointerGC::incrementRefCount(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (pointers.count(id) > 0) {
        pointers[id].second++;
    }
}

void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = pointers.begin(); it != pointers.end(); ) {
        if (it->second.second == 0) {
            delete static_cast<char*>(it->second.first);  // se usa char* para asegurar el delete
            std::cout <<"puntero " << it->second.first << " recolectado por GC" << std::endl;
            it = pointers.erase(it);
        } else {
            ++it;
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
