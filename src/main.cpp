// run multiple kalman filters
#include <iostream>
#include <omp.h>
#include "include/matops.h"
#include "include/linearMotion.h"
#include <cmath>
#include <random>
#include "include/write.h"

int main()
{
    double delta_t = 0.001;
    int SIZE = 1; // the number of objects
    
    // intialize an array of 10 linear motion objects
    LinearMotion *lms[SIZE];
    // initialize the 10 state covariance matrices
    matrix *stateCOVMats[SIZE];

    // initialize the 10 process noise covariance matrices
    matrix *processCOVMats[SIZE];

    // initialize the 10 measurement noise covariance matrices
    matrix *measurementCOVMats[SIZE];

    // initialize the 10 kalman gain matrices
    matrix *kalmanGainMats[SIZE];

    matrix *measurementMats[SIZE];

    // initialize the writing matrix
	double writingMatrix[SIZE][1000][8];

    for (int i = 0; i < SIZE; i++)
    {
        // we are randomizing height between 50 and 150 pixels which is kinda common
        double height = rand() % (150 - 50 + 1) + 50;
        // double height = height;
        lms[i] = new LinearMotion(
            // motion starts at rest
            new matrix{8, 1, new double[8]{0.0, 0.0, 0.0, height, 0.0, 0.0, 0.0, 0.0}}, // state vector
    
            new matrix{8, 8, new double[64]{// transition matrix
                                           1, 0.0, 0, 0, delta_t, 0, 0, 0,
                                            0, 1, 0, 0, 0, delta_t, 0, 0, 
                                            0, 0, 1, 0, 0, 0, delta_t, 0, 
                                            0, 0, 0, 1, 0, 0, 0, delta_t, 
                                            0, 0, 0, 0, 1, 0, 0, 0, 
                                            0, 0, 0, 0, 0, 1, 0, 0, 
                                            0, 0, 0, 0, 0, 0, 1, 0, 
                                            0, 0, 0, 0, 0, 0, 0, 1}},
    
            new matrix{8, 4, new double[32]{// input matrix
                                           0, 0, 0, 0, 
                                           0, 0, 0, 0, 
                                           0, 0, 0, 0, 
                                           0, 0, 0, 0, 
                                           1, 0, 0, 0, 
                                           0, 1, 0, 0, 
                                           0, 0, 1, 0, 
                                           0, 0, 0, 1}});


        double large_unc = pow((2.0*(1.0/20.0)*height),2); // (0.05h)^2
        double small_unc = pow((10.0*(1.0/160.0)*height),2); //(0.00625h)^2
        double large_e_unc = pow(exp(1.0) ,-4); //(e^-2)^2
        double small_e_unc = pow(exp(1.0) ,-10); //(e^-5)^2
        // double large_unc = 1; // (0.05h)^2
        // double small_unc = 1; //(0.00625h)^2
        // double large_e_unc = 1; //(e^-2)^2
        // double small_e_unc = 1; //(e^-5)^2
        // printf("***************%Lf %Lf %Lf %Lf %Lf", height, large_unc, small_unc, large_e_unc, small_e_unc);

        


        stateCOVMats[i] = new matrix{8, 8, new double[64]{
            large_unc, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, large_unc, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, large_e_unc, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, large_unc, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, small_unc, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, small_unc, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, small_e_unc, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, small_unc
        }};

        processCOVMats[i] = new matrix{8, 8, new double[64]{
            large_unc, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, large_unc, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, large_e_unc, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, large_unc, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, small_unc, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, small_unc, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, small_e_unc, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, small_unc
        }};

        measurementCOVMats[i] = new matrix{4, 4, new double[16]{
            large_unc, 0.0, 0.0, 0.0,
            0.0, large_unc, 0.0, 0.0,
            0.0, 0.0, large_e_unc, 0.0,
            0.0, 0.0, 0.0, large_unc
        }};


        kalmanGainMats[i] = new matrix{8, 4, new double[32]{
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0    
        }};

        measurementMats[i] = new matrix{4, 8, new double[32]{
            1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0
        }};
        
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> accel_dist(0, 5.0);

    
    // print hello to that this is multi kalman
    // printf("hello: ");
    
    // run all 10 kalman filters
    double start = omp_get_wtime();
    
    // #pragma omp parallel for num_threads(16) schedule(dynamic)
    for(int i=0; i<100; i++)
    {
        #pragma omp parallel for num_threads(4) schedule(static)
        for(int k=0; k<SIZE; k++) {
            // we have now randomized accelerations in x and y direction between -3 and 3 m/s which is pretty common
            // additionally we randomized angular acceleration which is very small 
            // we are also saying height acceleration isnt there cuz we say camera is 
            // fixed and height of predestrians does not change
            double accelx = accel_dist(gen); // acceleration in x direction
            double accely = accel_dist(gen); // acceleration in y direction
            //double accela = ((double)rand() / RAND_MAX) * 0.2 - 0.1; // acceleration in angular direction
            double accela = 1 * 0.2 - 0.1; // acceleration in angular direction
            double accelh = 0.0;

            // for constant acceleration
            // TODO: do for variable acceleration
            // TODO: add noise to the acceleration

            // prediction step
            matrix *input_vec = new matrix{4, 1, new double[4]{accelx, accely, accela, accelh}};

            //  prediction step
            //  x = Fx + Bu
            lms[k]->updateState(input_vec);

            //  z = Hx + Du as D = [0]
            // matrix *measurement_vec = mat_mul(measurementMat, state_vec);

            // P = FPF^T + Q
            // Q is process noise
            stateCOVMats[k] = mat_mul(lms[k]->getTransitionMatrix(), mat_mul(stateCOVMats[k], mat_transpose(lms[k]->getTransitionMatrix())));
            stateCOVMats[k] = mat_add(stateCOVMats[k], processCOVMats[k]);
            // display_matrix(stateCOVMat);

            //  K = PH^T(HPH^T + R)^-1
            //  R is measurement noise
            matrix *temp = mat_mul(mat_mul(measurementMats[k], stateCOVMats[k]), mat_transpose(measurementMats[k]));        
            temp = mat_add(temp, measurementCOVMats[k]);
            kalmanGainMats[k] = mat_mul(mat_mul(stateCOVMats[k], mat_transpose(measurementMats[k])), mat_inv(temp));
            // printf("kalman gain matrix:\n");
            // display_matrix(kalmanGainMat);

            //  innovation/error
            //  y_err = z - Hx
            // measurement vector should be supplied from external sensor
            matrix *y_err = mat_sub(new matrix{4, 1, new double[4]{0.0, 0.0, 0.0, 0.0}}, mat_mul(measurementMats[k], lms[k]->getStateVector()));
            // printf("y_err: %f\n");
            // display_matrix(y_err);

            //  x = x + K*y_err
            // state_vec = mat_add(state_vec, mat_mul(kalmanGainMat, y_err));
            lms[k]->setStateVector(mat_add(lms[k]->getStateVector(), mat_mul(kalmanGainMats[k], y_err)));
            // printf("State vector after correction: \n");
            // display_matrix(mat_mul(kalmanGainMat, y_err));
            // don't know seems like double is playing a role here
            // display_matrix(lm.getStateVector());

            //  P = (I - KH)P
            stateCOVMats[k] = mat_mul(mat_sub(new matrix{8, 8, new double[64]{
                1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
            }}, mat_mul(kalmanGainMats[k], measurementMats[k])), stateCOVMats[k]);
            // printf("State covariance matrix after correction: \n");
            // display_matrix(stateCOVMat);
            // looks good up to this point

            //std::cout << "State vector after " << i << " time steps: [" << lm.getStateVector()->data[0] << ", " << lm.getStateVector()->data[1] << "]" << std::endl;

            for (int j = 0; j < 8; j++) {
				writingMatrix[k][i][j] = lms[k]->getStateVector()->data[j];
			}

            free(input_vec->data);
            free(input_vec);
        }
    }
    double end = omp_get_wtime();
    //printf("Time taken: %f ms\n", (end - start)*1000);
    printf("Time taken: %.2f ms\n", (end - start) * 1000);

    int success = writeDoubles(writingMatrix, SIZE);
	
	std::cout << success << "<- Success value of writing data";


    return 0;
}