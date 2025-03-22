#ifndef MATOPS_H
#define MATOPS_H

// lets define some matrix data structures
struct matrix
{
    int rows;
    int cols;
    float *data;
};

matrix *mat_mul(matrix *A, matrix *B);
matrix *mat_add(matrix *A, matrix *B);
matrix *mat_inv(matrix *A);
#endif // MATOPS_H