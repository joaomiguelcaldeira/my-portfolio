#include <stdint.h>

typedef int node_t;
#define MAX_NODES 100
typedef uint8_t cost_t;
#define COST_INFINITY 255

#define COST_ADD(a, b)                                                         \
  (((int)(a)) + ((int)(b)) < COST_INFINITY ? (a) + (b) : COST_INFINITY)

extern "C" {
/******************************************************************************\
* Router API                                                                   *
* Router module must include implementations for the handler functions         *
* and may use the command functions as needed.                                 *
\******************************************************************************/

// Handlers to implement in router module.
// Notify a node that a neighboring link has changed cost.
void notify_link_change(node_t neighbor, cost_t new_cost);

// Receive a message sent by a neighboring node.
void notify_receive_message(node_t sender, void *message);

// Commands to use.
// Get the current node ID.
node_t get_current_node();

// Access the current node's state.
void *get_state();

// Set the buffer for the current node's state.
// Buffer may subsequently be updated or changed in place.
void set_state(void *state);

// Functions to help with iterating over nodes.
node_t get_first_node();
node_t get_last_node();

// Get the cost of a neighboring link. returns COST_INFINITY if not a neighbor.
cost_t get_link_cost(node_t neighbor);

// Set or update the rout to destination, via the next_hop.
void set_route(node_t destination, node_t next_hop, cost_t cost);

// Send a message to a neighboring node.
void send_message(node_t neighbor, void *message);
}
