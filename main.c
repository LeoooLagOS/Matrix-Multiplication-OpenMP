#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void multiply_matrices(int m1, int n1, int n2, int *A, int *B, int *C) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            int sum = 0;
            for (int k = 0; k < n1; k++) {
                sum += A[i * n1 + k] * B[k * n2 + j];
            }
            C[i * n2 + j] = sum;
        }
    }
}

void print_matrix(int rows, int cols, int *M, FILE **f) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("[%d]", M[i * cols + j]);
            if(*f) fprintf(*f,"[%d]", M[i*cols +j]);
        }
        printf("\n");
        if(*f) fprintf(*f, "\n");
    }
}

int main() {
    int hilos, m1, n1, m2, n2;
    srand(time(NULL));

    printf("--- Multiplicacion de Matrices Paralela (OpenMP) ---\n");
    
    // 1. Configuración de Hilos
    int disponibles = omp_get_num_procs();
    printf("Nucleos detectados: %d\n", disponibles);
    printf("Dame el numero de hilos a usar: ");
    // fflush para asegurar que el print salga antes del input en algunas consolas
    fflush(stdout); 
    if (scanf("%d", &hilos) != 1) return 1;

    if (hilos > disponibles) {
        printf("Advertencia: %d hilos supera tus %d nucleos. Se usaran %d.\n", hilos, disponibles, disponibles);
        hilos = disponibles;
    }
    omp_set_num_threads(hilos);

    // 2. Dimensiones
    printf("Filas Matriz A: "); scanf("%d", &m1);
    printf("Cols  Matriz A: "); scanf("%d", &n1);
    printf("Filas Matriz B: "); scanf("%d", &m2);
    printf("Cols  Matriz B: "); scanf("%d", &n2);

    if (n1 != m2) {
        printf("Error: Cols de A (%d) deben ser igual a Filas de B (%d).\n", n1, m2);
        return 1;
    }

    // 3. Reserva de Memoria
    int *A = malloc(sizeof(int) * m1 * n1);
    int *B = malloc(sizeof(int) * m2 * n2);
    int *C = malloc(sizeof(int) * m1 * n2);

    // 4. Archivo de salida
    FILE *f = fopen("resultado.txt", "w");

    // 5. Generar Datos
    printf("\nGenerando matriz A...\n");
    for (int i = 0; i < m1 * n1; i++) A[i] = rand() % 10 + 1;
    
    printf("Generando matriz B...\n");
    for (int i = 0; i < m2 * n2; i++) B[i] = rand() % 10 + 1;

    // 6. Ejecución y Medición
    printf("\nCalculando...\n");
    double start = omp_get_wtime();
    multiply_matrices(m1, n1, n2, A, B, C);
    double end = omp_get_wtime();

    // 7. Resultados
    printf("\n--- Resultado (Parcial) ---\n");
    if (m1 < 10 && n2 < 10) {
        print_matrix(m1, n2, C, &f);
    } else {
        printf("(Matriz muy grande para mostrar en consola)\n");
        if(f) {
            fprintf(f, "Matriz Resultado:\n");
            for(int i=0; i<m1; i++) {
                for(int j=0; j<n2; j++) fprintf(f, "[%d]", C[i*n2+j]);
                fprintf(f, "\n");
            }
        }
    }
    
    printf("\n>>> Tiempo de ejecucion: %f segundos <<<\n", end - start);
    printf("Resultados guardados en 'resultado.txt'\n");

    if(f) fclose(f);
    free(A); free(B); free(C);
    return 0;
}
