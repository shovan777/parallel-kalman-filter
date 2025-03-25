#include <iostream>
#include "include/matops.h"
#include "include/linearMotion.h"
#include "include/plotter.h"
#include "include/write.h"

// just print hello world with cout
int main()
{
    std::cout << "Hello, World! Test couting!" << std::endl;
    float delta_t = 0.1;
    LinearMotion lm = LinearMotion(
        // motion starts at rest
        new matrix{2, 1, new float[2]{0.0, 0.0}},
        new matrix{2, 2, new float[4]{1.0, delta_t, 0, 1}},
        new matrix{2, 1, new float[2]{0, delta_t}});
    // lets generate a sequence of input vectors
    for (int i = 0; i < 10; i++)
    {   
        // for constant acceleration
        float accel = 2.0;
        // TODO: do for variable acceleration
        // TODO: add noise to the acceleration
        matrix *input_vec = new matrix{1, 1, new float[1]{accel}};
        matrix *state_vec = lm.updateState(input_vec);
        std::cout << "State vector after " << i << " time steps: [" << state_vec->data[0] << ", " << state_vec->data[1] << "]" << std::endl;
        free(input_vec->data);
        free(input_vec);
    }
    double data[20] = {1,2.5,3,4,5,6.5,7,8,9,10,11,12,13,14,15,16,17,18,19};

    //plotter();

    int success = writeDoubles(data);

    std::cout << success;
    
    return 0;
}