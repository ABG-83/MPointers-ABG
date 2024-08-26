//
// Created by aldo-bagliano on 25/08/24.
//
#include "MPointerGC.h"

MPointerGC* MPointerGC::getInstance() {
    static MPointerGC instance;
    return &instance;
}

MPointerGC::MPointerGC() : nextId(0) {}

MPointerGC::~MPointerGC() {
    collectGarbage();
}

int MPointerGC::registerPointer(MPointerBase* ptr) {
    std::lock_guard<std::mutex> lock(mtx);
    int id = nextId++;
    pointers[id] = ptr;
    return id;
}

void MPointerGC::deregisterPointer(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    pointers.erase(id);
}

void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& pair : pointers) {
        delete pair.second;
    }
    pointers.clear();
}
