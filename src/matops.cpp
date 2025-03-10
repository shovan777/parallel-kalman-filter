#include <stdio.h>
#include <stdlib.h>
#include "include/matops.h"

// lets define some matrix operations
// return just the pointer to the matrix
matrix* mat_mul(matrix* A, matrix* B) {
    matrix* C = new matrix;
    int m = A->rows;
    int n = A->cols;
    int p = B->cols;
    C->rows = m;
    C->cols = p;
    C->data = (float *)malloc(C->rows * C->cols * sizeof(float));
    // for (int i = 0; i < C->rows; i++) {
    //     for (int j = 0; j < C->cols; j++) {
    //         C->data[i * C->cols + j] = 0;
    //         for (int k = 0; k < A->cols; k++) {
    //             C->data[i * C->cols + j] += A->data[i * A->cols + k] * B->data[k * B->cols + j];
    //         }
    //     }
    // }
    
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<p; j++)
        {
            // printf("for element at i=%d, j=%d***********\n", i, j);
            int c_idx = i * p + j;
            C->data[c_idx] = 0.0;
            for (int k=0; k<n; k++)
            {
                C->data[c_idx] += (A->data[i * n + k] * B->data[k * p + j]);
            }
            // printf("value of c[%d][%d]=%d\n", i, j, c[c_idx]);
        }
    }
    return C;
}

matrix* mat_add(matrix* A, matrix* B) {
    matrix* C = new matrix;
    int m = A->rows;
    int n = A->cols;
    C->rows = m;
    C->cols = n;
    C->data = (float *)malloc(C->rows * C->cols * sizeof(float));
    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->cols; j++) {
            C->data[i * C->cols + j] = A->data[i * A->cols + j] + B->data[i * B->cols + j];
        }
    }
    return C;
}