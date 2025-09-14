// Copyright 2017 <University of Idaho>
#ifndef SIMULATION_INCLUDE_PARAM_H_
#define SIMULATION_INCLUDE_PARAM_H_

class Parameters {
 private:
  int evo_strat;
  int pop_size;
  int child_pop_size;
  int tourney_size;

  float sigma;
  float xover_prob;
  float mutate_prob;

 public:
  // Getters:
  int get_evo_strat() const { return this->evo_strat; }
  int get_pop_size() const { return this->pop_size; }
  int get_child_pop_size() const { return this->child_pop_size; }
  int get_tourney_size() const { return this->tourney_size; }
  float get_sigma() const { return this->sigma; }
  float get_xover_prob() const { return this->xover_prob; }
  float get_mutate_prob() const { return this->mutate_prob; }

  // Setters:
  void set_evo_strat(int s) { evo_strat = s; }
  void set_pop_size(int s) { pop_size = s; }
  void set_child_pop_size(int s) { child_pop_size = s; }
  void set_tourney_size(int s) { tourney_size = s; }
  void set_sigma(float s) { sigma = s; }
  void set_xover_prob(float p) { xover_prob = p; }
  void set_mutate_prob(float p) { mutate_prob = p; }

  // Printer:
  void print() {
    printf("Evolution parameters: ");
    if (evo_strat == 0) {
      printf("ES(%d + %d)\n", pop_size, child_pop_size);
    } else {
      printf("ES(%d , %d)\n", pop_size, child_pop_size);
    }

    printf("\tSigma: %f\n", sigma);
    printf("\tCrossover probability: %f\n", xover_prob);
    printf("\tMutate probability: %f\n", mutate_prob);
    printf("\tTournament size: %d\n", tourney_size);
  }
};

#endif  // SIMULATION_INCLUDE_PARAM_H_
