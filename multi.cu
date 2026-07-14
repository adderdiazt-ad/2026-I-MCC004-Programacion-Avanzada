#include <iostream>
#include <cuda_runtime.h>
#include "types.h"

// El Kernel: Cada hilo calcula un elemento específico (fila, columna) de la matriz C
__global__ void matrizMulKernel(const T3F* A, const T3F* B, T3F* C, TI N) {
    // Calcular la fila y la columna global correspondientes a este hilo
    TI fila = blockIdx.y * blockDim.y + threadIdx.y;
    TI col = blockIdx.x * blockDim.x + threadIdx.x;

    // Verificar que el hilo no intente acceder a memoria fuera de los límites de la matriz
    if (fila < N && col < N) {
        T3F suma = 0.0f;
        // Producto punto entre la fila de A y la columna de B
        for (TI k = 0; k < N; ++k) {
            suma += A[fila * N + k] * B[k * N + col];
        }
        // Guardar el resultado en la posición linealizada de la matriz C
        C[fila * N + col] = suma;
    }
}

int main() {
    // Definir una dimensión grande (Ej: 2048 x 2048)
    const TI N = 2048; 
    size_t tamanoMatriz = N * N * sizeof(T3F);

    // --- 1. Asignar e inicializar memoria en el Host (CPU) ---
    T3F* h_A = new T3F[N * N];
    T3F* h_B = new T3F[N * N];
    T3F* h_C = new T3F[N * N];

    // Llenar matrices con valores constantes para validar el cálculo fácilmente
    for (TI i = 0; i < N * N; ++i) {
        h_A[i] = 1.5f; // Matriz A llena de 1.5
        h_B[i] = 2.0f; // Matriz B llena de 2.0
    }

    // --- 2. Asignar memoria en el Device (GPU) ---
    T3F *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, tamanoMatriz);
    cudaMalloc(&d_B, tamanoMatriz);
    cudaMalloc(&d_C, tamanoMatriz);

    // --- 3. Copiar datos del Host al Device ---
    cudaMemcpy(d_A, h_A, tamanoMatriz, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, tamanoMatriz, cudaMemcpyHostToDevice);

    // --- 4. Configurar la topología bidimensional de bloques e hilos ---
    // Definimos bloques de 16x16 hilos (256 hilos en total por bloque)
    dim3 hilosPorBloque(16, 16);
    
    // Calculamos los bloques necesarios en cada eje para cubrir toda la matriz N x N
    dim3 bloquesPorGrid((N + hilosPorBloque.x - 1) / hilosPorBloque.x,
                        (N + hilosPorBloque.y - 1) / hilosPorBloque.y);

    std::cout << "Lanzando kernel con un Grid de [" << bloquesPorGrid.x << "x" << bloquesPorGrid.y 
              << "] bloques..." << std::endl;

    // --- 5. Lanzar el Kernel en la GPU ---
    matrizMulKernel<<<bloquesPorGrid, hilosPorBloque>>>(d_A, d_B, d_C, N);
    
    // Forzar sincronización para medir o asegurar que la GPU ha terminado
    cudaDeviceSynchronize();

    // --- 6. Copiar los resultados de regreso al Host ---
    cudaMemcpy(h_C, d_C, tamanoMatriz, cudaMemcpyDeviceToHost);

    // --- 7. Validación matemática del resultado ---
    // Para matrices llenas de 1.5 y 2.0, cada celda de C debe valer: 1.5 * 2.0 * N = 3.0 * N
    T3F valorEsperado = 3.0f * N;
    std::cout << "Resultado en C[0]: " << h_C[0] << " (Esperado: " << valorEsperado << ")" << std::endl;
    std::cout << "Resultado en la esquina opuesta: " << h_C[(N*N)-1] << " (Esperado: " << valorEsperado << ")" << std::endl;

    // --- 8. Liberar toda la memoria asignada ---
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;

    return 0;
}