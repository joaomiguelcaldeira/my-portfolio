#include <stdlib.h>
#include <stdio.h>
#include "routing-simulator.h"

// Message format to send between nodes.
typedef struct {
	cost_t distance_vector[MAX_NODES][MAX_NODES];
} message_t;

// State format.
typedef struct {
	int mat[MAX_NODES][MAX_NODES][MAX_NODES];
} state_t;

void copyArray(int dv[MAX_NODES][MAX_NODES],cost_t msg[MAX_NODES][MAX_NODES]){
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		for (node_t j = get_first_node(); j <= get_last_node() + 1; j++)
			msg[i][j] = dv[i][j];
}

void insertPath(state_t* s, node_t hop, node_t n){
	for (node_t i = get_first_node() + 1; i <= get_last_node(); i++){
		if(s -> mat[get_current_node()][n][i] == -1){
			s -> mat[get_current_node()][n][i] = hop;
			break;
		}
	}
}

bool checkLoop(state_t* s,node_t i, node_t n){
	for (node_t j = get_first_node() + 1; j <= get_last_node(); j++){
		if(get_current_node() == s -> mat[i][n][j])
			return true;
	}
	return false;
}

cost_t min(state_t* s,node_t n){
	cost_t aux = COST_INFINITY;
	cost_t calc;
	node_t hop;
	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
			if(checkLoop(s,i,n)){
				calc = COST_INFINITY;
			}
			else{
				calc = COST_ADD(get_link_cost(i),s -> mat[i][n][0]);
				if (aux > calc){
					aux = calc;
					hop = i;
				}
			}
		}
	}
	set_route(n,hop,aux);
	if(aux < COST_INFINITY)
		insertPath(s,hop,n);
	return aux;
}

void initMat(state_t* s){
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		for (node_t j = get_first_node(); j <= get_last_node(); j++)
			for (node_t k = get_first_node(); k <= get_last_node(); k++)
				s -> mat[i][j][k] = -1;
}

// Notify a node that a neighboring link has changed cost.
void notify_link_change(node_t neighbor, cost_t new_cost) {
	state_t *s;
	if (!(s = (state_t*)get_state())) {				//state inicial
		s = (state_t*)malloc(sizeof(state_t));
		initMat(s);
		for (node_t i = get_first_node(); i <= get_last_node(); i++) {
			for (node_t j = get_first_node(); j <= get_last_node(); j++) {
				if(j == i)
					s -> mat[i][j][0] = 0;
				else
					s -> mat[i][j][0] = COST_INFINITY;
			}
		}
	}
	s -> mat[get_current_node()][neighbor][0] = new_cost;
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		if(i != get_current_node()){
			s -> mat[get_current_node()][i][0] = min(s,i);
		}


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
		for (node_t j = get_first_node(); j <= get_last_node(); j++)
			s -> mat[sender][i][j] = m -> distance_vector[i][j];

	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(i != get_current_node()){
			min_aux = min(s,i);
			if(s -> mat[get_current_node()][i][0] != min_aux)
				sendFlag = 1;
			s -> mat[get_current_node()][i][0] = min_aux;
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