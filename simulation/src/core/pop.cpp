// Copyright 2017 <University of Idaho>
#include <map>
#include <utility>
#include <vector>
#include <functional>
#include "pop.h"

Population::Population(int p_size) {
  this->pop_size = p_size;
}

std::pair<float, Chromosome> Population::get_best() const {
  // take the first element (greatest fitness) from the multimap
  auto iter = this->population.begin();
  std::pair<float, Chromosome> best_pair(iter->first, iter->second);

  return best_pair;
}

void Population::print_population() const {
  for (auto iter = this->population.begin();
       iter != this->population.end(); iter++) {
    printf("Fit: %f\n", iter->first);
    iter->second.print_chromosome();
  }
}

std::vector<Chromosome> Population::vector_best() const {
  std::vector<Chromosome> c_vec;
  c_vec.push_back(this->get_best().second);
  return c_vec;
}

std::vector<Chromosome> Population::get_vector() const {
  std::vector<Chromosome> c_vec;

  for (auto iter = this->population.begin();
       iter != this->population.end(); iter++) {
    c_vec.push_back(iter->second);
  }

  return c_vec;
}

void Population::add_chromosome(float f, Chromosome ind) {
  this->population.emplace(f, ind);
}

std::pair<float, Chromosome> Population::select_at(int index) {
  std::multimap<float, Chromosome, std::less<float> >::iterator iter =
    this->population.begin();

  if (index < this->population.size() && index >= 0) {
    while (std::distance(this->population.begin(), iter) != index) {
      iter++;
    }
  }

  return std::pair<float, Chromosome>(iter->first, iter->second);
}

std::pair<float, Chromosome> Population::select(int tourney_size) {
  std::vector< std::pair<float, Chromosome> > pop_copy;
  std::vector<int> options;
  int selected, rand_val, ret_index;

  // Copy all pairs from multimap to vector. Slow, annoying...
  // TODO(keith) Change Multimap to doublevector
  for (auto iter = this->population.begin();
       iter != this->population.end(); iter++) {
    pop_copy.push_back(std::pair<float, Chromosome>(iter->first,
						     iter->second));
  }

  for (int i = 0; i < pop_size; i++) {
    options.push_back(i);
  }

  selected = randMod(pop_size);
  ret_index = selected;
  std::pair<float, Chromosome> chosen = pop_copy[ret_index];

  for (int i = 0; i < tourney_size; i++) {
    rand_val = randMod(options.size());
    selected = options[rand_val];
    options.erase(options.begin() + rand_val);

    if (pop_copy[ret_index].first <= pop_copy[selected].first) {
      chosen = pop_copy[selected];
      ret_index = selected;
    }
  }

  return chosen;
}

void Population::insert(int tourney_size,
			 std::pair<float, Chromosome> new_ind) {
  std::vector< std::pair<float, Chromosome> > pop_copy;
  std::vector<int> options;
  int selected, rand_val, fit_index;
  int pop_size = this->population.size();

  // Copy all pairs from multimap to vector. Slow, annoying...
  for (auto iter = this->population.begin();
       iter != this->population.end(); iter++) {
    pop_copy.push_back(std::pair<float, Chromosome>(iter->first,
						     iter->second));
  }

  for (int i = 0; i < pop_size; i++) {
    options.push_back(i);
  }

  selected = randMod(pop_size);
  fit_index = selected;

  for (int i = 0; i < tourney_size; i++) {
    rand_val = randMod(options.size());
    selected = options[rand_val];
    options.erase(options.begin() + rand_val);

    if (pop_copy[fit_index].first >= pop_copy[selected].first) {
      fit_index = selected;
    }
  }

  std::multimap<float, Chromosome, std::less<float> >::iterator it =
    this->population.find(pop_copy[fit_index].first);
  this->population.erase(it);

  this->population.emplace(new_ind.first, new_ind.second);
}

void Population::print_fitnesses() const {
  for (auto iter = this->population.begin();
       iter != this->population.end(); iter++) {
    printf("%f\n", iter->first);
  }
}

void Population::cull() {
  // Remove worst elements until population size equals pop_size.
  // Use a fresh end() each iteration to avoid invalidated iterators.
  while (population.size() > pop_size) {
    auto last = population.end();
    --last;  // points to the worst because we use greater<float> ordering
    population.erase(last);
  }
}

void Population::clear() {
  this->population.clear();
}
