#include <iostream>
#include "include/matops.h"
#include "include/linearMotion.h"
#include <omp.h>

// just print hello world with cout
int main()
{
    double delta_t = 0.1;
    LinearMotion lm = LinearMotion(
        // motion starts at rest
        new matrix{2, 1, new double[2]{0.0, 0.0}},
        new matrix{2, 2, new double[4]{1.0, delta_t, 0, 1}},
        new matrix{2, 1, new double[2]{0, delta_t}});

    // initialize
    // state covariance matrix
    matrix *stateCOVMat = new matrix{2, 2, new double[4]{0.01, 0.0, 0.0, 0.01}};
    // printf("State covariance matrix:\n");
    // display_matrix(stateCOVMat);
    // process noise covariance matrix
    matrix *processCOVMat = new matrix{2, 2, new double[4]{0.01, 0.0, 0.0, 0.01}};
    // printf("Process noise covariance matrix:\n");
    // display_matrix(processCOVMat);
    // measurement noise covariance matrix
    // matrix *measurementCOVMat = new matrix{2, 2, new double[4]{0.0, 0.05, 0.0, 0.05}};
    matrix *measurementCOVMat = new matrix{1, 1, new double[1]{0.01}};
    // printf("Measurement noise covariance matrix:\n");
    // display_matrix(measurementCOVMat);
    // kalman gain matrix
    matrix *kalmanGainMat = new matrix{2, 1, new double[2]{0.0, 0.0}};
    // printf("Kalman gain matrix:\n");
    // display_matrix(kalmanGainMat);
    // measurement matrix
    matrix *measurementMat = new matrix{1, 2, new double[2]{1.0, 0.0}};
    // printf("Measurement matrix:\n");
    // display_matrix(measurementMat);
    
    // use openmp to get running time
    double start_time = omp_get_wtime();
    // lets generate a sequence of input vectors
    for (int i = 0; i < 10; i++)
    {
        // for constant acceleration
        double accel = 2.0;
        // TODO: do for variable acceleration
        // TODO: add noise to the acceleration

        // prediction step
        matrix *input_vec = new matrix{1, 1, new double[1]{accel}};

        //  prediction step
        //  x = Fx + Bu
        lm.updateState(input_vec);

        //  z = Hx + Du as D = [0]
        // matrix *measurement_vec = mat_mul(measurementMat, state_vec);

        // P = FPF^T + Qinv
        // Q is process noise
        stateCOVMat = mat_mul(lm.getTransitionMatrix(), mat_mul(stateCOVMat, mat_transpose(lm.getTransitionMatrix())));
        stateCOVMat = mat_add(stateCOVMat, processCOVMat);
        // display_matrix(stateCOVMat);

        //  K = PH^T(HPH^T + R)^-1
        //  R is measurement noise
        matrix *temp = mat_mul(mat_mul(measurementMat, stateCOVMat), mat_transpose(measurementMat));
        temp = mat_add(temp, measurementCOVMat);
        kalmanGainMat = mat_mul(mat_mul(stateCOVMat, mat_transpose(measurementMat)), mat_inv(temp));
        // printf("kalman gain matrix:\n");
        // display_matrix(kalmanGainMat);

        //  innovation/error
        //  y_err = z - Hx
        // measurement vector should be supplied from external sensor
        matrix *y_err = mat_sub(new matrix{1, 1, new double[1]{0.0}}, mat_mul(measurementMat, lm.getStateVector()));
        // printf("y_err: %f\n");
        // display_matrix(y_err);


        //  x = x + K*y_err
        // state_vec = mat_add(state_vec, mat_mul(kalmanGainMat, y_err));
        lm.setStateVector(mat_add(lm.getStateVector(), mat_mul(kalmanGainMat, y_err)));
        // printf("State vector after correction: \n");
        // display_matrix(mat_mul(kalmanGainMat, y_err));
        // don't know seems like double is playing a role here


        //  P = (I - KH)P
        stateCOVMat = mat_mul(mat_sub(new matrix{2, 2, new double[4]{1.0, 0.0, 0.0, 1.0}}, mat_mul(kalmanGainMat, measurementMat)), stateCOVMat);
        // printf("State covariance matrix after correction: \n");
        // display_matrix(stateCOVMat);
        // looks good up to this point

        // std::cout << "State vector after " << i << " time steps: [" << lm.getStateVector()->data[0] << ", " << lm.getStateVector()->data[1] << "]" << std::endl;

        free(input_vec->data);
        free(input_vec);
        free(y_err->data);
        free(y_err);

        // if (i==1) {
        //     break;
        // }
    }
    printf("Time in microseconds: %f\n", (omp_get_wtime() - start_time) * 1000000);
    // free the memory allocated for the matrices
    // free(stateCOVMat->data);
    // free(stateCOVMat);
    // free(processCOVMat->data);
    // free(processCOVMat);
    // free(measurementCOVMat->data);
    // free(measurementCOVMat);
    // free(kalmanGainMat->data);
    // free(kalmanGainMat);
    // free(measurementMat->data);
    // free(measurementMat);
    // free(lm.getStateVector()->data);
    return 0;
}