// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_AGENT_H_
#define SIMULATION_INCLUDE_AGENT_H_

#include <string>
#include <memory>
#include <iostream>
#include <vector>

#include "node.h"
#include "edge.h"

class Agent {
  int id;
  float safety;
  int num_members;
  float next_time;
  int moves;
  float transit_time;
  float final_time;

  // route[i] should correspond to route_times[i]
  std::vector<int> route;
  std::vector<float> route_times;

  // Either current location, or destination
  std::shared_ptr<Node> to;
  std::shared_ptr<Node> from;
  std::shared_ptr<Edge> edge;

 public:
  Agent(int num_members = 0,
        float next_time = 0.0,
        std::shared_ptr<Node> to = nullptr,
        std::shared_ptr<Node> from = nullptr,
        std::shared_ptr<Edge> edge = nullptr);

  // Accessors
  float get_next_time() const { return this->next_time; }
  std::shared_ptr<Node> get_to() { return this->to; }
  std::shared_ptr<Node> get_from() { return this->from; }
  std::shared_ptr<Edge> get_edge() { return this->edge; }
  float get_safety() const { return this->safety; }
  int get_id() const { return this->id; }
  int get_moves() const { return this->moves; }
  float get_transit_time() const { return this->transit_time; }
  float get_final_time() const { return this->final_time; }
  float get_curr_safety() const;
  int get_member_count() const { return num_members; }
  const std::vector<int>& get_route() const { return this->route; }
  const std::vector<float>& get_route_times() const { return this->route_times; }
  std::vector<int> get_collapsed_route();

  // Printers
  // Prints agent information
  void print_agent() const;
  // Prints unformatted route information
  void print_route() const;
  // Prints *more* formatted route information
  void print_route_clean() const;

  // Adds safety s to total safety. Used for integrating safety over time
  void add_safety(float s) { safety += s; }

  // Increment the number of moves the agent has taken
  void inc_moves() { moves++; }

  // Increment the total transit time of the agent, by amount t
  void inc_transit_time(float t) { transit_time += t; }

  // Adds nodeID n to the route taken by the agent.
  void add_to_route(int n);

  // Setters
  void set_time(float t) { this->next_time = t; }
  void set_to(std::shared_ptr<Node> n) { this->to = n; }
  void set_from(std::shared_ptr<Node> n) { this->from = n; }
  void set_edge(std::shared_ptr<Edge> e) { this->edge = e; }
  void set_id(int i) { this->id = i; }
  void set_final_time(float f) { this->final_time = f; }
  void set_safety(float f) { this->safety = f; }

  // Comparison operator for priority queue use. 
  struct cmpSoonest {
    bool operator() (const Agent& a, const Agent& b) const {
      return a.get_next_time() > b.get_next_time();
    }
  };
};

#endif  // SIMULATION_INCLUDE_AGENT_H_
