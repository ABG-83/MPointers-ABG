//
// Created by aldo-bagliano on 13/09/24.
//
#include <gtest/gtest.h>
#include "MPointer.h"
#include "MPointerGC.h" //  incluir el archivo del recolector de basura

// Ejemplo de una clase simple para probar MPointer
class TestClass {
public:
    TestClass() : value(0) {}
    TestClass(int v) : value(v) {}
    int getValue() const { return value; }
    void setValue(int v) { value = v; }

private:
    int value;
};

// Pruebas para MPointer
class MPointerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // se puede inicializar cualquier cosa aquí antes de cada prueba
    }

    void TearDown() override {
        //  limpiar cualquier cosa aquí después de cada prueba
    }
};

// Prueba de constructor por defecto
TEST_F(MPointerTest, DefaultConstructor) {
    MPointer<TestClass> mp;
    ASSERT_NE(mp.get(), nullptr);
    EXPECT_EQ(mp->getValue(), 0); // Valor por defecto del TestClass
}

// Prueba de constructor con valor
TEST_F(MPointerTest, ConstructorWithValue) {
    MPointer<TestClass> mp(42);
    ASSERT_NE(mp.get(), nullptr);
    EXPECT_EQ(mp->getValue(), 42); // Valor inicializado
}

// Prueba de constructor de copia
TEST_F(MPointerTest, CopyConstructor) {
    MPointer<TestClass> mp1(42);
    MPointer<TestClass> mp2 = mp1; // Usando el constructor de copia
    ASSERT_NE(mp2.get(), nullptr);
    EXPECT_EQ(mp2->getValue(), 42);
}

// Prueba de operador de asignación
TEST_F(MPointerTest, AssignmentOperator) {
    MPointer<TestClass> mp1(42);
    MPointer<TestClass> mp2;
    mp2 = mp1; // Usando el operador de asignación
    ASSERT_NE(mp2.get(), nullptr);
    EXPECT_EQ(mp2->getValue(), 42);
}

// Prueba de comparación con nullptr
TEST_F(MPointerTest, ComparisonWithNullptr) {
    MPointer<TestClass> mp1; // Constructor por defecto, ptr no debería ser nullptr
    MPointer<TestClass> mp2(42); // Constructor con valor, ptr no debería ser nullptr

    // Verificar que mp1 no es nullptr (debería ser falso)
    EXPECT_FALSE(mp1 == nullptr);

    // Verificar que mp2 no es nullptr (debería ser falso)
    EXPECT_FALSE(mp2 == nullptr);

    // Verificar la comparación inversa
    EXPECT_TRUE(mp1 != nullptr); // mp1 no debería ser nullptr
    EXPECT_TRUE(mp2 != nullptr); // mp2 no debería ser nullptr
}


// Prueba de creación estática
TEST_F(MPointerTest, StaticCreate) {
    MPointer<TestClass> mp = MPointer<TestClass>::New(42);
    ASSERT_NE(mp.get(), nullptr);
    EXPECT_EQ(mp->getValue(), 42);
}

