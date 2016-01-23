#include "TSP.h"

Tsp::Tsp (unsigned int design_technique, unsigned int** distances,
        unsigned int number_of_cities) {
    this->design_technique = design_technique;
    this->distances = distances;
    this->number_of_cities = number_of_cities;
    this->optimal_cost = UINT_MAX;
}

void Tsp::solve() {
    unsigned int level = 1;
    unsigned int* optimal_path = new unsigned int[this->number_of_cities]();
    unsigned int* current_path = new unsigned int[this->number_of_cities]();

    if (this->design_technique == BACKTRACKING)
        solve_with_backtrack(level, optimal_path, current_path);
    else if (this->design_technique == BRANCH_AND_BOUND)
        solve_with_branch_and_bound(level, optimal_path, current_path);


    delete[] current_path;
    this->solution = optimal_path;
}

void Tsp::print_solution() {

    cout << this->optimal_cost << endl;

    for (unsigned int i = 0; i < this->number_of_cities; ++i) {
        unsigned int from = this->solution[i];
        unsigned int to;

        if (i == (this->number_of_cities - 1))
            to = this->solution[0];
        else
            to = this->solution[i + 1];

        cout << from + 1 << " " << to + 1 << " " << this->distances[from][to];
        cout << endl;
    }

}

Tsp::~Tsp () {
    for (unsigned int i = 0; i < this->number_of_cities; ++i) {
        delete[] this->distances[i];
        this->distances[i] = 0;
    }

    delete[] this->distances;
    this->distances = 0;

    delete[] this->solution;
    this->solution = 0;
}

void Tsp::solve_with_backtrack(unsigned int level,
                               unsigned int* optimal_path,
                               unsigned int* _current_path) {

    unsigned int* current_path = new unsigned int[this->number_of_cities]();
    for (unsigned int i = 0; i < this->number_of_cities; ++i) {
        current_path[i] = _current_path[i];
    }

    if (level == this->number_of_cities) {
        unsigned int cost_of_current_path = 0;
        // Calculate cost of current path
        for (unsigned int i = 0; i < this->number_of_cities; ++i) {
            if (i != 0 && current_path[i] == 0)
                break;

            unsigned int from = current_path[i];
            unsigned int to;
            if (i == (this->number_of_cities - 1))
                to = current_path[0];
            else
                to = current_path[i+1];

            cost_of_current_path += this->distances[from][to];
        }

        if (cost_of_current_path < this->optimal_cost) {
            this->optimal_cost = cost_of_current_path;

            for (unsigned int i = 0; i < this->number_of_cities; ++i) {
                optimal_path[i] = current_path[i];
            }
        }

    } else {
        unsigned int path_length = 1;
        for (unsigned int i = 1; i < this->number_of_cities; ++i) {
            if (current_path[i] == 0)
                break;
            path_length++;
        }

        unsigned int bound = matrix_reduction(this->distances,
                                              this->number_of_cities,
                                              current_path,
                                              path_length);

        current_path[level] = 1;
        while ((bound < this->optimal_cost) &&
               (current_path[level] < this->number_of_cities)) {

            bool isDistinct = true;

            for (unsigned int i = 0; i < level; ++i) {
                if (current_path[i] == current_path[level]) {
                    isDistinct = false;
                    break;
                }
            }
            if (isDistinct) {
                solve_with_backtrack(level + 1, optimal_path, current_path);
            }
            current_path[level] = current_path[level] + 1;
        }
    }
    delete[] current_path;
}

void Tsp::solve_with_branch_and_bound(unsigned int level,
                                      unsigned int* optimal_path,
                                      unsigned int* _current_path) {
    // TODO

}

unsigned int Tsp::matrix_reduction(unsigned int **distances,
                                   unsigned int dimension,
                                   unsigned int *current_path,
                                   unsigned int path_length) {

    unsigned int** matrix = new unsigned int*[dimension];
    for (unsigned int i = 0; i < dimension; ++i)
        matrix[i] = new unsigned int[dimension];

    for (unsigned int i = 0; i < dimension; ++i) {
        for (unsigned int j = 0; j < dimension; ++j) {
            matrix[i][j] = distances[i][j];
        }
    }

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

    result = calculate_bound(matrix, dimension) + path_distance;
    for (unsigned int i = 0; i < dimension; ++i) {
        delete[] matrix[i];
        matrix[i] = 0;
    }

    delete[] matrix;
    matrix = 0;

#ifdef DEBUG
    cout << "Bound result: " << result << endl;
#endif /* DEBUG */

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
