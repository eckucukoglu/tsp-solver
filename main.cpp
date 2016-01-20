/*
 * Travelling Salesman Problem Solver
 *
 * TSP solver finds optimal route using 
 * Backtracking and Branch & Bound design methods.
 * 
 * Emre Can Kucukoglu, eckucukoglu@gmail.com
 * https://github.com/eckucukoglu/tsp-solver
 */

#include "TSP.h"
#include "Reader.h"

int main () {
    
    /* Read input. */
    InputReader::read();
    unsigned int design_technique = InputReader::get_design_technique();
    unsigned int** distances = InputReader::get_distances();
    unsigned int number_of_cities = InputReader::get_number_of_cities();
    
    /* Create TSP graph. */
    Tsp tsp = Tsp(design_technique, distances, number_of_cities);
    
    /* Solve TSP. */
    unsigned int *solution = tsp.solve();
    
    /* Print TSP solution. */
    tsp.print_solution(solution);
    
    delete[] solution;

    return 0;
}
