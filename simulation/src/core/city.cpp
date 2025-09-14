// Copyright 2017 <University of Idaho>
#include <deque>
#include <string>
#include <memory>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <set>
#include "city.h"

/** The city object constructor.
 * String is the city name, number of nodes for the graph representation
 * of the city, degree is the maximum degree of the city, representing
 * the maximum number of edges leaving a city.
 */
City::City(std::string name, int num_nodes = 0, int degree = 0) {
  this->name = name;
  this->num_nodes = num_nodes;
  this->nodes = std::vector<std::shared_ptr<Node> >();

  if (degree == 0) {
    printf("City::City degree defined as zero. A city with no roads");
    printf(" seems pretty useless, doesn't it? See SLang specification.\n");
    exit(1);
  }

  // Create initial node objects.
  for (int i = 0; i < num_nodes; i++) {
    nodes.push_back(std::make_shared<Node>());
  }

  this->edges = std::vector<std::shared_ptr<Edge> >();
  this->degree = degree;
}

/** Returns a vector of all agents from the priority queue used in the last
 * simulation. Used to analyze or inspect agent behavior more easily than 
 * using the priority queue object.
 *
 * This function is necessary for retrieving a data structure that can be
 * iterated over easily. Priority queues cannot be iterated on because doing
 * so is error prone, as a result of user-defined comparison operators and
 * the potential destruction of the order of the data structure. 
 */
std::vector<Agent> City::get_agent_vector() {
  // Copy the agents priority queue.
  std::priority_queue<Agent, std::deque<Agent>, Agent::cmpSoonest> agents_copy;
  agents_copy = this->agents;

  // Create the vector object
  std::vector<Agent> agent_vector;

  // Push agents into the vector, pop them from the priority queue
  while (agents_copy.size() > 0) {
    agent_vector.push_back(agents_copy.top());
    agents_copy.pop();
  }

  return agent_vector;
}

/** Calculates fitness by summing safety of all agents, and dividing
 * the sum by the number of agents.  
 */
float City::get_fitness() {
  float total_fitness = 0.0;
  std::vector<Agent> agent_vector = get_agent_vector();

  for (auto agent : agent_vector) {
    total_fitness += agent.get_safety();
  }

  return total_fitness / static_cast<float>(agents.size());
}

/** Simply checks to see if the agent_start_sets object has been
 * initialized.
 */
bool City::agent_sets_initialized() {
  if (agent_start_sets.empty()) {
    return false;
  } else {
    return true;
  }
}

/** Calls print_node on all nodes in the city.
 */
void City::print_nodes() {
  printf("NODES:\n");
  for (auto iterator = nodes.begin(); iterator != nodes.end(); iterator++) {
    iterator->get()->print_node();
  }
}

/** Calls print_edge on all edges in the city.
 */
void City::print_edges() {
  printf("EDGES:\n");
  for (auto iterator = edges.begin(); iterator != edges.end(); iterator++) {
    if (iterator->get() != nullptr) {
      iterator->get()->print_edge();
    }
  }
}

/** Prints the city data and all nodes and edges in the city.
 */
void City::print_city() {
  printf("CITY: %s, %d, %d\n", get_name().c_str(),
	 static_cast<int>(get_nodes().size()), get_degree());
  print_nodes();
  print_edges();
}

/** Prints all agents in the priority queue.
 */
void City::print_agents(std::priority_queue<Agent,
			std::deque<Agent>, Agent::cmpSoonest> agents_copy) {
  std::vector<Agent> copy;

  // Copy priority queue into vector for printing
  while (agents_copy.size() > 0) {
    copy.push_back(agents_copy.top());
    agents_copy.pop();
  }

  // Print agents
  for (auto a : copy) {
    a.print_agent();
  }
}

/** (Re)Initializes the priority queue with agents at locations from
 * the agent set specified. 
 */
