cmake_minimum_required(VERSION 3.10)
project(Matrix_Multiplication_OpenMP C)

set(CMAKE_C_STANDARD 99)

# 1. Buscar el paquete
find_package(OpenMP REQUIRED)

# 2. Definir el ejecutable
add_executable(Matrix_Multiplication_OpenMP main.c)

# 3. Vincular OpenMP explícitamente
if(OpenMP_C_FOUND)
    # Vinculación estándar
    target_link_libraries(Matrix_Multiplication_OpenMP PUBLIC OpenMP::OpenMP_C)

    # --- FIX PARA WINDOWS/MINGW ---
    # Forzamos la bandera de compilación y de enlazado
    target_compile_options(Matrix_Multiplication_OpenMP PUBLIC -fopenmp)
    target_link_options(Matrix_Multiplication_OpenMP PUBLIC -fopenmp)
endif()