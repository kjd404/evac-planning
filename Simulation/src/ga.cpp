// Copyright 2017 <University of Idaho>
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include "ga.h"

void run_ga(int ga_code, int iterations, int print_interval,
	     int runs, int population) {
  switch (ga_code) {
  case 0:
    generational(iterations, print_interval, population);
    return;
  case 1:
    evolution_strategy(iterations,
		       population,
		       runs,
		       params.get_child_pop_size(),
		       print_interval);
    return;
  case 2:
    probability_init_safety_to_danger(iterations,
				      params.get_pop_size(),
				      params.get_child_pop_size(),
				      print_interval);
    return;
  case 3:
    apply_dijkstra_algorithm();
    return;
  default:
    printf("No legal GA specified. Please try again.\n");
    return;
  }
}

/** This function is really deprecated. Try to use it at your own risk. 
 *  The EA used currently (Mar-2017) is evolution_strategy(...), below.
 */
void generational(int iterations, int print_interval, int population_size) {
  // Initialize the population, get fitness of individuals.
  Population pop_one = Population(population_size);
  Population pop_two = Population(population_size);

  // Initialize probability populations.
  for (int i = 0; i < population_size; i++) {
    Chromosome ind(get_random_probabilities(theCity->get_nodes().size(),
					      theCity->get_degree(),
					      theCity->get_nodes()));
    pop_one.add_chromosome(fitness(&ind), ind);
    pop_two.add_chromosome(fitness(&ind), ind);
  }

  Chromosome x_1(pop_one.get_best().second.get_data());
  Chromosome x_2(pop_one.get_best().second.get_data());
  Chromosome tmp(pop_one.get_best().second.get_data());
  std::pair<float, Chromosome> tmp_pair1(0.0, x_1);
  std::pair<float, Chromosome> tmp_pair2(0.0, x_2);

  for (int curr_iter = 0; curr_iter < iterations; curr_iter++) {
    // Copy the population over using tournament selection
    // Tournament size guarantees elitism of size theCity->tourney_size() - 1
    for (int j = 2; j < population_size; j += 2) {
      tmp_pair1 = pop_one.select(params.get_tourney_size());
      x_1 = tmp_pair1.second;
      tmp_pair2 = pop_one.select(params.get_tourney_size());
      x_2 = tmp_pair2.second;

      if (choose(params.get_xover_prob())) {
	Chromosome tmp = x_1;
	x_1 = x_1.cross(x_2);
	x_2 = x_2.cross(tmp);
      }

      x_1 = x_1.mutate();
      x_2 = x_2.mutate();

      tmp_pair1.first = fitness(&x_1);
      tmp_pair1.second = x_1;
      tmp_pair2.first = fitness(&x_2);
      tmp_pair2.second = x_2;

      pop_two.insert(params.get_tourney_size(), tmp_pair1);
      pop_two.insert(params.get_tourney_size(), tmp_pair2);
    }

    pop_one = pop_two;

    if (curr_iter % print_interval == 0) {
      std::pair<float, Chromosome> p = pop_one.get_best();
      float f = fitness(&p.second);
      f = (f + p.first) / 2.0;
      printf("*******************************\n");
      printf("Best Fitness on iteration %d: %f\n", curr_iter, f);
      theCity->set_nodes(p.second.get_data());
      theCity->print_nodes();
      theCity->print_simulation();
      printf("*******************************\n");
    }
  }

  printf("Pop1.size: %lu, Pop2.size: %lu\n", pop_one.get_population().size(),
	  pop_two.get_population().size());

  tmp_pair1 = pop_one.get_best();
  printf("Best fitness: %f\n", tmp_pair1.first);
  theCity->set_nodes(tmp_pair1.second.get_data());
  theCity->print_city();
  pop_one.print_fitnesses();
}

/** This is the current (Mar-2017) EA being used. An Evolution Strategy (ES)
 *
 * @param iterations - the number of generations to run the algorithm
 * @param population - the size of the parent population
 * @param runs - the number of times to re-run the ES algorithm
 * @param child_population - the number of children to generate from parents pop
 * @param print_interval - the interval on which data is output (of iterations)
 * @author Keith Drew
 */
