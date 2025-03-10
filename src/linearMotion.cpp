// create a class that will handle the linear motion of the robot
#include "include/linearMotion.h"
#include <iostream>
#include <cmath>

// Implementation of LinearMotion class methods

LinearMotion::LinearMotion(matrix *state_vec, matrix *transition_matrix, matrix *input_matrix)
{
    this->state_vec = state_vec;
    this->transition_matrix = transition_matrix;
    this->input_matrix = input_matrix;
}

void LinearMotion::setTransitionMatrix(matrix *transition_matrix)
{
    this->transition_matrix = transition_matrix;
}

matrix *LinearMotion::updateState(matrix *input_vec)
{
    // update the state vector
    state_vec = mat_mul(this->transition_matrix, state_vec);
    matrix *temp = mat_mul(this->input_matrix, input_vec);
    state_vec = mat_add(temp, state_vec);
    free(temp->data);
    return state_vec;
}

// Destructor
LinearMotion::~LinearMotion()
{
    free(state_vec->data);
    free(transition_matrix->data);
    free(input_matrix->data);
}