void City::set_agents(int agent_set) {
  // Check bounds of agent_set argument for validity.
  if (agent_start_sets.empty()) {
    printf("City::set_agents agent set uninitialized - rectify SLang\n");
    exit(1);
  } else if (agent_set < 0 || agent_set > num_agent_sets()) {
    printf("City::set_agents argument invalid\n");
    printf("Attempted to initialize agents with set out of bounds.");
    exit(1);
  }

  // Remove previous agents from priority queue, if any.
  while (!agents.empty()) {
    agents.pop();
  }

  // Specify constructor arguments - number of individuals,
  // agent_start_time, AKA arrival_time
  int num_ind = 1;
  float agent_start_time = 0.0;

  // Add new agents to priority queue from specified set
  for (auto i : agent_start_sets.at(agent_set)) {
    // Presumably need more than 1 agent at each spot. Try 10
    for (int j = 0; j < 10; j++) {
      // Create a new agent at the indicated node (i)
      Agent new_agent = Agent(num_ind, agent_start_time, nodes.at(i),
			      nodes.at(i), NULL);
      agents.push(new_agent);
    }
  }
}

/** Resets agents in the priority queue to their starting locations.
 */
void City::reset_agents() {
  // Clear priority queue
  while (!agents.empty()) {
    agents.pop();
  }

  // Push initialization agent set into priority queue
  for (auto a : init_agents) {
    agents.push(a);
  }
}

/** Prints the city in drawable format. Needs continual maintenance
 * as the project moves forward, new features are added, new data
 * maintained about the city. 
 *
 * Should produce identical output to output_drawable.
 */ 
void City::print_drawable() {
  for (auto e : edges) {
    // ID, FromID, ToID, cmax, bcoeff, powcoeff, safety
    printf("EDGE: %d, %d, %d, %f, %f, %f, %f\n",
	   e->get_id(), e->get_from()->get_id(),
	   e->get_to()->get_id(), e->get_cmax(),
	   e->get_bcoeff(), e->get_powcoeff(), e->get_safety());
  }
  for (auto n : nodes) {
    // ID, Capacity, wait_time, safety, longitude (x), latitude (y)
    printf("NODE: %d, %d, %f, %f, %f, %f\n",
	   n->get_id(), n->get_capacity(),
	   n->get_wait_time(), n->get_safety(),
	   n->get_longitude(), n->get_latitude());

    for (auto ep : n->get_prob()) {
      // Edge ID, probability
      printf("PROB: %d, %f\n",
	     ep.first->get_id(), ep.second);
    }
  }
  for (auto a : init_agents) {
    // ID, ToID, FromID
    printf("AGNT: %d, %d, %d\n",
	   a.get_id(), a.get_to()->get_id(), a.get_from()->get_id());
  }
}

/** Outputs to a file a drawable version of the city. Should be seeded
 * by running some simulation first, so probabilities are available.
 * For use with Homaja's drawing program, output specified for reading
 * by that software.
 */ 
