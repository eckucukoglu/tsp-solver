#ifndef _TSP_H_
#define _TSP_H_

using namespace std;

typedef struct node_struct {
    unsigned int node_id;
} Node;

typedef struct edge_struct {
    unsigned int edge_id;
    unsigned int weight;
    Node *node1;
    Node *node2;
} Edge;

class Tsp {

private:
    unsigned int design_technique;
    Node *cities;
    Edge *edges;
        
public:
    Tsp(unsigned int, Node *, Edge *);
    Edge **solve();
    Edge **solve_with_backtrack();
    Edge **solve_with_branch_and_bound();
    void print(Edge **edges_to_print);

};

#endif /* not defined _TSP_H_ */
