#include "Reader.h"

unsigned int InputReader::design_technique = 0;
unsigned int** InputReader::distances = NULL;
unsigned int InputReader::number_of_cities = 0;

void InputReader::read() {
    unsigned int number_of_distances;

    cin >> design_technique >> number_of_cities >> number_of_distances;

    distances = new unsigned int*[number_of_cities];
    for (unsigned int i = 0; i < number_of_cities; ++i)
        distances[i] = new unsigned int[number_of_cities];

    for (unsigned int i = 0; i < number_of_cities; ++i) {
        for (unsigned int j = 0; j < number_of_cities; ++j) {
            distances[i][j] = UINT_MAX;
        }
    }

    for (unsigned int i = 0; i < number_of_distances; ++i) {
        unsigned int from, to, distance;

        cin >> from >> to >> distance;

        distances[from-1][to-1] = distance;
        distances[to-1][from-1] = distance;
    }
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
