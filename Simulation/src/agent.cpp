// Copyright 2017 <University of Idaho>
#include <memory>
#include <vector>
#include "agent.h"

/* The Agent class constructor */
Agent::Agent(int num_members, float next_time, std::shared_ptr<Node> to,
	     std::shared_ptr<Node> from, std::shared_ptr<Edge> edge) {
    this->num_members = num_members;
    this->next_time = next_time;
    this->to = to;
    this->from = from;
    this->edge = edge;
    this->safety = 0.0;
    this->moves = 0;
    this->transit_time = 0.0;
    this->final_time = 0.0;
}

float Agent::get_curr_safety() const {
    if (this->edge) {
	return this->edge->get_safety();
    }

    return this->from->get_safety();
}

std::vector<int> Agent::get_collapsed_route() {
    std::vector<int> collapsed_route;

    int last = route[0];
    collapsed_route.push_back(last);
    if (route.size() > 1) {
	for (int i = 1; i < route.size(); i++) {
	    if (last != route[i]) {
		collapsed_route.push_back(route[i]);
	    }
	    last = route[i];
	}
    }

    return collapsed_route;
}

void Agent::print_agent() const {
    printf("Agent: \n");

    printf("\t%d members traveling %d -> %d ",
	    num_members, this->from->get_id(), this->to->get_id());

    if (this->edge) {
	printf("on edge %d\n", this->edge->get_id());
	this->edge->print_edge();
    } else {
	printf("on null edge\n");
    }

    printf("\tSafety: %f\n", this->get_safety());
}

void Agent::print_route() const {
    printf("*** Agent %d's route, safety %g\n", this->id,
	    this->get_curr_safety());

    for (auto i : this->route) {
	printf("%d ", i);
    }
    printf("\n");

    for (auto f : this->route_times) {
	printf("%g ", f);
    }
    printf("\n");
}

void Agent::print_route_clean() const {
  std::vector<int> indices_to_print;

  int last = route[0];
  indices_to_print.push_back(0);
  if (route.size() > 1) {
    for (int i = 1; i < route.size(); i++) {
      if (last != route[i]) {
	indices_to_print.push_back(i);
      }
      last = route[i];
    }
  }

  printf("*** Agent %d's route, safety %g\n", this->id,
	 this->get_curr_safety());

  if (route.size() != route_times.size()) {
    printf("Agent::print_route_clean() error:");
    printf("route and route_times have different sizes. Not printing.\n");
  } else {
    for (auto index : indices_to_print) {
      printf("%d\t", route[index]);
    }
    printf("\n");
    for (auto index : indices_to_print) {
      printf("%f ", route_times[index]);
    }
    printf("\n");
  }
}

void Agent::add_to_route(int n) {
    route_times.push_back(this->transit_time);
    route.push_back(n);
}
