#ifndef _TSP_H_
#define _TSP_H_

/* For UINT_MAX. */
#include <limits.h>
#include <stdlib.h>
#include <iostream>

#define BACKTRACKING 1
#define BRANCH_AND_BOUND 2

using namespace std;

/*
 * Travelling Salesman Problem
 *
 * It is a problem in graph theory requiring the most efficient (i.e., least
 * total distance) Hamiltonian cycle a salesman can take through each of cities.
 */
class Tsp {

private:
    /* 1: backtracking, 2: branch & bound. */
    unsigned int design_technique;
    /* Number of cities. Note that city ids starts from 1, not 0. */
    unsigned int number_of_cities;
    /* Symmetrical distances matrix between cities. */
    unsigned int **distances;
    /* */
    unsigned int optimal_cost;
    /* */
    unsigned int* solution;

    /*
     * Solves Tsp with backtracking.
     */
    void solve_with_backtrack(unsigned int level,
                              unsigned int* optimal_path,
                              unsigned int* _current_path);

    /*
     * Solves Tsp with branch and bound.
     */
    void solve_with_branch_and_bound(unsigned int level,
                                     unsigned int* optimal_path,
                                     unsigned int* _current_path);

    /*
     * Matrix reduction.
     */
    unsigned int matrix_reduction(unsigned int **matrix,
                                  unsigned int dimension,
                                  unsigned int *current_path,
                                  unsigned int path_length);

    unsigned int calculate_bound(unsigned int **matrix, unsigned int dimension);

    /*
     * Prints matrix to stdout.
     */
    void print_pretty_matrix(char const* desc, unsigned int **matrix,
                             unsigned int dimension);

    /*
     * Sorts array according to comparable array.
     */
    void insertion_sort (unsigned int arr[], unsigned int comparable[],
                         unsigned int length);

public:
    Tsp(unsigned int design_technique, unsigned int** distances,
        unsigned int number_of_cities);

    /*
     * Solves Tsp with with set design technique.
     */
    void solve();

    /*
     * Prints solution to stdout, template is of the form:
     *
     * [total distance covered]
     * [from city 1] [to city x] [distance 1-x]
     * [from city x] [to city y] [distance x-y]
     * ...
     */
    void print_solution();

    ~Tsp();
};

#endif /* not defined _TSP_H_ */