void evolution_strategy(int iterations, int population, int runs,
			 int child_population, int print_interval) {
  // Allocate the population of individuals, genotypes, whichever.
  Population pop = Population(population);

  // Print header
  print_header();

  // Make sure fitness is calculated for all predefined probabilities
  // Prevents re-calculation for successive iterations of the "run"
  // loop below.
  for (auto& c : predefined_probabilities) {
    (void)fitness(&c);
  }

  // Run the experiment "runs" times.
  // TODO(Keith) Reload probabilities from previous runs?
  for (int r = 0; r < runs; r++) {
    // get predefined probabilities, if any.
    for (auto c : predefined_probabilities) {
      if (pop.current_size() < population) {
	pop.add_chromosome(c.get_fitness(), c);
      }
    }

    // Initialize the remaining population space with random genotypes
    while (pop.current_size() < population) {
      Chromosome ind(get_random_probabilities(theCity->get_nodes().size(),
						theCity->get_degree(),
						theCity->get_nodes()));
      // Calculate fitness of each new, random, individual
      pop.add_chromosome(fitness(&ind), ind);
    }

    int curr_iter = 0;
    // generations loop - terminates on iterations limit or max fitness (1.0)
    for (curr_iter = 0; curr_iter < iterations &&
	   pop.get_best().first < 1.0; curr_iter++) {
      // children vector
      std::vector<std::pair<float, Chromosome>> children;

      // create specified number of children from parent population
      for (int i = 0; i < child_population; i++) {
	// Select parent using tournament selection
	std::pair<float, Chromosome> child = pop.select(params.get_tourney_size());

	// Chance to crossover with a second parent, chosen with tournament
	if (choose(params.get_xover_prob())) {
	  child.second =
	    child.second.cross(pop.select(params.get_tourney_size()).second);
	}

	// Mutate the new child
	child.second = child.second.mutate();

	// Evaluate child's fitness
	child.first = fitness(&child.second);

	// Place child into children population
	children.push_back(child);
      }

      // ES '+' operator is designated
      if (params.get_evo_strat() == 0) {
	// add all children to total population
	for (auto c : children) {
	  pop.add_chromosome(c.first, c.second);
	}

	// cull the population of the worst fitnesses.
	pop.cull();
      } else if (params.get_evo_strat() == 1) {
	// ES ',' operator is designated
	// Clear all the parents from population
	pop.clear();

	// Add all the children to the population
	for (auto c : children) {
	  pop.add_chromosome(c.first, c.second);
	}

	// Force competetion between children for best performers
	pop.cull();
      }

      // Clear the children vector.
      children.clear();

      // Print data regularly, every interval.
      if (curr_iter % print_interval == 0 && print_interval != iterations) {
	write_curr_data(pop.get_best(), r, curr_iter, iterations);
      }
    }

    write_curr_data(pop.get_best(), r, curr_iter, iterations);

    // Write the drawable city out, after EA is completed.
    theCity->output_drawable();

    // if true, write whole population to file, else just best
    if (true) {
      write_best_probs(pop.get_vector());
    } else {
      write_best_probs(pop.vector_best());
    }

    pop.clear();
  }
}

void output_stats(std::vector<int> gens_vec,
		   std::vector<float> fit_vec, int r) {
  // get averages
  float gen_avg = average_generations(gens_vec, r);
  float fit_avg = average_fitness(fit_vec, r);
  float gen_sum = 0.0, fit_sum = 0.0;

  // get stddev for gens
  for (auto i : gens_vec) {
    gen_sum += pow(static_cast<float>(i) - gen_avg, 2);
  }
  float gen_std_dev = sqrt(gen_sum / static_cast<float>(r));

  // get stddev for fitnesses
  for (auto f : fit_vec) {
    fit_sum += pow(f - fit_avg, 2);
  }
  float fit_std_dev = sqrt(fit_sum / static_cast<float>(r));

  // get min maxes
  std::pair<int, int> p = get_gens_min_max(gens_vec, r);
  std::pair<float, float> p2 = get_fit_min_max(fit_vec, r);

  // output
  printf("Average gens: %g\nStandard Deviation: %g\n", gen_avg, gen_std_dev);
  printf("Min gens %d\nMax gens: %d\n", p.first, p.second);
  printf("Average fitness: %g\nFitness Standard Deviation: %g\n",
	 fit_avg, fit_std_dev);
  printf("Min fitness %g\nMax fitness: %g\n", p2.first, p2.second);
}

