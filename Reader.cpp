#include "Reader.h"

unsigned int InputReader::design_technique = 0;
unsigned int** InputReader::distances = NULL;
unsigned int InputReader::number_of_cities = 0;

void InputReader::read() {
    // TODO
}

unsigned int InputReader::get_design_technique() {
    return InputReader::design_technique;
}

unsigned int** InputReader::get_distances() {
    return InputReader::distances;
}

unsigned int InputReader::get_number_of_cities() {
    return InputReader::number_of_cities;
}
