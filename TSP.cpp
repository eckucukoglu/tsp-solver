#include "TSP.h"

Tsp::Tsp (unsigned int design_technique, unsigned int** distances, 
        unsigned int number_of_cities) {
    this->design_technique = design_technique;
    this->distances = distances;
    this->number_of_cities = number_of_cities;
}

unsigned int* Tsp::solve() {
    unsigned int* result = NULL;
    
    if (this->design_technique == BACKTRACKING)
        result = solve_with_backtrack();
    else if (this->design_technique == BRANCH_AND_BOUND)
        result = solve_with_branch_and_bound();
        
    return result;
}

void Tsp::print_solution(unsigned int* solution) {
    // TODO
    
    print_pretty_matrix("Distances", this->distances, this->number_of_cities);
    
    unsigned int path_size = 2;
    unsigned int* current_path = new unsigned int[path_size];
    current_path[0] = 0;
    current_path[1] = 1;
    
    matrix_reduction(this->distances, this->number_of_cities,
                    current_path, path_size);
}

Tsp::~Tsp () {
    for (unsigned int i = 0; i < this->number_of_cities; ++i) {
        delete[] this->distances[i];
        this->distances[i] = 0;
    }

    delete[] this->distances;
    this->distances = 0;
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
    unsigned int path_distance = 0;
    unsigned int result = 0;
    
    if (path_length > 1) {
        for (unsigned int i = 1; i < path_length; ++i) {
            unsigned int from = current_path[i-1];
            unsigned int to = current_path[i];
            
            path_distance += matrix[from][to];
        }
    
        for (unsigned int i = 1; i < path_length; ++i) {
            unsigned int former_node = current_path[i-1];
            unsigned int current_node = current_path[i];
            /* Remove column. */
            for (unsigned int j = 0; j < dimension; ++j) {
                matrix[j][current_node] = UINT_MAX;
            }
            matrix[current_node][0] = UINT_MAX;
            /* Remove row. */
            for (unsigned int j = 0; j < dimension; ++j) {
                matrix[former_node][j] = UINT_MAX;
            }
        }
    }

    result = calculate_bound(matrix, dimension);

#ifdef DEBUG
    cout << "Bound result: " << result << endl;
    cout << "Path distance: " << path_distance << endl;
#endif /* DEBUG */
    
    result += path_distance;
    return result;
}

unsigned int Tsp::calculate_bound(unsigned int **matrix, unsigned int dimension) {
    unsigned int local_min = UINT_MAX;
    unsigned int result = 0;
    
    for (unsigned int i = 0; i < dimension; ++i) {
        local_min = matrix[i][0];
        for (unsigned int j = 0; j < dimension; ++j) {
            if (local_min > matrix[i][j]) {
                local_min = matrix[i][j];
            }
        }
        
        for (unsigned int j = 0; j < dimension; ++j) {
            if (matrix[i][j] < UINT_MAX) {
                matrix[i][j] -= local_min; 
            }
        }
        
        if (local_min != UINT_MAX)
            result += local_min;
    }

#ifdef DEBUG
    cout << "Bound intermediate result: " << result << endl;
    print_pretty_matrix("After row/before column reduction", matrix, dimension);
#endif /* DEBUG */
    
    for (unsigned int j = 0; j < dimension; ++j) {
        local_min = matrix[0][j];
        for (unsigned int i = 0; i < dimension; ++i) {
            if (local_min > matrix[i][j]) {
                local_min = matrix[i][j];
            }
        }
        
        for (unsigned int i = 0; i < dimension; ++i) {
            if (matrix[i][j] < UINT_MAX) {
                matrix[i][j] -= local_min;
            }
        }
        
        if (local_min != UINT_MAX)
            result += local_min;
    }
    
    return result;
}

void Tsp::print_pretty_matrix(char const* desc, unsigned int **matrix, 
                              unsigned int dimension) {
    cout << desc << " (" << dimension << "x" << dimension << "):" << endl;
    
    for (unsigned int i = 0; i < dimension; ++i) {
        for (unsigned int j = 0; j < dimension; ++j) {
            if (matrix[i][j] == UINT_MAX) {
                cout << "-" << "\t";
                continue;
            }
            
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}