void City::output_drawable() {
  // Build output filename (supports optional EVAC_OUTPUT_DIR override)
  const char* outdir_env = getenv("EVAC_OUTPUT_DIR");
  std::string filename;
  if (outdir_env && strlen(outdir_env) > 0) {
    filename = outdir_env;
    if (filename.back() != '/') filename.push_back('/');
  } else {
    filename = "outputs/";
  }
  filename.append(this->get_name());
  filename.append("Final.txt");

  // Get a file handle
  std::ofstream drawable;

  // Open the file
  drawable.open(filename);

  // If the was opened, write the drawable info out.
  if (drawable.is_open()) {
    // Output drawable edge data.
    for (auto e : edges) {
      drawable << "e ";
      drawable << e->get_id() << " ";
      drawable << e->get_from()->get_id() << " ";
      drawable << e->get_to()->get_id() << " ";
      drawable << e->get_safety() << std::endl;
    }

    // Output drawable node data.
    for (auto n : nodes) {
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
    std::vector<Agent> copy = get_agent_vector();

    // Output drawable agent data: route (a), group size (g), and times (t)
    for (auto agent : copy) {
      // Route
      drawable << "a ";
      drawable << agent.get_id();
      for (auto i : agent.get_route()) {
        drawable << " " << i;
      }
      drawable << std::endl;

      // Group size
      drawable << "g " << agent.get_id() << " " << agent.get_member_count() << std::endl;

      // Route times (absolute arrival times corresponding to route entries)
      std::vector<float> rts = agent.get_route_times();
      drawable << "t " << agent.get_id();
      for (auto tf : rts) {
        drawable << " " << tf;
      }
      drawable << std::endl;
    }
    drawable.close();
  } else {
    printf("Couldn't write to %s\n", filename.c_str());
  }
}

/** Prints a representation of the last simulation run. 
 * More specifically, outputs agent routes take during the last simulation.
 */
void City::print_simulation() {
  std::vector<Agent> copy = get_agent_vector();

  for (auto agent : copy) {
    agent.print_route_clean();
  }
}

/* Initializes node probabilities.
 */
void City::initialize_nodes() {
  for (auto n : nodes) {
    n->init_probs();
  }
}

/** Initializes edges.
 */
void City::initialize_edges() {
  for (auto& e : edges) {
    e->init();
  }
}

/** Sets edges in the city with the probabilities specified in the
 * argument. Chromosome objects produce the prob_set object for
 * reading by this function, and some other stuff...
 */
void City::set_nodes(std::vector< std::vector<float> > prob_set) {
  std::vector<float> curr_probs;
  int i = 0;

  // Iterate over all nodes in the city...
  for (auto& n : nodes) {
    // Get the probabilities corresponding to the current node
    curr_probs = prob_set.at(i);

    // Set the node's probabilities accordingly...
    n->set_probs(curr_probs);

    // Increment index.
    i++;
  }
}

// DEPRECATED - DO NOT USE
float City::simulate() {
  float currTime = 0;
  Agent currAgent;  // Container for the currently evaluated agent.
  std::shared_ptr<Node> currNode;  // Container for the current node.
  std::shared_ptr<Edge> selectedEdge;  // Container for the selected edge.
  float t = 0.0;

  if (this->agents.size() == 0) {
    printf("Whoops. Agent priority queue uninitialized. Exiting...\n");
    exit(1);
  }

  // Run the priority queue while time lasts.
  while (currTime < static_cast<float>(this->sim_hours)) {
    // Get the next agent.
    currAgent = this->agents.top();

    // Remove the agent from the queue.
    this->agents.pop();

    currTime = currAgent.get_next_time();

    // Check to make sure we dont evaluate any agents that arrive after max time
    if (currTime >= static_cast<float>(this->sim_hours)) break;

    // Get the node the agent is arriving at.
    currNode = currAgent.get_to();
    currAgent.add_to_route(currNode->get_id());

    // 1.0 is max safety - specified in slang. once reached agents should not be
    // evaluated again.
    if (currNode->get_safety() == 1.0) {
      // At max safety node - agent will stay here so set edge to self-edge
      selectedEdge = currNode->get_self_edge();

      // Sanity check
      if (!selectedEdge) {
	printf("Node %d has no self edge. Adjust in SLANG.\n",
		currNode->get_id());
	exit(0);
      }

      // Incremenet count on edge.
      selectedEdge->inc_c(currAgent.get_member_count());

      // Decrement
      if (currAgent.get_edge() != NULL) {
	currAgent.get_edge()->dec_c(currAgent.get_member_count());
      }

      // Set the from edge to the current node.
      currAgent.set_from(currNode);

      // Set the edge to currNode's self-edge.
      currAgent.set_edge(selectedEdge);

      // Set the agent's final time of travel before reaching safety.
      currAgent.set_final_time(currTime);

      // Put agent at final end of queue - should never be evaluated again.
      currAgent.set_time(static_cast<float>(this->sim_hours));
    } else {
      // Select the edge the agent will move to.
      selectedEdge = get_next_edge(currNode);

      if (selectedEdge == NULL) {
	printf("An edge selected during simulation was a null edge. Exiting...\n");
	exit(0);
      }

      printf("Time to travel edge for this agent: %f\n", selectedEdge->time());

      if (currAgent.get_edge() != NULL) {
	// Remove counter from current edge; agent is leaving the edge.
	currAgent.get_edge()->dec_c(currAgent.get_member_count());
      }

      // Set the from node for current agent.
      currAgent.set_from(currNode);

      // Set the edge for the current agent.
      currAgent.set_edge(selectedEdge);
      selectedEdge->inc_c(currAgent.get_member_count());

      // Set the next node for the current agent.
      currAgent.set_to(selectedEdge->get_to());

      // Check if agent is travelling on self-edge,
      // indicating staying in the same node
      if (selectedEdge->get_from()->get_id() ==
	  selectedEdge->get_to()->get_id()) {
	// Wait specified time indicated in SLANG
	t = currNode->get_wait_time();
      } else {
	// Get the expected time to travel the edge.
	t = selectedEdge->time();
      }
      currAgent.inc_transit_time(t);

      currAgent.set_time(currTime + t);
    }

    // push the agent back into the priority queue.
    agents.push(currAgent);
  }

  // Calculating fitness...
  // float total_safety = 0.0;
  // float total_time = 0.0;
  std::vector<Agent> copy;
  std::priority_queue<Agent,
		      std::deque<Agent>,
		      Agent::cmpSoonest> agents_copy = this->agents;

  // TODO(next user) Make so fitness incorporates longest time taken by an agent
  while (agents_copy.size() > 0) {
    copy.push_back(agents_copy.top());
    agents_copy.pop();
  }

  float max_time = 0.0;
  for (auto a : copy) {
    float f = a.get_final_time();
    if (f > max_time) {
      max_time = f;
    }
    // total_time += a.get_transit_time();
    // total_safety += a.get_curr_safety();
  }

  // Somthing not true: Divide total_safety by number of agents,
  // to normalize fitness value
  // return total_safety / agents.size();
  // return total_time / agents.size();
  return max_time;
}

// CURRENTLY USED SIMULATION
float City::simulate_for_safety() {
  float curr_time = 0.0, t = 0.0, epoch = this->sim_hours / 10.0;
  float next_time = epoch;
  Agent curr_agent;
  std::shared_ptr<Node> curr_node;
  std::shared_ptr<Edge> next_edge;

  safety_over_time.clear();

  if (this->agents.size() == 0) {
    printf("Agent priority queue uninitialized. Exiting...\n");
    exit(1);
  }

  // Simulation loop - runs until the next agent to be processed arrives
  // after the allowed simulation time (this->sim_hours)
  while (curr_time < this->sim_hours) {
    if (next_time - curr_time <= 0.0) {
      next_time += epoch;
      safety_over_time.push_back(get_sum_safety() / agents.size());
    }

    // Get and remove the next agent to be processed from the priority queue
    curr_agent = this->agents.top();
    this->agents.pop();

    // Update time to the next agents arrival time
    curr_time = curr_agent.get_next_time();

    // Make sure we are not running over the simulation time
    if (curr_time >= this->sim_hours) {
      agents.push(curr_agent);
      break;
    }

    // Get the node the agent is arriving at and add it to the agent's list
    curr_node = curr_agent.get_to();
    curr_agent.add_to_route(curr_node->get_id());

    // Select next edge the agent will travel on, according to node probs
    next_edge = get_next_edge(curr_node);

    // Traffic is backed up - set agent to wait and continue.
    if (next_edge == NULL) {
      float wait_time = curr_node->get_wait_time();

      curr_agent.inc_transit_time(wait_time);
      curr_agent.set_time(curr_time + wait_time);
      agents.push(curr_agent);
    } else {
      // Remove counter from edge agent is leaving
      if (curr_agent.get_edge() != NULL) {
	curr_agent.get_edge()->dec_c(curr_agent.get_member_count());
      }

      // Set this node as the agent's last node
      curr_agent.set_from(curr_node);

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

	if (next_edge->get_safety() == 1.0) {
	  t = this->sim_hours;
	}
      } else {
	// Get the link travel time.
	t = next_edge->time();
      }

      // Increment the agent's total transit time.
      curr_agent.inc_transit_time(t);

      // Set the arrival time of the agent
      curr_agent.set_time(curr_time + t);

      // Push the agent back onto the priority queue
      agents.push(curr_agent);
    }
  }

  // Calculate fitness - the sum of safety across all agents
  float total_safety = get_sum_safety();
  safety_over_time.push_back(total_safety / agents.size());

  return total_safety / static_cast<float>(this->agents.size());
}

