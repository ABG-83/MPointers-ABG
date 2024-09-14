cmake_minimum_required(VERSION 3.29)
project(MPointers_ABG)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

# Buscar e incluir GTest
find_package(GTest REQUIRED)
include(GoogleTest)

# Ejecutable principal
add_executable(MPointers_ABG
        include/MPointer.h
        include/MPointerGC.h
        src/main.cpp
        src/MPointerGC.cpp
        include/MPointerList.h
        include/lista_ordenamiento.h
        include/algoritmosOrdenamiento.h
)

# Ejecutable de pruebas para la lista
add_executable(test_lista
        Gtest/test_lista_ordenamiento.cpp
        src/MPointerGC.cpp
        include/MPointerList.h
        include/lista_ordenamiento.h
)

# Ejecutable de pruebas para los algoritmos
add_executable(test_algoritmos
        Gtest/test_algoritmos_ordenamiento.cpp
        src/MPointerGC.cpp
        include/algoritmosOrdenamiento.h
)

# Ejecutable de pruebas para MPointer
add_executable(test_mpointer
        Gtest/test_mpointer.cpp
        src/MPointerGC.cpp
        include/MPointer.h
        include/MPointerGC.h
)

# Ejecutable de pruebas para MPointerGC
add_executable(test_mpointer_gc
        Gtest/test_mpointer_gc.cpp
        src/MPointerGC.cpp
        include/MPointer.h
        include/MPointerGC.h
        include/MPointerList.h
)

# Ejecutable de pruebas para MPointerList
add_executable(test_mpointer_list
        Gtest/test_mpointer_list.cpp
        include/MPointerList.h
)

# Enlazar las librerías de GTest con las pruebas
target_link_libraries(test_lista GTest::GTest GTest::Main)
target_link_libraries(test_algoritmos GTest::GTest GTest::Main)
target_link_libraries(test_mpointer GTest::GTest GTest::Main)
target_link_libraries(test_mpointer_gc GTest::GTest GTest::Main)
target_link_libraries(test_mpointer_list GTest::GTest GTest::Main)

# Activar las pruebas
enable_testing()

# Descubrir pruebas
gtest_discover_tests(test_lista)
gtest_discover_tests(test_algoritmos)
gtest_discover_tests(test_mpointer)
gtest_discover_tests(test_mpointer_gc)
gtest_discover_tests(test_mpointer_list)
