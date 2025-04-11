// run multiple kalman filters
#include <iostream>
#include <omp.h>
#include "include/matops.h"
#include "include/linearMotion.h"
#include "./src/include/write.h"


int main()
{
    float delta_t = 0.1;
    int SIZE = 10;

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
	
	// initialize the plotting matrix
	float plottingMatrix[8][1000];

    for (int i = 0; i < SIZE; i++)
    {
        lms[i] = new LinearMotion(
            // motion starts at rest
            new matrix{8, 1, new float[8]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}, // state vector
    
            new matrix{8, 8, new float[64]{// transition matrix
                                           1, 0, 0, 0, delta_t, 0, 0, 0,
                                            0, 1, 0, 0, 0, delta_t, 0, 0, 
                                            0, 0, 1, 0, 0, 0, delta_t, 0, 
                                            0, 0, 0, 1, 0, 0, 0, delta_t, 
                                            0, 0, 0, 0, 1, 0, 0, 0, 
                                            0, 0, 0, 0, 0, 1, 0, 0, 
                                            0, 0, 0, 0, 0, 0, 1, 0, 
                                            0, 0, 0, 0, 0, 0, 0, 1}},
    
            new matrix{8, 4, new float[32]{// input matrix
                                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}});

        stateCOVMats[i] = new matrix{8, 8, new float[64]{
            0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1,
        }};

        processCOVMats[i] = new matrix{8, 8, new float[64]{
            0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01,
        }};

        measurementCOVMats[i] = new matrix{4, 4, new float[16]{
            0.01, 0.0, 0.0, 0.0,
            0.0, 0.01, 0.0, 0.0,
            0.0, 0.0, 0.1, 0.0,
            0.0, 0.0, 0.0, 0.1
        }};


        kalmanGainMats[i] = new matrix{8, 4, new float[32]{
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0    
        }};

        measurementMats[i] = new matrix{4, 8, new float[32]{
            1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        }};
		
		plottingMatrix[i] = new matrix{8, 1000, new float[8000]}; 
        
    }

    float accelx = 2.0; // acceleration in x direction
    float accely = 1.0; // acceleration in y direction
    float accela = 0.0; // acceleration in angular direction
    float accelh = 0.0;

    // print hello to that this is multi kalman
    printf("hello ***************************************");

    // run all 10 kalman filters
    double start = omp_get_wtime();
    // #pragma omp parallel for num_threads(10)
    for(int i=0; i<100; i++)
    {
        for(int k=0; k<SIZE; k++) {

            float accel = 2.0;
            // for constant acceleration
            // TODO: do for variable acceleration
            // TODO: add noise to the acceleration

            // prediction step
            matrix *input_vec = new matrix{4, 1, new float[4]{accelx, accely, accela, accelh}};

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
            matrix *y_err = mat_sub(new matrix{4, 1, new float[4]{0.0, 0.0, 0.0, 0.0}}, mat_mul(measurementMats[k], lms[k]->getStateVector()));
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
            stateCOVMats[k] = mat_mul(mat_sub(new matrix{8, 8, new float[64]{
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

            // std::cout << "State vector after " << i << " time steps: [" << lm.getStateVector()->data[0] << ", " << lm.getStateVector()->data[1] << "]" << std::endl;
			
			for (int j = 0; j < 8; j++) {
				plottingMatrix[j][i] = lm.getStateVector()->data[j];
			}

            free(input_vec->data);
            free(input_vec);
        }
    }
    double end = omp_get_wtime();
    printf("Time taken: %f milli seconds\n", (end - start)*1000);
	
	int success = writeDoubles(plottingMatrix);
	
	std::cout << success << "<- Success value of writing data";


    return 0;
}
