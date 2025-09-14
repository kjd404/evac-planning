// Copyright 2017 <University of Idaho>
#include <memory>
#include "edge.h"

Edge::Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to,
	   float cmax, float freeflow, float bcoeff, float powcoeff,
	   float safety, int id) {
  this->id = id;
  this->from = from;
  this->to = to;
  this->c = 0.0;
  this->cmax = cmax;
  this->freeflow = freeflow;
  this->bcoeff = bcoeff;
  this->powcoeff = powcoeff;
  this->total_count = 0;
  this->safety = safety;
}

void Edge::print_edge() {
  printf("ID: %d\t%d -> %d : %d\n", get_id(), get_from()->get_id(),
	 get_to()->get_id(), get_total_count());
  printf("\tFreeflow: %f\n", this->freeflow);
  printf("\tSafety: %f\n", this->safety);
}

// Returns the expected travel time
float Edge::time() {
  return freeflow * (1 + bcoeff * pow((c / cmax), powcoeff));
}
