#include <iostream>
#include <cuda_runtime.h>
#include <iomanip>
#include "types.h"

#define BLOCK_SIZE 16

// ============================================================================
// KERNEL 1: Naive (Acceso directo a Memoria Global)
// ============================================================================
__global__ void matrizMulKernelNaive(const T3F* A, const T3F* B, T3F* C, TI N) {
    TI fila = blockIdx.y * blockDim.y + threadIdx.y;
    TI col = blockIdx.x * blockDim.x + threadIdx.x;

    if (fila < N && col < N) {
        T3F suma = 0.0f;
        for (TI k = 0; k < N; ++k) {
            suma += A[fila * N + k] * B[k * N + col];
        }
        C[fila * N + col] = suma;
    }
}

// ============================================================================
// KERNEL 2: Tiled (Uso de Memoria Compartida / Shared Memory)
// ============================================================================
__global__ void matrizMulKernelTiled(const T3F* A, const T3F* B, T3F* C, TI N) {
    // Memoria compartida asignada dinámicamente por bloque de hilos
    __shared__ T3F ds_A[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ T3F ds_B[BLOCK_SIZE][BLOCK_SIZE];

    TI tx = threadIdx.x;
    TI ty = threadIdx.y;
    TI fila = blockIdx.y * BLOCK_SIZE + ty;
    TI col = blockIdx.x * BLOCK_SIZE + tx;

    T3F suma = 0.0f;

    // Iteramos por fases (pasos de bloque) a lo largo de las matrices A y B
    for (TI m = 0; m < (N + BLOCK_SIZE - 1) / BLOCK_SIZE; ++m) {
        
        // Cargar elemento de A en Shared Memory con protección de bordes
        if (fila < N && (m * BLOCK_SIZE + tx) < N) 
            ds_A[ty][tx] = A[fila * N + m * BLOCK_SIZE + tx];
        else 
            ds_A[ty][tx] = 0.0f;

        // Cargar elemento de B en Shared Memory con protección de bordes
        if (col < N && (m * BLOCK_SIZE + ty) < N) 
            ds_B[ty][tx] = B[(m * BLOCK_SIZE + ty) * N + col];
        else 
            ds_B[ty][tx] = 0.0f;
    

        // Esperar a que todo el bloque termine la fase de carga
        __syncthreads();

        // Multiplicar los elementos del sub-bloque actual
        for (TI k = 0; k < BLOCK_SIZE; ++k) {
            suma += ds_A[ty][k] * ds_B[k][tx];
        }

        // Esperar a que todos los hilos terminen de leer antes de sobrescribir en el sgte ciclo
        __syncthreads();
    }

    // Guardar el resultado final en la memoria global de la GPU
    if (fila < N && col < N) {
        C[fila * N + col] = suma;
    }
}

int main() {
    const TI N = 4096; // Modifica este tamaño para ver cómo escala el rendimiento
    size_t tamanoMatriz = N * N * sizeof(T3F);

    std::cout << "=== BENCHMARK DE MULTIPLICACIÓN DE MATRICES EN CUDA ===" << std::endl;
    std::cout << "Matriz de dimensiones: " << N << " x " << N << std::endl;
    std::cout << "Memoria requerida por matriz: " << (T3F)tamanoMatriz / (1024 * 1024) << " MB" << std::endl;

    // 1. Asignar memoria en el Host (CPU)
    T3F* h_A = new T3F[N * N];
    T3F* h_B = new T3F[N * N];
    T3F* h_C = new T3F[N * N];

    // Inicializar matrices
    for (TI i = 0; i < N * N; ++i) {
        h_A[i] = 1.5f;
        h_B[i] = 2.0f;
    }

    // 2. Asignar memoria en el Device (GPU)
    T3F *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, tamanoMatriz);
    cudaMalloc(&d_B, tamanoMatriz);
    cudaMalloc(&d_C, tamanoMatriz);

    // Copiar datos de entrada al Device
    cudaMemcpy(d_A, h_A, tamanoMatriz, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, tamanoMatriz, cudaMemcpyHostToDevice);

    // 3. Configuración del Grid y Bloques (Grid 2D de bloques de 16x16 hilos)
    dim3 hilosPorBloque(BLOCK_SIZE, BLOCK_SIZE);
    dim3 bloquesPorGrid((N + hilosPorBloque.x - 1) / hilosPorBloque.x,
                        (N + hilosPorBloque.y - 1) / hilosPorBloque.y);

    // Crear eventos para la toma de tiempos en la GPU
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // ============================================================================
    // PRUEBA 1: KERNEL NAIVE
    // ============================================================================
    cudaMemset(d_C, 0, tamanoMatriz); // Asegurar que iniciamos con C en ceros
    
    cudaEventRecord(start);
    matrizMulKernelNaive<<<bloquesPorGrid, hilosPorBloque>>>(d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    
    cudaEventSynchronize(stop);
    T3F tiempoNaive = 0;
    cudaEventElapsedTime(&tiempoNaive, start, stop);

    // Validar y guardar resultado
    cudaMemcpy(h_C, d_C, tamanoMatriz, cudaMemcpyDeviceToHost);
    T3F valorEsperado = 3.0f * N;
    bool naiveCorrecto = (h_C[0] == valorEsperado && h_C[(N*N)-1] == valorEsperado);

    // ============================================================================
    // PRUEBA 2: KERNEL TILED (CON MEMORIA COMPARTIDA)
    // ============================================================================
    cudaMemset(d_C, 0, tamanoMatriz); // Limpiar memoria de salida de GPU de nuevo
    
    cudaEventRecord(start);
    matrizMulKernelTiled<<<bloquesPorGrid, hilosPorBloque>>>(d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    
    cudaEventSynchronize(stop);
    T3F tiempoTiled = 0;
    cudaEventElapsedTime(&tiempoTiled, start, stop);

    // Validar y guardar resultado
    cudaMemcpy(h_C, d_C, tamanoMatriz, cudaMemcpyDeviceToHost);
    bool tiledCorrecto = (h_C[0] == valorEsperado && h_C[(N*N)-1] == valorEsperado);

    // ============================================================================
    // RESULTADOS
    // ============================================================================
    std::cout << "\n==================== REPORTES ====================" << std::endl;
    std::cout << "1. Kernel Naive: " << std::fixed << std::setprecision(4) << tiempoNaive << " ms "
              << (naiveCorrecto ? "[CORRECTO]" : "[ERROR DE CÁLCULO]") << std::endl;
    std::cout << "2. Kernel Tiled: " << std::fixed << std::setprecision(4) << tiempoTiled << " ms "
              << (tiledCorrecto ? "[CORRECTO]" : "[ERROR DE CÁLCULO]") << std::endl;
    
    if (naiveCorrecto && tiledCorrecto) {
        T3F speedup = tiempoNaive / tiempoTiled;
        std::cout << "\n>>> ¡La version Tiled es " << std::setprecision(2) << speedup 
                  << " veces mas rapida que la Naive! <<<" << std::endl;
    }

    // Limpieza
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    delete[] h_A; delete[] h_B; delete[] h_C;

    return 0;
}