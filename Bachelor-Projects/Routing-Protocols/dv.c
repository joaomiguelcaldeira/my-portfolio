
#include <stdlib.h>
#include <stdio.h>
#include "routing-simulator.h"

// Message format to send between nodes.
typedef struct {
	cost_t distance_vector[MAX_NODES];
} message_t;

// State format.
typedef struct {
	cost_t mat[MAX_NODES][MAX_NODES];
} state_t;

void copyArray(cost_t dv[MAX_NODES],cost_t msg[MAX_NODES]){
	for (node_t i = get_first_node(); i <= get_last_node(); i++) 
		msg[i] = dv[i];
}

cost_t min(state_t* s,node_t n){
	cost_t aux = COST_INFINITY;
	cost_t calc;
	node_t hop;
	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
			calc = COST_ADD(get_link_cost(i),s -> mat[i][n]);
			if (aux > calc){
				aux = calc;
				hop = i;
			}
		}
	};
	set_route(n,hop,aux);
	return aux;
}

// Notify a node that a neighboring link has changed cost.
void notify_link_change(node_t neighbor, cost_t new_cost) {
	printf("node %d neighbor %d\n",get_current_node(),neighbor);
	state_t *s;
	if (!(s = (state_t*)get_state())) {				//state inicial
		s = (state_t*)malloc(sizeof(state_t));
		for (node_t i = get_first_node(); i <= get_last_node(); i++) {
			for (node_t j = get_first_node(); j <= get_last_node(); j++) {
				if(j == i)
					s -> mat[i][j] = 0;
				else
					s -> mat[i][j] = COST_INFINITY;
			}
		}
	}
	s -> mat[get_current_node()][neighbor] = new_cost;

	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		if(i != get_current_node())
			s -> mat[get_current_node()][i] = min(s,i);

	set_state(s);
	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
			message_t *message = (message_t*) malloc(sizeof(message_t));
			copyArray(s -> mat[get_current_node()],message -> distance_vector);
			send_message(i,message);
		}
	}
}

// Receive a message sent by a neighboring node.
void notify_receive_message(node_t sender, void *message) {
	message_t * m;
	state_t *s;
	int sendFlag = 0;
	cost_t min_aux;
	s = (state_t*)get_state();
	m = (message_t*)message;
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		s -> mat[sender][i] = m -> distance_vector[i];
    
	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(i != get_current_node()){
			min_aux = min(s,i);
			if(s -> mat[get_current_node()][i] != min_aux)
				sendFlag = 1;
			s -> mat[get_current_node()][i] = min_aux;
		}
	}

	if(sendFlag){
		for (node_t i = get_first_node(); i <= get_last_node(); i++) {
			if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
				message_t *msg = (message_t*) malloc(sizeof(message_t));
				copyArray(s -> mat[get_current_node()],msg -> distance_vector);
				send_message(i,msg);
			}
		}
	}	
}