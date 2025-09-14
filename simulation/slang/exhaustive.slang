// Used for exhaustive search only
city exhaustedCity 3 2
// ES( 100 + 100 ) sigma = 0.1, hours = 4, t_size = 3, xover=0.2, mutate=0.5
parameters ES+ 0.1 0.2 100 100 3 0.2 0.5
// src, dst, maxCapacity, freeflow, B, Beta, safety
edge 0 0 0.0 0.0 0.0 0.0 0.0
edge 0 1 1000.0 0.016 4.00 0.15 0.0
edge 1 1 0.0 0.0 0.0 0.0 0.0
edge 1 2 1000.0 0.016 4.00 0.15 0.0
edge 2 2 0.0 0.0 0.0 0.0 1.0
// node id, capacity, wait time, safety, x coord, y coord
node 0 1 0.016 0.0 0.0 0.0
node 1 1 0.016 0.0 1.0 0.0
node 2 1 0.016 1.0 2.0 0.0
agent 0 500 10
show topology
// run 100 10
// show parameters
exhaustive
