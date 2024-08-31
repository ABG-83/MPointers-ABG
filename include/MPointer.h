#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
public:
    MPointer() : ptr(new T()), id(MPointerGC::getInstance()->registerPointer(ptr)) {}

    ~MPointer() {
        if (ptr != nullptr) {
            MPointerGC::getInstance()->deregisterPointer(id);
            ptr = nullptr;
        }
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

    MPointer& operator=(const T& value) {
        *ptr = value;
        return *this;
    }

    MPointer& operator=(const MPointer<T>& other) {
        if (this != &other) {
            MPointerGC::getInstance()->deregisterPointer(id);
            ptr = other.ptr;
            id = other.id;
            MPointerGC::getInstance()->incrementRefCount(id);
        }
        return *this;
    }

    static MPointer New() { return MPointer(); }

private:
    T* ptr;
    int id;
};

#endif
