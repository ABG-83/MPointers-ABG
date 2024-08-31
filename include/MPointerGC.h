#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <map>
#include <mutex>
#include <thread>
#include "MPointerList.h"

class MPointerGC {
public:
    static MPointerGC* getInstance();
    int registerPointer(void* ptr);
    void deregisterPointer(int id);
    void incrementRefCount(int id);
    void collectGarbage();
    void startGCThread();
    void stopGCThread();

private:
    MPointerGC();
    ~MPointerGC();
    void garbageCollectionThread();

    std::map<int, std::pair<void*, int>> pointers; // Cambiar a pair<void*, int> para manejar el conteo de referencias
    MPointerList pointersList;
    int nextId;
    std::mutex mtx;
    std::thread gcThread;
    bool stopFlag;  // Bandera para controlar la ejecución del hilo
    int interval; // Intervalo para la recolección de basura
};

#endif
