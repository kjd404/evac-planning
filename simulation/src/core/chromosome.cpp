// Copyright 2017 <University of Idaho>
#include <vector>
#include "chromosome.h"

Chromosome::Chromosome(std::vector<std::vector<float> > data) {
  this->data = data;
}

Chromosome Chromosome::swap_mutate() {
  Chromosome child(get_data());

  for (auto& v : child.get_data()) {
    int choice1 = randMod(v.size());
    int choice2 = choice1;

    while (choice2 == choice1) {
      choice2 = randMod(v.size());
    }

    float tmp = v.at(choice1);
    v.at(choice1) = v.at(choice2);
    v.at(choice2) = tmp;
  }

  return child;
}

Chromosome Chromosome::mutate_all() {
  //    Chromosome child(get_data());
  std::vector<std::vector<float> > cp = this->data;

  for (auto& v : cp) {
    if (choose(params.get_mutate_prob())) {
      for (auto& f : v) {
	f += randNorm(params.get_sigma());
	if (f < 0.0) {
	  f = 0.0;  // No negative weights
	}
      }

      // Normalize probabilities so they sum to one
      float sum = 0.0;
      for (auto f : v) {
	sum += f;  // Get total
      }

      for (int i = 0; i < v.size(); i++) {
	v.at(i) = v.at(i) / sum;
      }
    }
  }
  Chromosome child(cp);
  return child;
}

Chromosome Chromosome::mutate() {
  std::vector<std::vector<float> > cp = this->data;

  for (auto& v : cp) {  // Per node edge weights
    if (choose(params.get_mutate_prob())) {
      // Choose edge to change

      // I think this choice might be picking bad spots.
      // Not all nodes have max degree edges, is that accounted for?

      int choice = randMod(v.size());

      // Choose amount to change edge by
      double delta = randNorm(0.1);

      // Change edge weight by amount chosen
      v.at(choice) += delta;

      // No negative weights
      if (v.at(choice) < 0.0) {
	v.at(choice) = 0.0;
      }

      // Sum all weights
      float sum = 0.0;
      for (float f : v) {
	sum += f;
      }

      // Normalize weights
      for (int i = 0; i < v.size(); i++) {
	v.at(i) /= sum;
      }
    }
  }
  Chromosome child(cp);

  return child;
}

Chromosome Chromosome::cross(Chromosome other) {
  Chromosome child(get_data());
  for (int i = 0; i < child.get_data().size(); i++) {
    if (choose(0.5)) child.get_data().at(i) = other.get_data().at(i);
  }

  return child;
}

void Chromosome::print_chromosome() const {
  for (auto v : data) {
    for (auto f : v) {
      printf("%f ", f);
    }
    printf("\n");
  }
}
