/* parser.y v0.0.1
 * Created by Keith Drew for Evac Planning simulation project
 * Based on the SLANG definition created by Damian Ball and Robert Heckendorn
 */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "spec.h"
#include "city.h"
#include "edge.h"
#include "node.h"
#include "param.h"
#include "ga.h"

#define IVAL u.tokptr->ival
#define FVAL u.tokptr->fval
#define SVAL u.tokptr->sval

std::shared_ptr<City> theCity;

Parameters params;

std::vector<Chromosome> predefined_probabilities;

int yylex();

static void yyerror( const char* );

%}

%union {
  struct treeNode *treeptr;
}

%token <treeptr> INT FLOAT STRING EXIT QUIT HI CITY EDGE RMEDGE RUN SHOW
%token <treeptr> STAR EDGES TOPOLOGY PROBABILITIES DOT EDGELOAD HEATMAP
%token <treeptr> ALLPATHS NL SAFETY NODE AGENT DRAWABLE SIMULATE EXH

%token <treeptr> PARAMETERS ES_P ES_C RANDOM SLANG PROBS SETS INIT

%type <treeptr> program commandlist command exit hi city edge rmedge
%type <treeptr> run show safety agent simulate exh probabilities slang probs
%type <treeptr> parameters node

 // %define parse.error verbose

%start program

%%

program: commandlist ;

commandlist: commandlist command | command ;

command: exit { printf( "Exiting...\n" ); exit(0); }
        | hi { printf( "Hi!\n" ); }
        | city
        | edge
        | agent
        | rmedge
        | run
        | show
        | safety
        | node
        | simulate
        | exh
	| probabilities
        | parameters
        | slang
	| probs;

exit: EXIT NL | QUIT NL;

hi: HI NL;

city: CITY STRING INT INT NL { theCity = std::make_shared<City>($2->SVAL,
								$3->IVAL,
								$4->IVAL ); };

edge: EDGE INT INT FLOAT FLOAT FLOAT FLOAT FLOAT NL {
	    theCity->add_edge( $2->IVAL, $3->IVAL, $4->FVAL,
			       $5->FVAL, $6->FVAL, $7->FVAL,
			       $8->FVAL ); }

rmedge: RMEDGE INT INT NL { theCity->remove_edge( $2->IVAL, $3->IVAL ); }
        | RMEDGE INT INT INT NL { /* not implemented yet */ };

run: RUN INT INT INT NL { run_ga( 1, $2->IVAL, $3->IVAL,
				  $4->IVAL, params.get_pop_size() ); }
   | RUN INT INT NL { run_ga( 1, $2->IVAL, $2->IVAL, $3->IVAL,
			      params.get_pop_size() ); }
   | RUN INT NL {run_ga(3, $2->IVAL, $2->IVAL,
                  $2->IVAL, params.get_pop_size() ); };

show: SHOW TOPOLOGY NL { theCity->print_city(); }
    | SHOW PROBABILITIES NL { theCity->print_nodes(); }
    | SHOW EDGELOAD NL { /* do stuff */ }
    | SHOW EDGES NL { theCity->print_edges(); }
    | SHOW DRAWABLE NL { theCity->print_drawable(); }
    | SHOW PARAMETERS NL { params.print(); };

safety: SAFETY NODE INT FLOAT NL { theCity->set_node_safety( $3->IVAL, $4->FVAL ); }
    | SAFETY EDGE INT INT FLOAT NL { theCity->set_edge_safety( $3->IVAL,
							   $4->IVAL,
							   $5->FVAL ); };

node: NODE INT INT FLOAT FLOAT FLOAT FLOAT NL { theCity->set_node( $2->IVAL,
								   $3->IVAL,
								   $4->FVAL,
								   $5->FVAL,
								   $6->FVAL,
								   $7->FVAL ); };

agent: AGENT INT INT INT NL { theCity->add_agents( $2->IVAL,
						   $3->IVAL,
						   $4->IVAL ); }
    | AGENT RANDOM INT INT NL { theCity->add_agents( -1,
						   $3->IVAL,
						   $4->IVAL ); }
    | AGENT SETS NL { theCity->generate_agent_starting_locations(); };

parameters: PARAMETERS ES_P FLOAT FLOAT INT INT INT FLOAT FLOAT NL
        { /* ES+, sigma, sim hours, pop size, child pop size, 
	     tourney size, xover prob, mutate prob */
	    theCity->set_sim_time( $4->FVAL );
	    params.set_evo_strat( 0 );
	    params.set_sigma( $3->FVAL );
	    params.set_pop_size( $5->IVAL );
	    params.set_child_pop_size( $6->IVAL );
	    params.set_tourney_size( $7->IVAL );
	    params.set_xover_prob( $8->FVAL );
	    params.set_mutate_prob( $9->FVAL ); }
    | PARAMETERS ES_C FLOAT FLOAT INT INT INT FLOAT FLOAT NL
        { /* ES, , sigma, sim hours, pop size, child pop size, 
	     tourney size, xover prob, mutate prob */
	    theCity->set_sim_time( $4->FVAL );
	    params.set_evo_strat( 1 );
	    params.set_sigma( $3->FVAL );
	    params.set_pop_size( $5->IVAL );
	    params.set_child_pop_size( $6->IVAL );
	    params.set_tourney_size( $7->IVAL );
	    params.set_xover_prob( $8->FVAL );
	    params.set_mutate_prob( $9->FVAL );	};

probabilities: PROBABILITIES STRING NL { read_probs( $2->SVAL ); }
    | PROBABILITIES INIT INT INT NL { run_ga(2, $3->IVAL, $4->IVAL, 0, 0); };

simulate: SIMULATE STRING NL { simulate_from_file( $2->SVAL ); };

exh: EXH NL { exhaustive_search(); /* Note - this requires a specific topology */ };

slang: SLANG STRING NL { theCity->write_slang( params, $2->SVAL ); };

probs: PROBS STRING INT NL { /* theCity->write_probs( $2->SVAL, $3->IVAL ); */ };

%%

static void yyerror( const char* s ) {
  fprintf(stderr, "%s: %s\n", s,
	  yylval.treeptr->u.tokptr->text );
  exit( 2 );
}

