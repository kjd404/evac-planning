// Test with 4 high safety nodes grouped in the bottom right corner of grid
city multiGridHighway 4 3
// ES+ sigma, hours, pop/childpop, t_size, xover, mutate
parameters ES+ 0.1 0.25 100 100 3 0.2 0.5
// Describe edges
// src, dst, maxCapacity, freeflow, b, Beta, safety
edge 0 0 1000.0 0.0 0.0 0.0 0.0
edge 0 1 1000.0 0.016 4.00 0.15 0.0
edge 0 3 1000.0 0.066 4.00 0.15 0.0
edge 1 1 1000.0 0.0 0.0 0.0 0.0
edge 1 0 1000.0 0.016 4.00 0.15 0.0
edge 1 2 1000.0 0.016 4.00 0.15 0.0
edge 2 2 1000.0 0.0 0.0 0.0 0.0
edge 2 1 1000.0 0.016 4.00 0.15 0.0
edge 2 3 1000.0 0.016 4.00 0.15 0.0
edge 3 3 1000.0 0.0 0.0 0.0 1.0
edge 3 0 1000.0 0.066 4.00 0.15 0.0
edge 3 2 1000.0 0.016 4.00 0.15 0.0
// describe nodes
// node id, capacity, wait time, safety, x coord, y coord
node 0 1 0.016 0.0 0.0 0.0
node 1 1 0.016 0.0 1.0 0.0
node 2 1 0.016 0.0 1.0 1.0
node 3 1 0.016 1.0 0.0 1.0
// describe agents
// agent start node, number of agents, number of individuals per agent
agent 0 100 10
show topology
// Run command - run iterations, print interval
run 100 10
//simulate simtest
show parameters
slang testslang
