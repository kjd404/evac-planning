// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_NODE_H_
#define SIMULATION_INCLUDE_NODE_H_

#include <map>
#include <memory>
#include <algorithm>
#include <vector>

#include "edge.h"

class Edge;

class Node {
  static int ID;  // Defined in node.cpp
  int id;
  int capacity;
  float wait_time;
  float safety;
  float longitude;
  float latitude;

  std::map<std::shared_ptr<Edge>, float> prob;

 public:
  Node(std::map<std::shared_ptr<Edge>, float> =
       std::map<std::shared_ptr<Edge>, float>(), float = 1.0);

  int get_id() { return id; }
  int get_capacity() { return capacity; }
  float get_wait_time() { return wait_time; }
  float get_safety() { return safety; }
  float get_longitude() { return longitude; }
  float get_latitude() { return latitude; }
  std::map<std::shared_ptr<Edge>, float> get_prob() { return prob; }

  std::shared_ptr<Edge> get_self_edge();
  std::vector<int> get_neighbor_IDs();

  void print_node();

  void add_edge(std::shared_ptr<Edge>);
  void remove_edge(std::shared_ptr<Edge>);

  void set_capacity(int c) { capacity = c; }
  void set_wait_time(float w) { wait_time = w; }
  void set_safety(float safetyVal);
  void set_longitude(float l) { longitude = l; }
  void set_latitude(float l) { latitude = l; }

  void init_probs();
  void set_probs(std::vector<float>);

  // Checks if this node is connected to nodeID.
  // Returns the edge that recognized this node as the "from" node
  // and the node with nodeID as the "to" node. Returns -1 otherwise.
  int is_connected(int nodeID);
};

#endif  // SIMULATION_INCLUDE_NODE_H_
