#include <iostream>
#include <cassert>
#include "include/matops.h"

void test_mat_mul() {
    // Test case 1: 2x2 matrices
    matrix A;
    A.rows = 2;
    A.cols = 2;
    double dataA[] = {1, 2, 3, 4};
    A.data = dataA;

    matrix B;
    B.rows = 2;
    B.cols = 2;
    double dataB[] = {5, 6, 7, 8};
    B.data = dataB;

    matrix* C = mat_mul(&A, &B);

    assert(C->rows == 2);
    assert(C->cols == 2);
    assert(C->data[0] == 19);
    assert(C->data[1] == 22);
    assert(C->data[2] == 43);
    assert(C->data[3] == 50);

    free(C->data);

    // Test case 2: 3x3 matrices
    A.rows = 3;
    A.cols = 3;
    double dataA2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    A.data = dataA2;

    B.rows = 3;
    B.cols = 3;
    double dataB2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    B.data = dataB2;

    C = mat_mul(&A, &B);

    assert(C->rows == 3);
    assert(C->cols == 3);
    assert(C->data[0] == 30);
    assert(C->data[1] == 24);
    assert(C->data[2] == 18);
    assert(C->data[3] == 84);
    assert(C->data[4] == 69);
    assert(C->data[5] == 54);
    assert(C->data[6] == 138);
    assert(C->data[7] == 114);
    assert(C->data[8] == 90);
    free(C->data);
}

void test_mat_add() {
    // Test case 1: 2x2 matrices
    matrix A;
    A.rows = 2;
    A.cols = 2;
    double dataA[] = {1, 2, 3, 4};
    A.data = dataA;

    matrix B;
    B.rows = 2;
    B.cols = 2;
    double dataB[] = {5, 6, 7, 8};
    B.data = dataB;

    matrix* C = mat_add(&A, &B);

    assert(C->rows == 2);
    assert(C->cols == 2);
    assert(C->data[0] == 6);
    assert(C->data[1] == 8);
    assert(C->data[2] == 10);
    assert(C->data[3] == 12);

    free(C->data);

    // Test case 2: 3x3 matrices
    A.rows = 3;
    A.cols = 3;
    double dataA2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    A.data = dataA2;

    B.rows = 3;
    B.cols = 3;
    double dataB2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    B.data = dataB2;

    C = mat_add(&A, &B);

    assert(C->rows == 3);
    assert(C->cols == 3);
    assert(C->data[0] == 10);
    assert(C->data[1] == 10);
    assert(C->data[2] == 10);
    assert(C->data[3] == 10);
    assert(C->data[4] == 10);
    assert(C->data[5] == 10);
    assert(C->data[6] == 10);
    assert(C->data[7] == 10);
    assert(C->data[8] == 10);
    free(C->data);
}

void test_mat_inv() {
    // Test case 1: 2x2 matrix
    matrix A;
    A.rows = 2;
    A.cols = 2;
    double dataA[] = {4, 7, 2, 6};
    A.data = dataA;

    matrix* C = mat_inv(&A);

    assert(C->rows == 2);
    assert(C->cols == 2);
    assert(C->data[0] == 0.6f);
    assert(C->data[1] == -0.7f);
    assert(C->data[2] == -0.2f);
    assert(C->data[3] == 0.4f);

    free(C->data);

    // Test case 2: 3x3 matrix
    A.rows = 3;
    A.cols = 3;
    double dataA2[] = {1, 2, 3, 0, 1, 4, 5, 6, 0};
    A.data = dataA2;

    C = mat_inv(&A);

    assert(C->rows == 3);
    assert(C->cols == 3);
    assert(C->data[0] == -24);
    assert(C->data[1] == 18);
    assert(C->data[2] == 5);
    assert(C->data[3] == 20);
    assert(C->data[4] == -15);
    assert(C->data[5] == -4);
    assert(C->data[6] == -5);
    assert(C->data[7] == 4);
    assert(C->data[8] == 1);
    free(C->data);
}

int main() {
    test_mat_mul();
    std::cout << "mat_mul tests passed!" << std::endl;
    test_mat_add();
    std::cout << "mat_add tests passed!" << std::endl;
    test_mat_inv();
    std::cout << "mat_inv tests passed!" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}


