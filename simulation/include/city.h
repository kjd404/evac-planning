// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_CITY_H_
#define SIMULATION_INCLUDE_CITY_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <deque>
#include <fstream>
#include <set>

#include "node.h"
class Node;

#include "edge.h"
class Edge;

#include "agent.h"
#include "rand.h"
#include "param.h"

class City {
  float sim_hours;
  std::string name;
  int num_nodes;
  int degree;

  std::vector<std::shared_ptr<Node> > nodes;
  std::vector<std::shared_ptr<Edge> > edges;

  std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agents;

  std::vector<Agent> init_agents;
  std::vector<std::set<int> > agent_start_sets;

  std::vector<std::vector<int> > routes;
  std::vector<float> safety_over_time;

 public:
  // Constructs the city object with name, nodes, and max degree of any node.
  City(std::string, int, int);

  // Accessors
  std::string get_name() { return name; }
  int get_num_nodes() { return num_nodes; }
  int get_degree() { return degree; }

  const std::vector<std::shared_ptr<Node> >& get_nodes() const { return nodes; }
  const std::vector<std::shared_ptr<Edge> >& get_edges() const { return edges; }

  std::shared_ptr<Node> get_node(int node_id) { return nodes.at(node_id); }

  std::priority_queue<Agent,
    std::deque<Agent>,
    Agent::cmpSoonest> get_agents() { return agents; }

  std::vector<Agent> get_agent_vector() const;

  int num_agents() const { return agents.size(); }
  int agent_group_size() const { return init_agents[0].get_member_count(); }

  float get_fitness();
  float sim_time() const { return sim_hours; }

  bool agent_sets_initialized();
  int num_agent_sets() { return agent_start_sets.size(); }

  // Print functions
  void print_nodes();
  void print_edges();
  void print_city();

  // Take a copy of the pq because print algorithm is destructive.
  void print_agents(std::priority_queue<Agent, std::deque<Agent>,
                    Agent::cmpSoonest> agents_copy);

  // Print drawable version of the city
  void print_drawable();
  void output_drawable();

  // Print Ahmed's tests
  void print_simulation();

  void set_sim_time(float t) { sim_hours = t; }

  // Runs the main genetic algorithm for arg1 iterations,
  // outputting data every arg2 intervals.
  void run(int iterations, int printInterval);

  // Reset agents in priority queue to initial random set up
  void reset_agents();

  // Set agent set to index provided.
  void set_agents(int agent_set);

  // Initializes node/edge probabilities
  void initialize_nodes();

  // Set all the edge traffic and traffic counts to 0
  void initialize_edges();

  // Sets nodes to the given set of probabilities.
  // There is a mapping from index to node IDs.
  void set_nodes(std::vector< std::vector<float> > prob_set);

  // Runs the agent simulation - specified for ahmeds tests (deprecated)
  float simulate();

  // Runs the simulation that optimizes safety
  float simulate_for_safety();

  // Returns the safety of all agents in the map summed together
  float get_sum_safety();

  // Gets the set of all unique routes agents took in the last simulation
  std::vector<std::vector<int> > get_route_set();

  // Returns safety over time (const view) and mutators for external writers
  const std::vector<float>& get_safety_over_time() const { return safety_over_time; }
  void clear_safety_over_time() { safety_over_time.clear(); }
  void append_safety_over_time(float v) { safety_over_time.push_back(v); }

  // Takes a node and selects an outgoing edge based on the probabilities
  std::shared_ptr<Edge> get_next_edge(std::shared_ptr<Node>);

  // Mutators.
  std::shared_ptr<Node> add_node();

  // from node, to node, cmax, freeflow, bcoeff, powcoeff, safety
  std::shared_ptr<Edge> add_edge(int from_index,
                                 int to_index,
                                 float cmax = 1.0,
                                 float freeflow = 1.0,
                                 float bcoeff = 1.0,
                                 float powcoeff = 1.0,
                                 float safety = 1.0);

  // Removes the edge between nodes with specified IDs
  std::shared_ptr<Edge> remove_edge(int fromID, int toID);

  // Sets the safety of the specified node, with the specified value
  void set_node_safety(int nodeID, float safetyVal);

  // Sets the safety of the specified edge with the specified value
  void set_edge_safety(int node1, int node2, float safetyVal);

  // Sets node values for node with specified ID
  void set_node(int node_ID, int capacity, float wait_time,
                float safety, float longitude, float latitude);

  // Writes the city out as SLang. Needs continuous updating, as specs change
  void write_slang(Parameters params, char *filename);

  // Adds num_agents of agents, with group size num_ind, at node_id
  void add_agents(int node_id, int num_agents, int num_ind);

  // Adds an agent to initial agents
  void add_agent(Agent a);

  // returns the maximum safety of any self-edge, AKA any node.
  float get_max_edge_safety();

  // Creates sets of integers corresponding to the nodes agents
  // should start at for the safety-to-danger probability initialization
  void generate_agent_starting_locations();

  void print_agent_sets();

  City get_semantic_copy();
};

#endif  // SIMULATION_INCLUDE_CITY_H_