std::pair<int, int> get_gens_min_max(std::vector<int> gens_vec, int r) {
  int min = r, max = 0;

  for (auto i : gens_vec) {
    if (i < min) min = i;

    if (i > max) max = i;
  }

  std::pair<int, int> p;
  p.first = min;
  p.second = max;

  return p;
}

std::pair<float, float> get_fit_min_max(std::vector<float> fit_vec, int r) {
  float min = 1.0, max = 0.0;

  for (auto f : fit_vec) {
    if (f < min) min = f;

    if (f > max) max = f;
  }

  std::pair<float, float> p;
  p.first = min;
  p.second = max;

  return p;
}

float average_generations(std::vector<int> gens_vec, int r) {
  int sum_gens = 0;

  for (auto i : gens_vec) {
    sum_gens += i;
  }

  return static_cast<float>(sum_gens) / static_cast<float>(r);
}

float average_fitness(std::vector<float> fit_vec, int r) {
  float sum_fit = 0.0;

  for (auto f : fit_vec) {
    sum_fit += f;
  }

  return sum_fit / static_cast<float>(r);
}

/** The fitness function currently used (Mar-2017)
 * Takes a chromosome and returns the fitness of the individual.
 */
float fitness(Chromosome *c) {
  // Reset agents to their starts, specified in City::init_agents
  theCity->reset_agents();
  // Initializes edges, resets old traffic counters
  theCity->initialize_edges();
  // Loads the genotype into the city for simulation.
  theCity->set_nodes(c->get_data());

  // Simulation using c's data. Returns fitness score.
  c->set_fitness(theCity->simulate_for_safety());
  
  return c->get_fitness();
}

void initialization_fitness(Chromosome *c, int agent_set) {
  // Initializes agents to locations specified in agent set specified
  theCity->set_agents(agent_set);

  // Initializes edges, resets old traffic counters
  theCity->initialize_edges();

  // Loads the genotype into the city object for simulation
  theCity->set_nodes(c->get_data());

  // Evaluates fitness of genotype
  float fitness_value = theCity->simulate_for_safety();

  // Stores the fitness value in the chromosome
  c->set_fitness(fitness_value);
}

std::vector<std::vector<float> > get_random_probabilities(
				 int num_nodes, int max_degree,
				 std::vector<std::shared_ptr<Node> > nodes) {
  std::vector< std::vector<float> > r_probs(num_nodes,
					    std::vector<float>(0, 0));
  int index = 0;

  // Initialize each vector in r_probs
  for (auto& v : r_probs) {
    // Get the number of edges this node has in the actual city
    // topology, for accurate probs...
    // All edge probabilities should sum to one.
    int num_edges = nodes.at(index)->get_prob().size();

    float sum = 0.0;
    // Initialize all values to sum to 1.
    // Should produce some interesting results.
    for (int i = 0; i < num_edges; i++) {
      v.push_back(randUnit());
      sum += v.at(i);
    }

    for (int i = 0; i < num_edges; i++) {
      v.at(i) /= sum;
    }

    index++;
  }

  return r_probs;
}

void simulate_from_file(char *filename) {
  // Should just fix the lexer to read strings better...
  std::string fname = "sims/";
  fname.append(filename);
  fname.append(".txt");
  std::cout << fname << std::endl;
  std::ifstream file;
  file.open(fname.c_str());

  if (!file.is_open()) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  int num_nodes, num_probs;
  float prob;
  file >> num_nodes;
  std::vector< std::vector<float> > prob_set;

  for (int i = 0; i < num_nodes && file >> num_probs; i++) {
    std::vector<float> p_set;

    for (int j = 0; j < num_probs && file >> prob; j++) {
      p_set.push_back(prob);
    }
    prob_set.push_back(p_set);
  }
  file.close();

  Chromosome c(prob_set);
  c.print_chromosome();

  float f = fitness(&c);
  theCity->print_nodes();
  theCity->print_simulation();
  printf("Fitness of simulation: %f\n", f);
}

