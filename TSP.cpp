#include "TSP.h"

Tsp::Tsp (unsigned int design_technique, unsigned int** distances, 
        unsigned int number_of_cities) {
    this->design_technique = design_technique;
    this->distances = distances;
    this->number_of_cities = number_of_cities;
}

unsigned int* Tsp::solve() {
    unsigned int *result = NULL;
    
    if (this->design_technique == BACKTRACKING)
        result = solve_with_backtrack();
    else if (this->design_technique == BRANCH_AND_BOUND)
        result = solve_with_branch_and_bound();
        
    return result;
}

void Tsp::print_solution(unsigned int * solution) {
    // TODO
}

Tsp::~Tsp () {
    // TODO
}

unsigned int* Tsp::solve_with_backtrack() {
    // TODO
    
    return NULL;
}
    
unsigned int* Tsp::solve_with_branch_and_bound() {
    // TODO
    
    return NULL;
}

unsigned int Tsp::matrix_reduction(unsigned int **matrix, 
                                   unsigned int dimension, 
                                   unsigned int *current_path, 
                                   unsigned int path_length) {
    // TODO
    
    return 0;                              
}








