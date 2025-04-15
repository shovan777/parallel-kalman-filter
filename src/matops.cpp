#include <stdio.h>
#include <stdlib.h>
#include "include/matops.h"
#include <iostream>
#include <omp.h>
#include <malloc.h>

// Set number of threads globally
// Call this at the beginning of your main() function
// Example:
// int main() {
//     omp_set_num_threads(8);  // Use 8 threads
//     ...
// }

// Macro for aligning memory to cache line boundaries (e.g., 64 bytes)
#define ALIGNMENT 64

// Custom memory allocation for cache alignment
void* aligned_malloc(size_t size) {
    void* ptr;
    if (posix_memalign(&ptr, ALIGNMENT, size) != 0) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return ptr;
}

matrix* mat_mul(matrix* A, matrix* B) {
    int m = A->rows;
    int n = A->cols;
    int p = B->cols;

    if (A->cols != B->rows) {
        printf("Matrix multiplication not possible\n");
        return NULL;
    }

    matrix* C = new matrix;
    C->rows = m;
    C->cols = p;
    C->data = (float*)aligned_malloc(m * p * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            float sum = 0.0f;
            #pragma omp simd reduction(+:sum)
            for (int k = 0; k < n; k++) {
                sum += A->data[i * n + k] * B->data[k * p + j];
            }
            C->data[i * p + j] = sum;
        }
    }

    return C;
}

matrix* mat_add(matrix* A, matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols)
        return NULL;

    int size = A->rows * A->cols;
    matrix* C = new matrix;
    C->rows = A->rows;
    C->cols = A->cols;
    C->data = (float*)aligned_malloc(size * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        C->data[i] = A->data[i] + B->data[i];
    }

    return C;
}

matrix* mat_sub(matrix* A, matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols)
        return NULL;

    int size = A->rows * A->cols;
    matrix* C = new matrix;
    C->rows = A->rows;
    C->cols = A->cols;
    C->data = (float*)aligned_malloc(size * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        C->data[i] = A->data[i] - B->data[i];
    }

    return C;
}

matrix* mat_inv(matrix* A) {
    int n = A->rows;

    if (A->cols != n) {
        printf("Only square matrices can be inverted\n");
        return NULL;
    }

    matrix* identity = new matrix;
    identity->rows = n;
    identity->cols = n;
    identity->data = (float*)aligned_malloc(n * n * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            identity->data[i * n + j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    matrix* A_copy = new matrix;
    A_copy->rows = n;
    A_copy->cols = n;
    A_copy->data = (float*)aligned_malloc(n * n * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < n * n; i++) {
        A_copy->data[i] = A->data[i];
    }

    for (int row = 0; row < n; row++) {
        float pivot = A_copy->data[row * n + row];
        if (pivot == 0.0f) {
            printf("Matrix is not invertible\n");
            free(A_copy->data);
            delete A_copy;
            return NULL;
        }

        for (int col = 0; col < n; col++) {
            A_copy->data[row * n + col] /= pivot;
            identity->data[row * n + col] /= pivot;
        }

        #pragma omp parallel for
        for (int j = 0; j < n; j++) {
            if (j == row) continue;
            float factor = A_copy->data[j * n + row];
            for (int col = 0; col < n; col++) {
                A_copy->data[j * n + col] -= factor * A_copy->data[row * n + col];
                identity->data[j * n + col] -= factor * identity->data[row * n + col];
            }
        }
    }

    free(A_copy->data);
    delete A_copy;
    return identity;
}

matrix* mat_transpose(matrix* A) {
    matrix* B = new matrix;
    B->rows = A->cols;
    B->cols = A->rows;
    B->data = (float*)aligned_malloc(B->rows * B->cols * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            B->data[j * A->rows + i] = A->data[i * A->cols + j];
        }
    }

    return B;
}

void display_matrix(matrix* A) {
    std::cout << "Matrix: " << std::endl;
    std::cout << "Rows: " << A->rows << ", Cols: " << A->cols << std::endl;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            std::cout << A->data[i * A->cols + j] << " ";
        }
        std::cout << std::endl;
    }
}