void exhaustive_search() {
  int min_percent = 0;
  int percent_bound = 101;
  float p = 1.0;
  std::vector< std::vector< std::vector<float> > > tests;
  std::vector<float> final_p_set;
  final_p_set.push_back(p);

  for (int x = min_percent; x < percent_bound; x++) {
    for (int y = min_percent; y < percent_bound; y++) {
      std::vector< std::vector<float> > node_set;
      std::vector<float> p_set;

      // Create probs for first node
      float p1 = static_cast<float>(x) / 100.0;
      p_set.push_back(p - p1);
      p_set.push_back(p1);
      node_set.push_back(p_set);

      std::vector<float> p_set2;
      // Create probs for second node
      float p2 = static_cast<float>(y) / 100.0;
      p_set2.push_back(p - p2);
      p_set2.push_back(p2);
      node_set.push_back(p_set2);

      node_set.push_back(final_p_set);

      tests.push_back(node_set);
    }
  }

  std::ofstream of;
  of.open("exh_avg_10.dat");

  float num_evals = 10.0;
  float f = 0.0;

  if (of.is_open()) {
    for (auto prob_set : tests) {
      Chromosome c(prob_set);

      f = 0.0;
      for (int i = 0; i < num_evals; i++) {
	f = f + fitness(&c);
      }

      f = f / num_evals;

      of << prob_set[0][1] << " ";
      of << prob_set[1][1] << " ";
      of << f << std::endl;
    }
    of.close();
  } else {
    printf("Couldn't open output file for exhaustive search output\n");
  }
}

void read_probs(char *filename) {
  std::ifstream file;
  file.open(filename);

  std::cout << filename << std::endl;
  if (!file.is_open()) {
    printf("Problem reading probability file. File %s does not exist.\n",
	   filename);

    return;
  }

  int num_sets, num_nodes, num_probs;
  float prob;
  file >> num_sets;

  for (int set = 0; set < num_sets; set++) {
    file >> num_nodes;
    std::vector< std::vector<float> > prob_set;

    for (int i = 0; i < num_nodes && file >> num_probs; i++) {
      std::vector<float> p_set;

      for (int j = 0; j < num_probs && file >> prob; j++) {
	p_set.push_back(prob);
      }
      prob_set.push_back(p_set);
    }

    Chromosome c(prob_set);

    predefined_probabilities.push_back(c);
  }

  file.close();
}

/** Prints header line. This servers as labels for data written
 *  out from ga::write_best_probs()
 */
void print_header() {
  printf("testName run time fitness gens maxGens ");
  printf("popSize cPopSize agents groupSize ");
  printf("e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 e10\n");
}

void write_best_probs(std::vector<Chromosome> pop) {
  FILE *out;
  std::string fname = theCity->get_name();
  fname.append("ProbSet");
  out = fopen(fname.c_str(), "w");

  fprintf(out, "%lu\n", pop.size());
  for (auto c : pop) {
    std::vector<std::vector<float> > p = c.get_data();

    fprintf(out, "%lu\n", p.size());
    for (auto n : p) {
      fprintf(out, "%lu", n.size());
      for (auto f : n) {
	fprintf(out, " %f", f);
      }
      fprintf(out, "\n");
    }
  }

  fclose(out);
}

void thread_wrapper(std::vector<std::pair<float, Chromosome> > *children,
		     City city_copy) {
  int num_children = children->size();
  int num_threads = num_children - 1;
  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(thread_fitness,
				  &children->at(i).second,
				  city_copy,
				  i));
  }

  thread_fitness(&children->back().second, city_copy, INT_MAX);
  children->back().first = children->back().second.get_fitness();

  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }

  for (int i = 0; i < num_threads; i++) {
    children->at(i).first = children->at(i).second.get_fitness();
  }
}

void thread_fitness(Chromosome *c, City city_copy, int pid) {
  city_copy.reset_agents();
  city_copy.initialize_edges();
  city_copy.set_nodes(c->get_data());

  float f = city_copy.simulate_for_safety();

  c->set_fitness(f);
}

/** A helper used to write data to stdout for processing.
 */
