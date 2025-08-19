// Test with 4 high safety nodes grouped in the bottom right corner of grid
city a1 9 4
// ES+ sigma, hours, pop/childpop, t_size, xover, mutate
parameters ES+ 0.1 0.5 100 100 3 0.2 0.5
// Describe edges
// src, dst, maxCapacity, freeflow, b, Beta, safety
edge 0 0 0.0 0.0 0.0 0.0 0.0
edge 0 1 1000.0 0.004 4.00 0.15 0.0
edge 0 7 1000.0 0.008 4.00 0.15 0.0
edge 1 0 1000.0 0.004 4.00 0.15 0.0
edge 1 1 0.0 0.0 0.0 0.0 0.0
edge 1 2 1000.0 0.008 4.00 0.15 0.0
edge 1 7 1000.0 0.011 4.00 0.15 1.0
edge 2 1 1000.0 0.008 4.00 0.15 0.0
edge 2 2 0.0 0.0 0.0 0.0 0.0
edge 2 3 1000.0 0.007 4.00 0.15 0.0
edge 2 5 1000.0 0.004 4.00 0.15 1.0
edge 2 8 1000.0 0.002 4.00 0.15 0.0
edge 3 2 1000.0 0.007 4.00 0.15 0.0
edge 3 3 0.0 0.0 0.0 0.0 0.0
edge 3 4 1000.0 0.009 4.00 0.15 1.0
edge 3 5 1000.0 0.014 4.00 0.15 1.0
edge 4 3 1000.0 0.009 4.00 0.15 0.0
edge 4 4 0.0 0.0 0.0 0.0 1.0
edge 4 5 1000.0 0.010 4.00 0.15 1.0
edge 5 2 1000.0 0.004 4.00 0.15 0.0
edge 5 3 1000.0 0.014 4.00 0.15 0.0
edge 5 4 1000.0 0.010 4.00 0.15 1.0
edge 5 5 0.0 0.0 0.0 0.0 1.0
edge 5 6 1000.0 0.002 4.00 0.15 0.0
edge 6 5 1000.0 0.002 4.00 0.15 1.0
edge 6 6 0.0 0.0 0.0 0.0 0.0
edge 6 7 1000.0 0.001 4.00 0.15 0.0
edge 6 8 1000.0 0.006 4.00 0.15 0.0
edge 7 0 1000.0 0.008 4.00 0.15 0.0
edge 7 1 1000.0 0.011 4.00 0.15 1.0
edge 7 6 1000.0 0.001 4.00 0.15 0.0
edge 7 7 0.0 0.0 0.0 0.0 0.0
edge 7 8 1000.0 0.007 4.00 0.15 0.0
edge 8 2 1000.0 0.002 4.00 0.15 0.0
edge 8 6 1000.0 0.006 4.00 0.15 0.0
edge 8 7 1000.0 0.007 4.00 0.15 0.0
edge 8 8 0.0 0.0 0.0 0.0 0.0
// describe nodes
// node id, capacity, wait time, safety, x coord, y coord
node 0 1 0.016 0.0 0.0 1.0
node 1 1 0.016 0.0 1.0 0.0
node 2 1 0.016 0.0 2.0 0.0
node 3 1 0.016 0.0 3.0 0.0
node 4 1 0.016 1.0 4.0 1.0
node 5 1 0.016 1.0 3.0 2.0
node 6 1 0.016 0.0 2.0 2.0
node 7 1 0.016 0.0 1.0 2.0
node 8 1 0.016 0.0 2.0 1.0
// describe agents
// agent start node, number of agents, number of individuals per agent
agent 0 10 2
agent 1 10 2
show topology
// Run command - run iterations, print interval
//run 100 10
//show parameters
//remove edge from 1 to 2
//rmedge 1 2
//show topology
// Run command - run iterations, print interval
//run 100 10
run 100
show parameters
