#include "linearMotion.h"
#include <iostream>

// Constructor: assigns parameter pointers to member variables.
LinearMotion::LinearMotion(matrix *state_vec, matrix *transition_matrix, matrix *input_matrix) {
    this->state_vec = state_vec;
    this->transition_matrix = transition_matrix;
    this->input_matrix = input_matrix;
}

// Set a new transition matrix.
void LinearMotion::setTransitionMatrix(matrix *transition_matrix) {
    this->transition_matrix = transition_matrix;
}

// Get the current transition matrix.
matrix *LinearMotion::getTransitionMatrix() {
    return transition_matrix;
}

// Update the state using the input vector.
void LinearMotion::updateState(matrix *input_vec) {
    if (transition_matrix && state_vec) {
        matrix *new_state = mat_mult(transition_matrix, state_vec); // Assuming mat_mult performs matrix multiplication
        matrix *input_effect = mat_mult(input_matrix, input_vec);
        
        if (new_state && input_effect) {
            matrix *updated_state = mat_add(new_state, input_effect); // Assuming mat_add performs matrix addition
            setStateVector(updated_state);
        }
    }
}

// Set the state vector
void LinearMotion::setStateVector(matrix *state_vec) {
    this->state_vec = state_vec;
}

// Destructor: free the memory allocated for the matrices.
LinearMotion::~LinearMotion() {
    // Assuming `matrix` class has a proper destructor to free allocated memory
    delete state_vec;
    delete transition_matrix;
    delete input_matrix;
}