void write_curr_data(std::pair<float, Chromosome> p,
		     int run, int curr_gen, int max_gens) {
  theCity->set_nodes(p.second.get_data());
  (void)fitness(&p.second);

  std::vector<float> safety_over_time = theCity->get_safety_over_time();

  printf("%s ", theCity->get_name().c_str());
  printf("%d ", run);
  printf("%f ", theCity->sim_time());
  printf("%f ", p.first);
  printf("%d ", curr_gen);
  printf("%d ", max_gens);
  printf("%d ", params.get_pop_size());
  printf("%d ", params.get_child_pop_size());
  printf("%d ", theCity->num_agents());
  printf("%d ", theCity->agent_group_size());
  for (auto f : safety_over_time) {
    printf("%g ", f);
  }
  printf("%g\n", p.first);
}

/** A variation of the ES algorithm, used to specifically initialize
 * sets of probabilities based on locations of safety in the network.
 */
void probability_init_safety_to_danger(int iterations, int population,
				       int child_population,
				       int print_interval) {
  int num_agent_sets = 0;
  if (!theCity->agent_sets_initialized()) {
    printf("Agent starting locations uninitialized. ");
    printf("Run SLang(agent sets) before probability initialization\n");
    return;
  } else {
    // Get the number of agent sets, ie the number of agent initializations
    num_agent_sets = theCity->num_agent_sets();
  }

  // Allocate population of individuals
  Population pop = Population(population);

  // Create random genotypes.
  while (pop.current_size() < population) {
    Chromosome individual(get_random_probabilities(theCity->get_nodes().size(),
						   theCity->get_degree(),
						   theCity->get_nodes()));
    // Calculate individual's fitness, start agents far from safety.
    initialization_fitness(&individual, theCity->num_agent_sets() - 1);

    // Add individual into population
    pop.add_chromosome(individual.get_fitness(), individual);
  }

  // Print header
  printf("Safety-to-danger initialization:\n");
  print_header();

  // Optimize individuals for each agent starting location set.
  for (int set = 0; set < num_agent_sets; set++) {
    int tournament_size = params.get_tourney_size();
    int curr_iter = 0;
    for (curr_iter = 0; curr_iter < iterations; curr_iter++ ) {
      // Create children vector locally
      std::vector<std::pair<float, Chromosome>> children;

      for (int i = 0; i < child_population; i++) {
	// Create mu children from selected parents
	std::pair<float, Chromosome> child = pop.select(tournament_size);

	// Check and perform crossover
	if (choose(params.get_xover_prob())) {
	  child.second =
	    child.second.cross(pop.select(tournament_size).second);
	}

	// Mutate new child
	child.second = child.second.mutate();

	// Evaluate child's fitness
	initialization_fitness(&child.second, set);
	child.first = child.second.get_fitness();

	// Place child into children population
	children.push_back(child);
      }

      // ES+ is evo_strat = 0, ES, is evo_strat = 1, else fail.
      if (params.get_evo_strat() == 0) {
	// Add children to parent population, to compete against parents
	for (auto c : children) {
	  pop.add_chromosome(c.first, c.second);
	}
      } else if (params.get_evo_strat() == 1) {
	// Clear all parents from the population
	pop.clear();

	// Add all children to the parent population
	for (auto c : children) {
	  pop.add_chromosome(c.first, c.second);
	}
      } else {
	printf("Evolution strategy invalid. Should be ES+ or ES,\n");
	printf("Fix error in SLang input, try again. Exiting...\n");
	exit(1);
      }

      // Force competition, keep best lambda individuals
      pop.cull();

      // Clear the children vector
      children.clear();

      // Print data each specified interval
      // if (curr_iter % print_interval == 0 && print_interval != iterations) {
	// write_curr_data(pop.get_best(), set, curr_iter, iterations);
      // }
    }

    // Re-seeds the city for a fitness run with the best indidual from this
    // generation, for output.
    if (true) {
      std::pair<float, Chromosome> p = pop.get_best();
      initialization_fitness(&p.second, set);

      for (auto agent : theCity->get_agent_vector()) {
	std::vector<int> route = agent.get_collapsed_route();
	printf("Set %d | Route start and end: %d %d\n", set,
	       route.front(), route.back());
      }
    }

    //write_curr_data(pop.get_best(), set, curr_iter, iterations);
  }

  // Write out a probabilities file for use in a following evolution run.
  write_best_probs(pop.get_vector());
}

/******************************************************************************
 * Start of portion for Dijkstra's algorithm
 ******************************************************************************/
