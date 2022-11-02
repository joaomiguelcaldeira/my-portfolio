#include <stdlib.h>
#include <stdio.h>
#include "routing-simulator.h"

typedef struct {
  cost_t link_cost[MAX_NODES];
  int version;
} link_state_t;

// Message format to send between nodes.
typedef struct {
  link_state_t ls[MAX_NODES];
} message_t;

// State format.
typedef struct {
	link_state_t nodeLs[MAX_NODES];
} state_t;

void initPath(node_t path[MAX_NODES]){
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
		path[i] = -1;
}

void initPredecessor(node_t predecessor[MAX_NODES]){
	for (node_t i = get_first_node(); i <= get_last_node(); i++)
			predecessor[i] = i;
}

bool fullPath(node_t path[MAX_NODES]){
	for (node_t i = get_first_node(); i <= get_last_node(); i++){
		if(path[i] == -1)
			return false;
	}
	return true;
}

bool checkExistence(node_t path[MAX_NODES],node_t node){
	for (node_t i = get_first_node(); i <= get_last_node(); i++){
		if(path[i] == node)
			return true;
	}
	return false;
}

node_t getPredecessor(node_t predecessor[MAX_NODES],node_t node){
	node_t aux = node;
	for (node_t i = get_first_node(); i <= get_last_node(); i++) // max iterations
		aux = predecessor[aux];
	return aux;
}

void doDijsktra(state_t *s){
	node_t path[MAX_NODES];
	initPath(path);
	path[0] = get_current_node();
	node_t predecessor[MAX_NODES];
	initPredecessor(predecessor);
	int pathSize = 1;
	while(!fullPath(path)){
		cost_t minW = COST_INFINITY;
		node_t w;
		for (node_t i = get_first_node(); i <= get_last_node(); i++){
			if(!checkExistence(path,i)){
				if(s -> nodeLs[get_current_node()].link_cost[i] <= minW){
					minW = s -> nodeLs[get_current_node()].link_cost[i];
					w = i;
				}
			}
		}
		path[pathSize] = w;
		pathSize++;
		cost_t cost = minW;
		node_t hop = predecessor[w];
		while(hop != predecessor[hop]) {
			if(s->nodeLs[hop].link_cost[predecessor[hop]] == COST_INFINITY)
				cost = COST_INFINITY;
			hop = predecessor[hop];
		}
		if(get_link_cost(hop) == COST_INFINITY) cost = COST_INFINITY;
		set_route(w,hop,cost);
		s->nodeLs[get_current_node()].link_cost[w] = cost;
		for (node_t j = get_first_node(); j <= get_last_node(); j++){
			if(!checkExistence(path,j)){
				if(get_link_cost(j) > COST_ADD(minW, s-> nodeLs[w].link_cost[j])){
					s -> nodeLs[get_current_node()].link_cost[j] = COST_ADD(minW, s-> nodeLs[w].link_cost[j]);
					predecessor[j] = w;
				}
			}
		}
	}
}

// Notify a node that a neighboring link has changed cost.
void notify_link_change(node_t neighbor, cost_t new_cost) {
	state_t *s;
	if (!(s = (state_t*)get_state())) {	
		s = (state_t*)malloc(sizeof(state_t));
		for (node_t i = get_first_node(); i <= get_last_node(); i++){
			s -> nodeLs[i].version = 0;
			for (node_t j = get_first_node(); j <= get_last_node(); j++)
				if(get_current_node() == i)
					s -> nodeLs[i].link_cost[j] = get_link_cost(j);
				else
					s -> nodeLs[i].link_cost[j] = COST_INFINITY;
		}
	}
	s -> nodeLs[get_current_node()].link_cost[neighbor] = new_cost;
	s -> nodeLs[get_current_node()].version++;
	doDijsktra(s);
	set_state(s);
	for (node_t i = get_first_node(); i <= get_last_node(); i++) {
		if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
			message_t *message = (message_t*) malloc(sizeof(message_t));
			for (node_t i = get_first_node(); i <= get_last_node(); i++)
				message -> ls[i] = s -> nodeLs[i];
			send_message(i,message);
		}
	}
}


// Receive a message sent by a neighboring node.
void notify_receive_message(node_t sender, void *message) {
	message_t * m;
	state_t *s;
	int sendFlag = 0;
	s = (state_t*)get_state();
	m = (message_t*)message;
	for (node_t i = get_first_node(); i <= get_last_node(); i++){
		if(m -> ls[i].version > s -> nodeLs[i].version){
			s -> nodeLs[i] = m -> ls[i];
			doDijsktra(s); 
			sendFlag = 1;
		}
	}
	set_state(s);
	if(sendFlag){
		for (node_t i = get_first_node(); i <= get_last_node(); i++) {
			if(get_link_cost(i) != COST_INFINITY && i != get_current_node()){
				message_t *message = (message_t*) malloc(sizeof(message_t));
				for (node_t i = get_first_node(); i <= get_last_node(); i++)
					message -> ls[i] = s -> nodeLs[i];
				send_message(i,message);
			}
		}
	}
}
