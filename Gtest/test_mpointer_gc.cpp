#include <gtest/gtest.h>
#include "MPointerGC.h"
#include "MPointer.h"

// Ejemplo de una clase simple para probar MPointerGC
class TestClass {
public:
    TestClass() : value(0) {}
    TestClass(int v) : value(v) {}
    int getValue() const { return value; }
    void setValue(int v) { value = v; }

private:
    int value;
};

// Pruebas para MPointerGC
class MPointerGC_Test : public ::testing::Test {
protected:
    void SetUp() override {
        gc = MPointerGC::getInstance();
        gc->startGCThread();
    }

    void TearDown() override {
        gc->stopGCThread();
    }

    MPointerGC* gc;
};

// Prueba de registro y desregistro de punteros
TEST_F(MPointerGC_Test, RegisterAndDeregisterPointer) {
    TestClass* obj = new TestClass(42);
    int id = gc->registerPointer(obj);

    // Asegurarse de que el puntero fue registrado
    ASSERT_NE(gc->getRefCount(id), 0);

    gc->deregisterPointer(id);
    // Asegurarse de que el puntero fue desregistrado
    ASSERT_EQ(gc->getRefCount(id), 0);
}

// Prueba de conteo de referencias
TEST_F(MPointerGC_Test, RefCountManagement) {
    TestClass* obj = new TestClass(42);
    int id = gc->registerPointer(obj);

    // Incrementar el conteo de referencias
    gc->incrementRefCount(id);
    gc->incrementRefCount(id);

    // Verificar el conteo de referencias usando el método getRefCount
    int refCount = gc->getRefCount(id);
    EXPECT_EQ(refCount, 3);

    // Decrementar el conteo de referencias
    gc->deregisterPointer(id);
    gc->deregisterPointer(id);

    // Verificar que el puntero no ha sido eliminado aún (usando getRefCount)
    refCount = gc->getRefCount(id);
    EXPECT_EQ(refCount, 1);

    // Decrementar a 0 y verificar que el recolector de basura lo elimina
    gc->deregisterPointer(id);
    refCount = gc->getRefCount(id);
    EXPECT_EQ(refCount, 0);
}

// Prueba de recolección de basura
TEST_F(MPointerGC_Test, GarbageCollection) {
    TestClass* obj1 = new TestClass(10);
    TestClass* obj2 = new TestClass(20);
    int id1 = gc->registerPointer(obj1);
    int id2 = gc->registerPointer(obj2);

    gc->deregisterPointer(id1);
    gc->deregisterPointer(id2);

    gc->collectGarbage();

    // Comprobar que la memoria ha sido liberada ( verificar el stdout en el caso de mensajes de recolección)

}

// hilo: Prueba para iniciar y detener el hilo del recolector de basura
TEST_F(MPointerGC_Test, GCThreadStartStop) {
    gc->startGCThread();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    gc->stopGCThread();


}