void addParentToRoute(std::shared_ptr<Node> child,
                      std::map<std::shared_ptr<Node>,std::shared_ptr<Node>> parents,
                      std::vector<std::shared_ptr<Node>> &routes) {
    auto itParent = parents.find(child);
    if (itParent->second == NULL) {
        return;
    } else {
        addParentToRoute(itParent->second, parents, routes);
        routes.push_back(itParent->second);
    }
    return;
}

std::shared_ptr<Edge> getEdgeConnectingFromAndTo(std::shared_ptr<Node> from,
                                                 std::shared_ptr<Node> to) {
    for (auto ep : from->get_prob()) {
        std::shared_ptr<Edge> e = ep.first;
        if (e->get_to() == to) {
            return e;
        }
    }
    return NULL;
}

std::vector<Agent> getAgentsVector(std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agentsQueue) {
    std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agents_tmp = agentsQueue;

    // Create the vector object
    std::vector<Agent> agent_vector;

    // Push agents into the vector, pop them from the priority queue
    while (agents_tmp.size() > 0) {
        agent_vector.push_back(agents_tmp.top());
        agents_tmp.pop();
    }

    return agent_vector;
}

float getSumSafety(std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agentsQueue) {
    float total_safety = 0.0;
    std::vector<Agent> agent_vector = getAgentsVector(agentsQueue);
    for (auto a : agent_vector) {
        total_safety += a.get_curr_safety();
    }
    return total_safety;
}

/*
 * Dijkstra's algorithm from start node to destination node
 */
void dijkstra_algorithm(std::shared_ptr<Node> startNode, std::vector<std::shared_ptr<Node>> &routes) {
    std::shared_ptr<Node> destinationNode = NULL;
    
    std::vector<std::shared_ptr<Node> > nodes = theCity->get_nodes();
    double inf = std::numeric_limits<double>::infinity();
    
    // set to keep track of nodes included in shortest path tree
    std::set<std::shared_ptr<Node>> sptSet;
    // set to keep track of not yet included in shortest path tree
    std::set<std::shared_ptr<Node>> notVisitedSet;
    // pair of child and parent
    std::map<std::shared_ptr<Node>, std::shared_ptr<Node>> parents;
    
    // initialize nodes with weight, 0 for start node and inf for others
    std::map<std::shared_ptr<Node>, float> nodesWithWeight;
    for (int i = 0; i < nodes.size(); i++) {
        if (i == startNode->get_id()) {
            nodesWithWeight.insert(std::pair<std::shared_ptr<Node>, float>
                                   (nodes.at(i), 0.0));  // initialize weight of start node to 0
        } else {
            nodesWithWeight.insert(std::pair<std::shared_ptr<Node>, float>
                                   (nodes.at(i), inf));  // initialize weight of all nodes (except start node) to infinity
        }
        notVisitedSet.insert(nodes.at(i));
        parents.insert(std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>
                       (nodes.at(i), NULL));
    }
    
    while (sptSet.size() < nodes.size()) {
        std::shared_ptr<Node> minNode;
        float minNodeWeight = inf;
        for (auto n : notVisitedSet) {
            auto it = nodesWithWeight.find(n);
            if (it->second < minNodeWeight) {
                minNode = it->first;
                minNodeWeight = it->second;
            }
        }
        sptSet.insert(minNode);
        notVisitedSet.erase(minNode);
        
        double edgeWeight;
        for (auto ep : minNode->get_prob()) {
            std::shared_ptr<Edge> e = ep.first;
            // use total time instead of freeflow time
            //edgeWeight = e->get_freeflow();
            edgeWeight = e->time();
            // printf("dijkstra total time: %f\n", edgeWeight);
            // printf("dijkstra freeflow time: %f\n", e->get_freeflow());
            auto it = nodesWithWeight.find(e->get_to());
            auto itParent = parents.find(e->get_to());
            if ((minNodeWeight+edgeWeight) < (it->second)) {
                it->second = minNodeWeight+edgeWeight;
                itParent->second = minNode;
            }
        }
        // set destination to nearest safe node
        if (destinationNode == NULL && minNode->get_safety() == 1.0) {
            destinationNode = minNode;
        }
    }
    
    routes.clear();
    addParentToRoute(destinationNode, parents, routes);
    routes.push_back(destinationNode);
    
    // print route
    printf("Route: ");
    for (auto r : routes) {
        printf("%d ", r->get_id());
    }
    printf("\n");
}

