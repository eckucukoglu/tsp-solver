#ifndef _READER_H_
#define _READER_H_

#include <stdlib.h>

using namespace std;

/*
 * InputReader reads stdin and creates corresponding components.
 * Input template is of the form:
 * 
 * [design technique number]
 * [#nodes] [#edges]
 * [from node x] [to node y] [distance x-y]
 * ...
 */
class InputReader {

private:
    static unsigned int design_technique;
    static unsigned int **distances;
    static unsigned int number_of_cities;
    
public:
    static void read();
    
    /* Accessors for static member fields. */
    static unsigned int get_design_technique();
    static unsigned int** get_distances();
    static unsigned int get_number_of_cities();
};

#endif /* not defined _READER_H_ */