/** Calculates the total safety of all agents.
 */
float City::get_sum_safety() {
  float total_safety = 0.0;
  std::vector<Agent> copy = get_agent_vector();

  // Clear all routes taken
  routes.clear();

  for (auto a : copy) {
    total_safety += a.get_curr_safety();
    routes.push_back(a.get_collapsed_route());
  }

  return total_safety;
}

std::vector<std::vector<int> > City::get_route_set() {
  std::vector<std::vector<int> > unique_routes;

  bool is_in = false;

  for (auto r : routes) {
    for (auto i : r) {
      printf("%d ", i);
    }
    printf("\n");
  }
  printf("***************\n");

  for (auto r : routes) {
    for (auto ur : unique_routes) {
      if (r == ur) {
	is_in = true;
      }
    }
    if (!is_in) {
      unique_routes.push_back(r);
    }
    is_in = false;
  }

  return unique_routes;
}

std::shared_ptr<Edge> City::get_next_edge(std::shared_ptr<Node> n) {
  // Get the probabilities map from the given node, n.
  std::map<std::shared_ptr<Edge>, float> m = n->get_prob();
  std::shared_ptr<Edge> ret_edge = NULL;

  // get a random value.
  float rand_val = static_cast<float>(randMod(100))/100.0;
  float sum_prob = 0.0;

  // This loop iterates over edges/probabilities.
  for (auto iterator = m.begin(); iterator != m.end(); iterator++) {
    // Accumulate probability
    sum_prob += iterator->second;

    // Accounting for null edges (ones that don't exist...)
    // Select the appropriate edge, probabilistically...
    if (rand_val < sum_prob) {
      if (iterator->first == NULL) {
	printf("Setting the ret_edge in get_next_edge...but it's null?\n");
      } else if (!(iterator->first->get_c() >= iterator->first->get_cmax())) {
	ret_edge = iterator->first;
	break;
      }
    }
  }

  return ret_edge;
}

