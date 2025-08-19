// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_POP_H_
#define SIMULATION_INCLUDE_POP_H_

#include <cstdio>
#include <map>
#include <functional>
#include <utility>
#include <vector>

#include "chromosome.h"

class Population {
 private:
  int pop_size;

  // std::multimap<float, Chromosome, std::less<float>> population;
  std::multimap<float, Chromosome, std::greater<float>> population;

 public:
  explicit Population(int p_size);

  int current_size() { return population.size(); }

  int size() { return pop_size; }

  // std::multimap<float, Chromosome, std::less<float>> get_population() {
  // return population;
  // }

  std::multimap<float, Chromosome, std::greater<float>> get_population() {
    return population;
  }

  std::pair<float, Chromosome> get_best();

  std::vector<Chromosome> vector_best();
  std::vector<Chromosome> get_vector();

  void print_population();
  void print_fitnesses();

  void add_chromosome(float f, Chromosome ind);
  void insert(int tourney_size, std::pair<float, Chromosome>);

  std::pair<float, Chromosome> select_at(int index);
  std::pair<float, Chromosome> select(int tourney_size);

  void cull();

  void clear();
};

#endif  // SIMULATION_INCLUDE_POP_H_
