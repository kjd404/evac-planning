// Tests 5 nodes along a straight line, safety at node 2, 4. 
city stretchOfRoad 5 3
// ES+ sigma, hours, pop size, child pop size, tourney size = 3,
// xover prob = 0.2, mutate prob = 0.5
parameters ES+ 0.1 4 200 200 3 0.2 0.5
// Describe edges
// src, dst, maxCapacity/num lanes, freeflow, B, Beta, safety
edge 0 0 0.0 0.0 0.0 0.0 0.0
edge 0 1 1.0 0.10 4.0 0.15 0.0
edge 1 1 0.0 0.0 0.0 0.0 0.0
edge 1 0 1.0 0.10 4.0 0.15 0.0
edge 1 2 1.0 0.10 4.0 0.15 0.0
edge 2 2 0.0 0.0 0.0 0.0 0.99
edge 2 1 1.0 0.10 4.0 0.15 0.0
edge 2 3 1.0 0.10 4.0 0.15 0.0
edge 3 3 0.0 0.0 0.0 0.0 0.0
edge 3 2 1.0 0.10 4.0 0.15 0.0
edge 3 4 1.0 0.10 4.0 0.15 0.0
edge 4 4 0.0 0.0 0.0 0.0 1.0
edge 4 3 1.0 0.10 4.0 0.15 0.0
// Describe Nodes
// node id, capacity, wait time, safety, x coord, y coord
node 0 1 0.25 0.0 0.0 0.0
node 1 1 0.25 0.0 1.0 0.0
node 2 1 0.25 1.0 2.0 0.0
node 3 1 0.25 0.0 3.0 0.0
node 4 1 0.25 0.0 4.0 0.0
// Describe agent population
// agent start node, num agents, individuals per agent
agent 0 10 1
show topology
// Run command - run iterations, print/output interval
run 1000 100