std::shared_ptr<Node> City::add_node() {
  std::shared_ptr<Node> n = std::make_shared<Node>();
  nodes.push_back(n);
  return nodes.back();
}

std::shared_ptr<Edge> City::add_edge(int from_index, int to_index,
				     float cmax, float freeflow,
				     float bcoeff, float powcoeff,
				     float safety) {
  if (from_index >= num_nodes || to_index >= num_nodes) {
    printf("Attempt to add edge between nodes %d and %d failed.\n",
	   from_index, to_index);
    printf("Maximum number of nodes is %d\n", num_nodes);
    exit(1);
  }

  // Get to and from nodes from index parameters
  std::shared_ptr<Node> from_node = nodes.at(from_index);
  std::shared_ptr<Node> to_node = nodes.at(to_index);

  // EDGES ID INIT HERE
  std::shared_ptr<Edge> e =
    std::make_shared<Edge>(from_node, to_node, cmax, freeflow,
			   bcoeff, powcoeff, safety, edges.size());
  // Add new edge to city's edges
  edges.push_back(e);

  // Give both to and from nodes the new edge
  // Directed graph shouldn't need to_node->add
  from_node->add_edge(e);

  return e;
}

std::shared_ptr<Edge> City::remove_edge(int from_index, int to_index) {
  // Get from and to nodes from index parameters
  std::shared_ptr<Node> from_node = nodes.at(from_index);
  std::shared_ptr<Node> to_node = nodes.at(to_index);

  // Find the edge in the FROM node that goes to the TO node
  std::map<std::shared_ptr<Edge>, float> probs_from_node =
    from_node->get_prob();

  for (auto iterator = probs_from_node.begin();
       iterator != probs_from_node.end(); iterator++) {
    std::shared_ptr<Edge> edge = iterator->first;

    if (edge->get_to() == to_node) {
      // Directed graphs shouldn't need to remove to_node's edge
      // Remove from node's record of the edge.
      from_node->remove_edge(edge);

      // Replace city's record with nullptr
      // edges.at(edge->get_id()) = nullptr;

      // Erase the record of edge in city's record
      edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());

      // Return the edge
      return edge;
    }
  }

  // Edge wasn't found, return nullptr
  return nullptr;
}

