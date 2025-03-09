// lets define some matrix data structures
struct matrix {
    int rows;
    int cols;
    float *data;
};

matrix* mat_mul(matrix* A, matrix* B);
