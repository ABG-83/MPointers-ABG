//
// Created by aldo-bagliano on 13/09/24.
//
#include <gtest/gtest.h>
#include "MPointerList.h"

class MPointerListTest : public ::testing::Test {
protected:
    MPointerList list;

    void SetUp() override {
        // Se ejecuta antes de cada prueba
    }

    void TearDown() override {
        // Se ejecuta después de cada prueba
        list.clear();
    }
};

// Prueba para agregar nodos a la lista
TEST_F(MPointerListTest, AddNode) {
    list.add(1, new int(10));
    MPointerNode* node = list.find(1);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->id, 1);
    EXPECT_EQ(*(static_cast<int*>(node->ptr)), 10);
}

// Prueba para encontrar un nodo
TEST_F(MPointerListTest, FindNode) {
    list.add(1, new int(20));
    MPointerNode* node = list.find(1);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->id, 1);
    EXPECT_EQ(*(static_cast<int*>(node->ptr)), 20);
}

// Prueba para eliminar un nodo
TEST_F(MPointerListTest, RemoveNode) {
    list.add(1, new int(30));
    list.remove(1);
    MPointerNode* node = list.find(1);
    EXPECT_EQ(node, nullptr);
}

// Prueba para limpiar la lista
TEST_F(MPointerListTest, ClearList) {
    list.add(1, new int(40));
    list.add(2, new int(50));
    list.clear();
    EXPECT_EQ(list.getHead(), nullptr);
}

// Prueba para agregar múltiples nodos y verificar su orden
TEST_F(MPointerListTest, AddMultipleNodes) {
    list.add(1, new int(60));
    list.add(2, new int(70));
    list.add(3, new int(80));

    MPointerNode* node1 = list.find(1);
    MPointerNode* node2 = list.find(2);
    MPointerNode* node3 = list.find(3);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    ASSERT_NE(node3, nullptr);

    EXPECT_EQ(node1->id, 1);
    EXPECT_EQ(*(static_cast<int*>(node1->ptr)), 60);

    EXPECT_EQ(node2->id, 2);
    EXPECT_EQ(*(static_cast<int*>(node2->ptr)), 70);

    EXPECT_EQ(node3->id, 3);
    EXPECT_EQ(*(static_cast<int*>(node3->ptr)), 80);
}