// Sets the safety value of the node with ID == nodeID.
void City::set_node_safety(int nodeID, float safetyVal) {
  if (nodes.size() > nodeID) {
    nodes.at(nodeID)->set_safety(safetyVal);
  }
}

// Sets the safety of the edge from node1 to node2
void City::set_edge_safety(int node1, int node2, float safetyVal) {
  std::shared_ptr<Node> node_ptr = nodes.at(node1);
  int edge_id = -1;
  bool check = false;

  edge_id = node_ptr->is_connected(node2);

  if (edge_id != -1) {
    edges.at(edge_id)->set_safety(safetyVal);
    check = true;
  }

  if (!check) {
    printf("Setting safety of edge between %d and %d failed.", node1, node2);
    printf(" The edge does not exist.\n");
  }
}

void City::set_node(int node_ID, int capacity, float wait_time,
		    float safety, float longitude, float latitude) {
  if (node_ID >= num_nodes) {
    printf("Attempt to set values for node %d failed.\n",
	   node_ID);
    printf("Node does not exist. There are only %d nodes.\n", num_nodes);
    exit(1);
  }

  std::shared_ptr<Node> n = this->get_nodes().at(node_ID);
  n->set_capacity(capacity);
  n->set_wait_time(wait_time);
  n->set_safety(safety);
  n->set_longitude(longitude);
  n->set_latitude(latitude);
}

// Outputs city to a SLANG file, in the slang format expected.
// Probably never fully complete - will require ongoing work, as SLANG changes
void City::write_slang(Parameters params, char *file) {
  std::string filename;
  filename.append(file);
  filename.append(".slang");

  FILE *out;
  out = fopen(filename.c_str(), "w");

  fprintf(out, "city %s %lu %d\n", this->name.c_str(),
	   this->nodes.size(), this->degree);

  // output parameters to file
  // parameters strategy sigma sim_time pop/child pop size t size xover mutate
  fprintf(out, "parameters ");

  if (params.get_evo_strat() == 0) {
    fprintf(out, "ES+ ");
  } else if (params.get_evo_strat() == 1) {
    fprintf(out, "ES, ");
  }
  fprintf(out, "%f %f %d %d %d %f %f\n",
	   params.get_sigma(),
	   sim_hours,
	   params.get_pop_size(),
	   params.get_child_pop_size(),
	   params.get_tourney_size(),
	   params.get_xover_prob(),
	   params.get_mutate_prob());

  // output edges
  // edge fromid toid maxCapacity, freeflow, b, beta, safety
  for (auto e : edges) {
    fprintf(out, "edge %d %d %f %f %f %f %f\n",
	     e->get_from()->get_id(),
	     e->get_to()->get_id(),
	     e->get_cmax(),
	     e->get_freeflow(),
	     e->get_bcoeff(),
	     e->get_powcoeff(),
	     e->get_safety());
  }

  // output nodes
  // node id capacity safety longitude latitude
  for (auto n : nodes) {
    fprintf(out, "node %d %d %f %f %f %f\n",
	     n->get_id(),
	     n->get_capacity(),
	     n->get_wait_time(),
	     n->get_safety(),
	     n->get_longitude(),
	     n->get_latitude());
  }

  // output agents
  // agent starting node id, number of agents, num members
  for (auto a : init_agents) {
    fprintf(out, "agent %d 1 %d\n",
	     a.get_from()->get_id(),
	     a.get_member_count());
  }

  // Don't store further commands, yet. Must add to end of output.
  fprintf(out, "ENTER SLANG COMMANDS HERE\n");

  fclose(out);

  printf("Wrote new slang file %s\n", filename.c_str());
}