std::shared_ptr<Edge> getNextEdge(std::shared_ptr<Node> currentNode) {
    std::vector<std::shared_ptr<Node>> routes;
    dijkstra_algorithm(currentNode, routes);
    
    for (int i = 0; i < routes.size(); i++) {
        if(routes.at(i)->get_id() == currentNode->get_id()) {
            if(i < routes.size()-1) {
                return getEdgeConnectingFromAndTo(routes.at(i), routes.at(i+1));
            } else {
                return getEdgeConnectingFromAndTo(routes.at(i), routes.at(i));
            }
        }
    }
    
    return NULL;
}

void outputDrawable(std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agents) {
    // Build output filename.
    std::string filename = "outputs/";
    filename.append(theCity->get_name());
    filename.append("Dijkstra.txt");
    
    // Get a file handle
    std::ofstream drawable;
    
    // Open the file
    drawable.open(filename);
    
    // If the was opened, write the drawable info out.
    if (drawable.is_open()) {
        // Output drawable edge data.
        for (auto e : theCity->get_edges()) {
            drawable << "e ";
            drawable << e->get_id() << " ";
            drawable << e->get_from()->get_id() << " ";
            drawable << e->get_to()->get_id() << " ";
            drawable << e->get_safety() << std::endl;
        }
        
        // Output drawable node data.
        for (auto n : theCity->get_nodes()) {
            drawable << "n ";
            drawable << n->get_id() << " ";
            drawable << n->get_capacity() << " ";
            drawable << n->get_safety() << " ";
            drawable << n->get_longitude() << " ";
            drawable << n->get_latitude() << std::endl;
            
            std::map<std::shared_ptr<Edge>, float> probs = n->get_prob();
            for (auto it = probs.begin(); it != probs.end(); it++) {
                drawable << "p ";
                drawable << it->first->get_id() << " ";
                drawable << it->second << std::endl;
            }
        }
        
        // Get agents.
        std::vector<Agent> copy = getAgentsVector(agents);
        
        // Output drawable agent data.
        for (auto agent : copy) {
            drawable << "a ";
            drawable << agent.get_id();
            for (auto i : agent.get_route()) {
                drawable << " " << i;
            }
            drawable << std::endl;
        }
        drawable.close();
    } else {
        printf("Couldn't write to %s\n", filename.c_str());
    }
}

