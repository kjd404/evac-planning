// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_EDGE_H_
#define SIMULATION_INCLUDE_EDGE_H_

#include <memory>
#include <cmath>

#include "node.h"
class Node;

class Edge {
  std::shared_ptr<Node> to;
  std::shared_ptr<Node> from;

  int id;
  float c;
  float cmax;
  float freeflow;
  float bcoeff;
  float powcoeff;
  float length;
  float safety;
  int total_count;

 public:
  // to node, from node, cmax, freeflow, bcoeff, powcoeff, length, safety, id
  Edge(std::shared_ptr<Node> from,
       std::shared_ptr<Node> to,
       float cmax = 1.0,
       float freeflow = 1.0,
       float bcoeff = 1.0,
       float powcoeff = 1.0,
       float safety = 1.0,
       int id = 0);


  int get_id() { return id; }
  std::shared_ptr<Node> get_to() { return to; }
  std::shared_ptr<Node> get_from() { return from; }
  float get_cmax() { return cmax; }
  float get_freeflow() { return freeflow; }
  float get_bcoeff() { return bcoeff; }
  float get_powcoeff() { return powcoeff; }
  float get_length() { return length; }
  float get_c() { return c; }

  float get_safety() { return safety; }
  int get_total_count() { return total_count; }

  void inc_c(int inc) { c += inc; total_count += inc; }
  void dec_c(int dec) { c -= dec; }
  void init() { c = 0.0; total_count = 0; }

  void print_edge();

  float time();

  void set_safety(float safetyVal) { safety = safetyVal; }
};

#endif  // SIMULATION_INCLUDE_EDGE_H_