/** Adds agents into the init_agents structure. 
 * An argument of -1 for node_id comes from the SLang specification
 * when the "random" keyword is used to specify where agents should
 * start, and accordingly, a random node ID is specified.
 */
void City::add_agents(int node_id, int num_agents, int num_ind) {
  if (node_id == -1) {
    for (int i = 0; i < num_agents; i++) {
      int start_node = randMod(this->nodes.size());
      Agent a = Agent(num_ind, 0.0, nodes.at(start_node),
		       nodes.at(start_node), NULL);
      a.set_id(init_agents.size());
      init_agents.push_back(a);
      agents.push(a);
    }
  } else if (node_id < num_nodes && node_id >= 0) {
    for (int i = 0; i < num_agents; i++) {
      Agent a = Agent(num_ind, 0.0, nodes.at(node_id),
		      nodes.at(node_id), NULL);
      a.set_id(init_agents.size());
      init_agents.push_back(a);
      agents.push(a);
    }
  } else {
    printf("Adding agents failed. Agents cannot be added to node %d",
	   node_id);
    printf(" as it does not exist.\n");
    exit(1);
  }
}

/** Adds an agent object to the init_agents structure.
 */
void City::add_agent(Agent a) {
  init_agents.push_back(a);
}

/** Returns the highest safety of any edge in the city.
 * Note, this returns the -semantic- highest safety. Agents cannot 
 * travel in node objects, and are only rewarded for being on edge objects
 * (ie, nodes' self-edges). Therefore, the value returned represents
 * the highest safety an agent can be at during a simulation.
 */
float City::get_max_edge_safety() {
  // initialize max.
  float max = 0.0;

  // Search for highest value, O(n)
  for (auto e : edges) {
    if (float curr_safety = e->get_safety() > max) {
      max = curr_safety;
    }
  }

  // Sanity check. Find potential SLang errors.
  if (max > 1.0) {
    printf("Maximum safety value on edges is greater than 1.0.");
    printf(" This may cause data to look weird - recommend verification.\n");
  }

  // Return it.
  return max;
}

/** Generates integer sets of starting locations for agents. Each set holds
 * the nodeIDs of the nodes agents should start at for each step 0...n-1 in 
 * the probability initialization procedure. For example, index 0 will hold
 * the set of nodeIDs with maximum safety. Index 1 will then hold the set of 
 * nodes who are neighbors with the nodes in the set at index 0, and so on. 
 * Therefore, the sets move initial agent locations from safety, towards danger,
 * for probability initialization. 
 * 
 * Stores final vector of sets in city data structure. 
 */
