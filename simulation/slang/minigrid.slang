// A small 4x4 grid (16 nodes) with safety at the top-right corner (node 15)
// Nodes are labeled row-major from 0 (bottom-left) to 15 (top-right).
city minigrid 16 4
// Parameters: ES+, sigma, sim_hours, pop_size, child_pop, tourney, xover, mutate
parameters ES+ 0.10 0.70 10 20 3 0.3 0.5
// Edges: self-edges (stay) and bidirectional grid links
// Self-edges; only node 15 has full safety (1.0)
edge 0 0 2000.0 0.0 0.0 0.0 0.0
edge 1 1 2000.0 0.0 0.0 0.0 0.0
edge 2 2 2000.0 0.0 0.0 0.0 0.0
edge 3 3 2000.0 0.0 0.0 0.0 0.0
edge 4 4 2000.0 0.0 0.0 0.0 0.0
edge 5 5 2000.0 0.0 0.0 0.0 0.0
edge 6 6 2000.0 0.0 0.0 0.0 0.0
edge 7 7 2000.0 0.0 0.0 0.0 0.0
edge 8 8 2000.0 0.0 0.0 0.0 0.0
edge 9 9 2000.0 0.0 0.0 0.0 0.0
edge 10 10 2000.0 0.0 0.0 0.0 0.0
edge 11 11 2000.0 0.0 0.0 0.0 0.0
edge 12 12 2000.0 0.0 0.0 0.0 0.0
edge 13 13 2000.0 0.0 0.0 0.0 0.0
edge 14 14 2000.0 0.0 0.0 0.0 0.0
edge 15 15 2000.0 0.0 0.0 0.0 1.0
// Grid connectivity (bidirectional). Freeflow ~= 0.05, b=4.0, beta=0.15, safety=0.0
// Helper indexing: row r in [0..3], col c in [0..3], id = 4*r + c
// Horizontal links
edge 0 1 1000.0 0.05 4.0 0.15 0.0
edge 1 0 1000.0 0.05 4.0 0.15 0.0
edge 1 2 1000.0 0.05 4.0 0.15 0.0
edge 2 1 1000.0 0.05 4.0 0.15 0.0
edge 2 3 1000.0 0.05 4.0 0.15 0.0
edge 3 2 1000.0 0.05 4.0 0.15 0.0
edge 4 5 1000.0 0.05 4.0 0.15 0.0
edge 5 4 1000.0 0.05 4.0 0.15 0.0
edge 5 6 1000.0 0.05 4.0 0.15 0.0
edge 6 5 1000.0 0.05 4.0 0.15 0.0
edge 6 7 1000.0 0.05 4.0 0.15 0.0
edge 7 6 1000.0 0.05 4.0 0.15 0.0
edge 8 9 1000.0 0.05 4.0 0.15 0.0
edge 9 8 1000.0 0.05 4.0 0.15 0.0
edge 9 10 1000.0 0.05 4.0 0.15 0.0
edge 10 9 1000.0 0.05 4.0 0.15 0.0
edge 10 11 1000.0 0.05 4.0 0.15 0.0
edge 11 10 1000.0 0.05 4.0 0.15 0.0
edge 12 13 1000.0 0.05 4.0 0.15 0.0
edge 13 12 1000.0 0.05 4.0 0.15 0.0
edge 13 14 1000.0 0.05 4.0 0.15 0.0
edge 14 13 1000.0 0.05 4.0 0.15 0.0
edge 14 15 1000.0 0.05 4.0 0.15 0.0
edge 15 14 1000.0 0.05 4.0 0.15 0.0
// Vertical links
edge 0 4 1000.0 0.05 4.0 0.15 0.0
edge 4 0 1000.0 0.05 4.0 0.15 0.0
edge 1 5 1000.0 0.05 4.0 0.15 0.0
edge 5 1 1000.0 0.05 4.0 0.15 0.0
edge 2 6 1000.0 0.05 4.0 0.15 0.0
edge 6 2 1000.0 0.05 4.0 0.15 0.0
edge 3 7 1000.0 0.05 4.0 0.15 0.0
edge 7 3 1000.0 0.05 4.0 0.15 0.0
edge 4 8 1000.0 0.05 4.0 0.15 0.0
edge 8 4 1000.0 0.05 4.0 0.15 0.0
edge 5 9 1000.0 0.05 4.0 0.15 0.0
edge 9 5 1000.0 0.05 4.0 0.15 0.0
edge 6 10 1000.0 0.05 4.0 0.15 0.0
edge 10 6 1000.0 0.05 4.0 0.15 0.0
edge 7 11 1000.0 0.05 4.0 0.15 0.0
edge 11 7 1000.0 0.05 4.0 0.15 0.0
edge 8 12 1000.0 0.05 4.0 0.15 0.0
edge 12 8 1000.0 0.05 4.0 0.15 0.0
edge 9 13 1000.0 0.05 4.0 0.15 0.0
edge 13 9 1000.0 0.05 4.0 0.15 0.0
edge 10 14 1000.0 0.05 4.0 0.15 0.0
edge 14 10 1000.0 0.05 4.0 0.15 0.0
edge 11 15 1000.0 0.05 4.0 0.15 0.0
edge 15 11 1000.0 0.05 4.0 0.15 0.0
// Nodes: id, capacity, wait_time, safety, x(col), y(row)
node 0  1 0.016 0.0 0.0 0.0
node 1  1 0.016 0.0 1.0 0.0
node 2  1 0.016 0.0 2.0 0.0
node 3  1 0.016 0.0 3.0 0.0
node 4  1 0.016 0.0 0.0 1.0
node 5  1 0.016 0.0 1.0 1.0
node 6  1 0.016 0.0 2.0 1.0
node 7  1 0.016 0.0 3.0 1.0
node 8  1 0.016 0.0 0.0 2.0
node 9  1 0.016 0.0 1.0 2.0
node 10 1 0.016 0.0 2.0 2.0
node 11 1 0.016 0.0 3.0 2.0
node 12 1 0.016 0.0 0.0 3.0
node 13 1 0.016 0.0 1.0 3.0
node 14 1 0.016 0.0 2.0 3.0
node 15 1 0.016 1.0 3.0 3.0
// Agents: random starts across the grid
agent random 50 2
// Optional: show topology
show topology
// Run EA: iterations, print interval, runs
run 10 5 1
