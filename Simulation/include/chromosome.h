// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_CHROMOSOME_H_
#define SIMULATION_INCLUDE_CHROMOSOME_H_

#include <vector>
#include <cstdio>

#include "rand.h"
#include "param.h"
extern Parameters params;

class Chromosome {
    std::vector<std::vector<float> > data;
    float fitness;

 public:
    explicit Chromosome(std::vector<std::vector<float> >);

    std::vector<std::vector<float> > get_data() { return data; }
    float get_fitness() { return fitness; }

    void set_fitness(float f) { fitness = f; }

    Chromosome swap_mutate();
    Chromosome mutate_all();
    Chromosome mutate();
    Chromosome cross(Chromosome);

    void print_chromosome();
};

#endif  // SIMULATION_INCLUDE_CHROMOSOME_H_