void City::generate_agent_starting_locations() {
  // The set of all visited nodes.
  std::set<int> visited_nodes;

  // A vector of sets. The sets contain groups of nodes for agents to
  // begin a probability initialization at. Index by step in initialization
  std::vector<std::set<int> > start_location_sets;

  // Get the maximum safety
  float max_safety = get_max_edge_safety();

  // Create initial set of nodeIDs, where max safety is.
  std::set<int> max_safety_set;

  // iterate over all edges.
  for (auto e : edges) {
    int curr_from_id = e->get_from()->get_id();
    int curr_to_id = e->get_to()->get_id();

    // Make sure we are looking at a self-edge.
    if (curr_from_id == curr_to_id) {
      int curr_id = curr_from_id;

      // Check if the self-edge has maximum safety.
      if (e->get_safety() == max_safety) {
	// Data structure that std::set::insert() returns
	std::pair<std::set<int>::iterator, bool> insert_return_val;

	// Add the nodeID to the visited_nodes set.
	insert_return_val = visited_nodes.insert(curr_id);

	// insert_return_val.second is bool. If true, new ID was
	// inserted in visited nodes, meaning this is a new ID. Insert.
	if (insert_return_val.second) {
	  // Add the nodeID to the max safety set.
	  max_safety_set.insert(curr_id);
	}
      }
    }
  }

  // Add the max_safety_set to the start locations vector.
  start_location_sets.push_back(max_safety_set);

  // get an index into the start locations vector.
  int set_index = 0;

  // Continue until all edges have been added
  while (visited_nodes.size() != nodes.size()) {
    std::set<int> next_set;

    // Iterate over each id in the last added set, find neighbors,
    // add them to next set.
    for (auto id : start_location_sets.at(set_index)) {
      // For each of the nodes in the last set, iterate over its neighbors
      for (auto new_id : get_node(id)->get_neighbor_IDs()) {
	// Used to check whether the current ID has been inserted in another set
	std::pair<std::set<int>::iterator, bool> insert_return_val;

	// Add each neighbor into the visited nodes set.
	insert_return_val = visited_nodes.insert(new_id);

	// If true, new_id is not in an other set. Insert.
	if (insert_return_val.second) {
	  // Add each neigbor into the next set.
	  next_set.insert(new_id);
	}
      }
    }

    // Error handling. Make sure we insert all nodes in the graph into
    // at least one of the sets. Checks if we added nothing, when we have
    // nodes left to add.
    if (next_set.empty() && visited_nodes.size() != nodes.size()) {
      printf("City::generate_agent_starting_locations():\n");
      printf("\tThere is an error in the graph topology. Unable to generate");
      printf(" the complete set of agent starting locations. Check graph.\n");
      break;
    } else {
      // Push the non-empty set into the starting locations vector.
      start_location_sets.push_back(next_set);
    }

    // Increment index that points to the last set inserted, the set the
    // holds nodeIDs for which we want to check the neighbors.
    set_index++;
  }

  // Push sets into city object container.
  this->agent_start_sets = start_location_sets;

  // For debugging purposes.
  // print_agent_sets();
}

// Prints out all the agent starting sets.
void City::print_agent_sets() {
  int set_number = 0;
  // Iterate over the sets.
  for (auto s : agent_start_sets) {
    // Print the IDs in each set.
    printf("Set %d:", set_number);
    for (auto id : s) {
      printf(" %d", id);
    }
    printf("\n");
    set_number++;
  }
}

/** Returns a semantic copy of the global city object, theCity, for use
 * in threading functions. Legacy, probablyl shouldn't be used anymore.
 */
City City::get_semantic_copy() {
  // Create the object by constructor.
  City new_city(this->get_name(), this->get_num_nodes(), this->get_degree());

  // Set the simulation time specified in theCity
  new_city.set_sim_time(this->sim_hours);

  // Get all the edges copied over, as new edge objects
  for (auto e : this->edges) {
    new_city.add_edge(e->get_from()->get_id(), e->get_to()->get_id(),
		       e->get_cmax(), e->get_freeflow(), e->get_bcoeff(),
		       e->get_powcoeff(), e->get_safety());
  }

  // Copy over all node objects
  for (auto n : this->nodes) {
    new_city.set_node(n->get_id(), n->get_capacity(), n->get_wait_time(),
		       n->get_safety(), n->get_longitude(), n->get_latitude());
  }

  // Copy over agent initializations
  for (auto a : this->init_agents) {
    new_city.add_agent(a);
  }

  // Return the new object.
  return new_city;
}
