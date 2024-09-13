#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
public:
    // Constructor por defecto
    MPointer() : ptr(new T()), id(MPointerGC::getInstance()->registerPointer(ptr)) {}

    // Constructor con valor
    explicit MPointer(const T& value) : ptr(new T(value)), id(MPointerGC::getInstance()->registerPointer(ptr)) {}

    // Constructor de copia
    MPointer(const MPointer<T>& other) : ptr(other.ptr), id(other.id) {
        MPointerGC::getInstance()->incrementRefCount(id);
    }

    // Constructor para nullptr
    MPointer(std::nullptr_t) : ptr(nullptr), id(-1) {}

    // Destructor
    ~MPointer() {
        // Solo se libera la memoria si es el último puntero que hace referencia a ella
        if (ptr != nullptr) {
            MPointerGC::getInstance()->deregisterPointer(id);
            // No se elimina ptr aquí, el recolector de basura se encargará de ello
            ptr = nullptr;
        }
    }

    // Operadores de acceso
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Operadores de asignación
    MPointer& operator=(const T& value) {
        if (ptr != nullptr) {
            *ptr = value;
        }
        return *this;
    }

    MPointer& operator=(const MPointer<T>& other) {
        if (this != &other) {
            // Primero, desregistrar y liberar el puntero actual si es el último
            if (ptr != nullptr) {
                MPointerGC::getInstance()->deregisterPointer(id);
                // No eliminar ptr aquí, el recolector de basura se encarga
            }

            // Copiar los datos del otro MPointer
            ptr = other.ptr;
            id = other.id;
            MPointerGC::getInstance()->incrementRefCount(id);
        }
        return *this;
    }

    // Operadores de comparación
    bool operator==(std::nullptr_t) const { return ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return ptr != nullptr; }
    bool operator==(const MPointer<T>& other) const { return ptr == other.ptr; }
    bool operator!=(const MPointer<T>& other) const { return ptr != other.ptr; }

    // Métodos estáticos para crear un nuevo MPointer
    static MPointer New(const T& value) {
        return MPointer(value);
    }

    static MPointer New() {
        return MPointer(); // Usa el constructor predeterminado
    }

private:
    T* ptr;
    int id;
};

#endif // MPOINTER_H
