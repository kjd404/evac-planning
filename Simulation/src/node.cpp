// Copyright 2017 <University of Idaho>
#include <map>
#include <utility>
#include <vector>
#include <memory>
#include "node.h"

// Node static to distribute ascending ids
int Node::ID = 0;

Node::Node(std::map<std::shared_ptr<Edge>, float> prob, float safety) {
  // Receive an id, increment for the next created node
  this->id = ID++;
  this->prob = prob;
  this->safety = safety;
}

std::shared_ptr<Edge> Node::get_self_edge() {
  for (auto iterator = prob.begin(); iterator != prob.end(); iterator++) {
    if (iterator->first->get_from()->get_id() ==
	iterator->first->get_to()->get_id()) {
      return iterator->first;
    }
  }

  return NULL;
}

// Returns a vector if nodeIDs, corresponding to this node's neighbor nodes.
std::vector<int> Node::get_neighbor_IDs() {
  std::vector<int> neighbor_IDs;

  // Iterate over the set of edges leaving this node, add neighbor node ID
  for (auto iterator = prob.begin(); iterator != prob.end(); iterator++) {
    neighbor_IDs.push_back(iterator->first->get_to()->get_id());
  }

  // Return the neighboring nodes' IDs.
  return neighbor_IDs;
}

void Node::print_node() {
  printf("ID: %d Safety: %f\n", this->id, this->safety);

  for (auto iterator = prob.begin(); iterator != prob.end(); iterator++) {
    printf("\t%d -> %d : %f\n", iterator->first->get_from()->get_id(),
	   iterator->first->get_to()->get_id(), iterator->second);
  }
}

void Node::add_edge(std::shared_ptr<Edge> edge) {
  this->prob.insert(std::pair<std::shared_ptr<Edge>, float>(edge, 0.0));
}

void Node::remove_edge(std::shared_ptr<Edge> edge) {
  prob.erase(edge);
}

void Node::set_safety(float safetyVal) {
  safety = safetyVal;
}

void Node::init_probs() {
  // Get an even distribution over each connection.
  float prob_per_node = 1.0 / static_cast<float>(prob.size());

  for (auto iterator = prob.begin(); iterator != prob.end(); iterator++) {
    iterator->second = prob_per_node;
  }
}

void Node::set_probs(std::vector<float> new_probs) {
  int i = 0;
  for (auto& p : prob) {
    p.second = new_probs.at(i);
    i++;
  }
}

int Node::is_connected(int nodeID) {
  for (auto iterator = this->prob.begin(); iterator != prob.end(); iterator++) {
    if (iterator->first->get_to()->get_id() == nodeID) {
      return iterator->first->get_id();
    }
  }
  return -1;
}