// simulation for dijkstra's algorithm
void simulate_for_dijkstra() {
    float curr_time = 0.0, t = 0.0, epoch = theCity->sim_time() / 10.0;
    float next_time = epoch;
    Agent curr_agent;
    std::shared_ptr<Node> curr_node;
    std::shared_ptr<Edge> next_edge;
    
    theCity->get_safety_over_time().clear();
    
    std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agents_copy = theCity->get_agents();
    if (agents_copy.size() == 0) {
        printf("Agent priority queue uninitialized. Exiting...\n");
        exit(1);
    }
    // Simulation loop - runs until the next agent to be processed arrives
    // after the allowed simulation time (theCity->sim_hours)
    while (curr_time < theCity->sim_time()) {
        if (next_time - curr_time <= 0.0) {
            next_time += epoch;
            theCity->get_safety_over_time().push_back(getSumSafety(agents_copy) / agents_copy.size());
        }
        // Get and remove the next agent to be processed from the priority queue
        curr_agent = agents_copy.top();
        agents_copy.pop();
        
        // Update time to the next agents arrival time
        curr_time = curr_agent.get_next_time();
        
        // Make sure we are not running over the simulation time
        if (curr_time >= theCity->sim_time()) {
            //theCity->get_agents().push(curr_agent);
            agents_copy.push(curr_agent);
            break;
        }
        
        // Get the node the agent is arriving at and add it to the agent's list
        curr_node = curr_agent.get_to();
        curr_agent.add_to_route(curr_node->get_id());
        
        // Select next edge the agent will travel on, according to dijkstra's algorithm
        next_edge = getNextEdge(curr_node);
        
        //////////////////////////////////////
        std::map<std::shared_ptr<Edge>, float> prob_copy = curr_node->get_prob();
        prob_copy[next_edge] = prob_copy[next_edge] + 1.0;
        std::vector<float> values_copy;
        for (auto ep : prob_copy) {
            values_copy.push_back(ep.second);
         }
        curr_node->set_probs(values_copy);
        //////////////////////////////////////
        
        // Traffic is backed up - set agent to wait and continue.
        if (next_edge == NULL) {
            float wait_time = curr_node->get_wait_time();
            
            curr_agent.inc_transit_time(wait_time);
            curr_agent.set_time(curr_time + wait_time);
            agents_copy.push(curr_agent);
        } else {
            // Remove counter from edge agent is leaving
            if (curr_agent.get_edge() != NULL) {
                curr_agent.get_edge()->dec_c(curr_agent.get_member_count());
            }
            
            // Set this node as the agent's last node
            curr_agent.set_from(curr_node);
            //curr_agent.set_from(next_edge->get_from()); // used next_edge->get_from()
            
            // Set the agents next edge
            curr_agent.set_edge(next_edge);
            
            // Increase edge count by members in agent.
            next_edge->inc_c(curr_agent.get_member_count());
            
            // Set the agents next node.
            curr_agent.set_to(next_edge->get_to());
            
            // Check if the agent is using a node's self edge
            if (next_edge->get_from()->get_id() == next_edge->get_to()->get_id()) {
                // Get the node's wait time
                t = curr_node->get_wait_time();
                
                if (next_edge->get_safety() == 1.0) { // used next_edge->get_to()->get_safety() instead of next_edge->get_safety()
                    t = theCity->sim_time();
                }
            } else {
                // Get the link travel time.
                t = next_edge->time();
                //t = next_edge->get_freeflow();
                // printf("total time: %f\n", t);
                // printf("freeflow time: %f\n", next_edge->get_freeflow());
            }
            
            // Increment the agent's total transit time.
            curr_agent.inc_transit_time(t);
            
            // Set the arrival time of the agent
            curr_agent.set_time(curr_time + t);
            
            // Push the agent back onto the priority queue
            agents_copy.push(curr_agent);
            //curr_agent.print_agent();
        }
    }
    // Calculate the sum of safety across all agents
    float total_safety = getSumSafety(agents_copy);
    theCity->get_safety_over_time().push_back(total_safety / agents_copy.size());
    printf("safety_over_time: %f\n", total_safety / agents_copy.size());
    
    ///////////////////////////////////////////////////////
    std::map<std::shared_ptr<Node>, float> mapTotalValue;
    float sum = 0.0;
    std::vector<float> probValues;
    for (auto n : theCity->get_nodes()) {
        // printf("NODE: %d\n", n->get_id());
        sum = 0.0;
        for (auto ep : n->get_prob()) {
            sum += ep.second;
            // printf("PROB: %d, %f\n", ep.first->get_id(), ep.second);
        }
        mapTotalValue.insert(std::pair<std::shared_ptr<Node>, float> (n, sum));
        //printf("total for node: %f\n", sum);
        
        probValues.clear();
        for (auto ep : n->get_prob()) {
            if(mapTotalValue[n] != 0.0) {
                probValues.push_back(ep.second/mapTotalValue[n]);
            } else {
                probValues.push_back(ep.second/1.0);
            }
        }
        n->set_probs(probValues);
        
        // print probs after actual probabilities just for test
        /*for (auto ep : n->get_prob()) {
            printf("PROB2: %d, %f\n", ep.first->get_id(), ep.second);
        }*/
    }
    
    // print map value just for test
    /*for (auto iterator = mapTotalValue.begin(); iterator != mapTotalValue.end(); iterator++) {
        printf("Node: %d totalValue: %f\n", iterator->first->get_id(), iterator->second);
    }*/
    
    outputDrawable(agents_copy);
    ///////////////////////////////////////////////////////
}

void apply_dijkstra_algorithm() {
    // printf("start of dijkstra's algorithm\n");
    theCity->reset_agents();
    theCity->initialize_edges();
    simulate_for_dijkstra();
}
/******************************************************************************
 * End of portion for Dijkstra's algorithm
 ******************************************************************************/
