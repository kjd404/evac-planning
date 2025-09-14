city YDistribution 5 4
// ES( 100 + 100 ) sigma = 0.1, hours = 4, t_size = 3, xover=0.2, mutate=0.5
parameters ES+ 0.1 0.3 100 100 3 0.2 0.5
// Describe edges
// src, dst, maxCapacity, freeflow, B, Beta, safety
edge 0 0 100.0 0.0 0.0 0.0 0.5
edge 0 1 100.0 0.016 4.00 0.15 0.0
edge 1 1 200.0 0.0 0.0 0.0 0.0
edge 1 0 100.0 0.016 4.00 0.15 0.0
edge 1 2 100.0 0.016 4.00 0.15 0.0
edge 1 3 100.0 0.016 4.00 0.15 0.0
edge 2 2 100.0 0.0 0.0 0.0 0.5
edge 2 1 100.0 0.016 4.00 0.15 0.0
edge 3 3 100.0 0.0 0.0 0.0 0.0
edge 3 1 100.0 0.016 4.00 0.15 0.0
edge 3 4 100.0 0.016 4.00 0.15 0.0
edge 4 4 100.0 0.0 0.0 0.0 1.0
edge 4 3 100.0 0.016 4.00 0.15 0.0
node 0 100 0.0006 0.5 0.0 0.0
node 1 200 0.0006 0.0 1.0 1.0
node 2 100 0.0006 0.5 0.0 2.0
node 3 100 0.0006 0.0 2.0 1.0
node 4 100 0.0006 1.0 3.0 1.0
agent 1 200 1
show topology
run 100 10
