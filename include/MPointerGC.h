//
// Created by aldo-bagliano on 25/08/24.
//

#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <map>
#include <mutex>

class MPointerBase {
public:
    virtual ~MPointerBase() = default;
};

class MPointerGC {
private:
    std::map<int, MPointerBase*> pointers;
    int nextId;
    std::mutex mtx;

    MPointerGC();
    ~MPointerGC();

public:
    static MPointerGC* getInstance();
    int registerPointer(MPointerBase* ptr);
    void deregisterPointer(int id);
    void collectGarbage();
};

#endif //MPOINTERGC_H
