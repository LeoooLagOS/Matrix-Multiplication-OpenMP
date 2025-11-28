# 🧮 Parallel Matrix Multiplication (OpenMP)

![C](https://img.shields.io/badge/Language-C99-blue?style=for-the-badge&logo=c)
![OpenMP](https://img.shields.io/badge/Concurrency-OpenMP-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-purple?style=for-the-badge)

This project implements a highly efficient matrix multiplication algorithm ($C = A \times B$) using the **OpenMP** API for shared-memory parallelism. It demonstrates the **Fork-Join** execution model and applies loop collapsing techniques to maximize CPU core utilization.

---

## 🧠 Theoretical Background

### Parallel Strategy
The algorithm transforms the classic $O(N^3)$ sequential multiplication into a parallel operation by distributing the calculation of the result matrix $C$ across multiple threads.

* **Model:** **Fork-Join**. The master thread creates a team of threads (Fork) to execute the loops in parallel and synchronizes them (Join) at the end.
* **Bernstein's Conditions:** The loop iterations satisfy Bernstein's conditions for parallel execution:
    1.  **Write Independence:** Each iteration computes a unique cell $C[i][j]$. No two threads write to the same memory location simultaneously.
    2.  **Read Independence:** Threads read shared data ($A$ and $B$) but do not modify it.

### Key Optimization
We use the OpenMP directive:
```c
#pragma omp parallel for collapse(2)
```

This "flattens" the nested loops (rows of $A$ and columns of $B$) into a single iteration space, allowing for better load balancing when the number of threads doesn't perfectly divide the number of rows.

## 📂 Project Structure

```Plaintext
Matrix-Multiplication-OpenMP/
├── .idea/               # CLion configuration (Ignored in Git)
├── cmake-build-debug/   # Build artifacts (Ignored in Git)
├── CMakeLists.txt       # Build configuration (Critical for linking OpenMP)
├── main.c               # Source code
├── resultado.txt        # Output file (generated at runtime)
└── README.md            # Documentation
```

## 🛠️ Prerequisites
* **Compiler:** GCC (MinGW for Windows) or Clang with OpenMP support.
* **IDE (Optional):** CLion 2024.x (Recommended).
* **System:** Multi-core processor recommended for performance testing.
## 🚀 Compilation & Execution
**Option A: Using CLion (Recommended)**
This project includes a `CMakeLists.txt` configured to handle the specific linker flags required for OpenMP on Windows/MinGW.
1. Open the project folder in CLion.
2. Let CMake load.
3. Click the Run (▶️) button.
4. Follow the prompts in the internal console.

**Option B: Using Terminal (GCC)**
If you prefer the command line, you must explicitly link the OpenMP library.
```Bash
# Compile
gcc -fopenmp main.c -o matrix_mult

# Run
./matrix_mult
```
## 📊 Usage Example
Upon running, the program will ask for configuration:
```Plaintext
--- Multiplicacion de Matrices Paralela (OpenMP) ---
Nucleos detectados: 12
Dame el numero de hilos a usar: 8
Filas Matriz A: 1000
Cols  Matriz A: 1000
Filas Matriz B: 1000
Cols  Matriz B: 1000

Calculando...

--- Resultado (Parcial) ---
(Matriz muy grande para mostrar en consola)

>>> Tiempo de ejecucion: 0.842300 segundos <<<
Resultados guardados en 'resultado.txt'
```
## ⚠️ Troubleshooting
**Error:** undefined reference to 'omp_get_num_procs'
* **Cause:** The linker didn't receive the OpenMP flag.
* **Fix:** Ensure your `CMakeLists.txt` contains:
```CMake
target_compile_options(Matrix_Multiplication_OpenMP PUBLIC -fopenmp)
target_link_options(Matrix_Multiplication_OpenMP PUBLIC -fopenmp)
```
