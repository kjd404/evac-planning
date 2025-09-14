city fork1 5 3
// ES( 100 + 100 ) sigma = 0.1, hours = 4, t_size = 3, xover=0.2, mutate=0.5
parameters ES+ 0.1 4 100 100 3 0.2 0.5
// Describe edges
// src, dst, maxCapacity, freeflow, B, Beta, safety
edge 0 0 10.0 0.10 4.00 0.15 2.0 0.0
edge 0 1 10.0 0.10 4.00 0.15 2.0 0.25
edge 1 1 10.0 0.10 4.00 0.15 2.0 0.5
edge 1 2 10.0 0.10 4.00 0.15 2.0 0.5
edge 1 4 10.0 0.10 4.00 0.15 2.0 0.75
edge 2 2 10.0 0.10 4.00 0.15 2.0 0.5
edge 2 3 10.0 0.10 4.00 0.15 2.0 0.75
edge 3 3 10.0 0.10 4.00 0.15 2.0 1.0
edge 4 4 10.0 0.10 4.00 0.15 2.0 1.0
safety node 0 0.0
safety node 1 0.5
safety node 2 0.5
safety node 3 1.0
safety node 4 1.0
show topology
run 1000 100
