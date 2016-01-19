#include "TSP.h"

Tsp::Tsp (unsigned int design, Node *cities, Edge *edges) {
    this->design_technique = design;
    this->cities = cities;
    this->edges = edges;
}
