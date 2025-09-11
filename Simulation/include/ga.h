// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_GA_H_
#define SIMULATION_INCLUDE_GA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <climits>
#include <memory>
#include <utility>
#include <vector>

#include "node.h"
#include "city.h"
#include "edge.h"
#include "chromosome.h"
#include "pop.h"
#include "agent.h"
#include "param.h"

extern std::shared_ptr<City> theCity;
extern Parameters params;

extern std::vector<Chromosome> predefined_probabilities;

// Run wrapper - keeps things modular. Allows addition of different GAs later.
void run_ga(int ga_code, int iterations, int population,
             int runs, int print_interval);

// Generational algorithm. Runs for iterations, on population,
// printing/outputting at print_interval
void generational(int iterations, int print_interval, int population);

// Runs the evolution strategy method.
void evolution_strategy(int iterations, int population, int runs,
                         int child_population, int print_interval);

void output_stats(std::vector<int> gens_vec, std::vector<float> fit_vec, int r);
std::pair<int, int> get_gens_min_max(std::vector<int> gens_vec, int r);
std::pair<float, float> get_fit_min_max(std::vector<float> fit_vec, int r);
float average_generations(std::vector<int> gens_vec, int r);
float average_fitness(std::vector<float> fit_vec, int r);

// Fitness function - takes a chromosome and simulates traffic to calc fitness
float fitness(Chromosome *c);

// Variation of fitness function used to initialize population by moving
// Agents from safety towards danger, iterating over sets of agent starting
// locations
void initialization_fitness(Chromosome *c, int agent_set);

// Returns a vector of float vectors with random probabilities summing to
// one, for each node.
// The size is n X max_degree, with n being the number of nodes, and
// max_degree being the highest number of connected edges to any node.
std::vector<std::vector<float> > get_random_probabilities(
                                int num_nodes, int max_degree,
                                std::vector<std::shared_ptr<Node> > nodes);

// Takes a file name for a file containing a set of probabilities for the
// already loaded city. Runs and outputs a simulation of the city with
// the loaded probabilities and SLANG parameters.
// Used for testing constructed probability sets.
void simulate_from_file(char *filename);

// This performs an exaustive search for a specific topology.
// 0 -> 1 -> 2
// With exhaustive search of probabilities for nodes 0 and 1, and a
// stay probability on node 2 of 1.0.
// Further, the safety should be zero everywhere except the stay edge on node
// 2. Use carefully.
void exhaustive_search();

// Prints evolution parameters data structure
void print_parameters();

// Sets the parameters for evolution.
void set_parameters(int strat, float sigma, int pop_size, int c_pop_size,
                     int t_size, float xover_p, float mutate_p);

// Reads and loads in sets of probabilities from specified file.
void read_probs(char *filename);

// Writes the header for data output in write_best_probs
void print_header();

// Writes the best individual's probabilities to specified file.
void write_best_probs(std::vector<Chromosome> pop);

// Wrapper for multi-threading simulations.
void thread_wrapper(std::vector<std::pair<float, Chromosome> > *children,
                     City city_copy);

// Threder for fitness evaluatons (simulations)
void thread_fitness(Chromosome *c, City city_copy, int pid);

// Function to write the current evolution data out.
void write_curr_data(std::pair<float, Chromosome> p, int run,
                      int curr_gen, int max_gens);

// Initializes probabilities by starting agents at locations of safety
// and iteratively moving them away from safety.
void probability_init_safety_to_danger(int iterations, int population,
                                       int child_population,
                                       int print_interval);

// Runs dijkstra's algorithm to all nodes
void apply_dijkstra_algorithm();

// Run dijkstra's algorithm starting from particular node as start node
void dijkstra_algorithm(std::shared_ptr<Node> startNode, std::vector<std::shared_ptr<Node>>&);

#endif  // SIMULATION_INCLUDE_GA_H_
