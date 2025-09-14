city anaheim 10 4
// ES+ sigma, hours, pop/childpop, t_size, xover, mutate
parameters ES+ 0.1 50.0 100 100 3 0.2 0.5
// Edges
// src, dst, maxCapacity, freeflow, beta, b, safety
edge 0 0 0.0 0.0 0.0 0.0 0.0
edge 0 1 100.0 2.0 4.0 0.3 0.0
edge 1 1 0.0 0.0 0.0 0.0 0.0
edge 1 2 100.0 1.0 4.0 0.3 0.0
edge 1 3 100.0 3.0 4.0 0.3 0.0
edge 2 2 0.0 0.0 0.0 0.0 0.0
edge 2 7 100.0 1.0 4.0 0.3 0.0
edge 3 3 0.0 0.0 0.0 0.0 0.0
edge 3 4 100.0 10.0 4.0 0.3 0.0
edge 3 5 100.0 2.0 4.0 0.3 0.0
edge 4 4 0.0 0.0 0.0 0.0 0.0
edge 4 6 100.0 10.0 4.0 0.3 0.0
edge 5 5 0.0 0.0 0.0 0.0 0.0
edge 5 8 100.0 3.0 4.0 0.3 0.0
edge 6 6 0.0 0.0 0.0 0.0 0.0
edge 6 5 100.0 10.0 4.0 0.3 0.0
edge 7 7 0.0 0.0 0.0 0.0 0.0
edge 7 8 100.0 1.0 4.0 0.3 0.0
edge 8 8 0.0 0.0 0.0 0.0 0.0
edge 8 9 100.0 2.0 4.0 0.3 0.0
edge 9 9 0.0 0.0 0.0 0.0 1.0
// Nodes
// node id, capacity, wait time, safety, x coord, y coord
node 0 1 0.016 0.0 0.0 0.0
node 1 1 0.016 0.0 0.0 0.0
node 2 1 0.016 0.0 0.0 0.0
node 3 1 0.016 0.0 0.0 0.0
node 4 1 0.016 0.0 0.0 0.0
node 5 1 0.016 0.0 0.0 0.0
node 6 1 0.016 0.0 0.0 0.0
node 7 1 0.016 0.0 0.0 0.0
node 8 1 0.016 0.0 0.0 0.0
node 9 1 0.016 1.0 0.0 0.0
// Agents
agent 0 100 10
run 100 10
