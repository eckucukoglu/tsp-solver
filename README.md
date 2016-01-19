# tsp-solver
Traveling Salesman Problem Solver

TSP solver finds optimal route using Backtracking and Branch & Bound design methods.

# specifications
* Matrix reduction is used as the bounding function.
* Graph is undirected with positive edges only.
* Nodes will be expanded in the given input order.

# input format
* First line indicates design technique: {1: backtracking, 2: branch & bound}
* Second line: {#nodes #edges}
* Rest of input define edges of the graph: {node_id node_id edge_weight}
* Example input is available in [test](https://github.com/eckucukoglu/tsp-solver/test) directory.

# output format
* First line indicates minimum cost of the route.
* Rest of output define edges in the optimum route.

# how to run
```
make
./tsp-solver < test/input > test/output
```
