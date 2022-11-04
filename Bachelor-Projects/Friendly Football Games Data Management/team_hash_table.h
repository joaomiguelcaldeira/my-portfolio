#ifndef TEAM_HASH_TABLE_H
#define TEAM_HASH_TABLE_H

#include "team_linked_list.h"

/* Defined type for each node of the hash table */
typedef struct stru_Teamht_node{
	TeamLink link;
	struct stru_Teamht_node *next;
}*TeamHT_node;

/* Defined type for the hash table */
typedef TeamHT_node *TeamHtable;

/* Functions for table indexing via hash function and a key */

int teamHash(char *str, int m);

char* teamKey(TeamLink link);

/* Node-related functions */

TeamHT_node teamHtNodeSelect(TeamHT_node head, char *name);

TeamHT_node teamHtNodeInsert(TeamHT_node node, TeamLink link);

/* Table-related functions */

TeamHtable teamHtInit(int dim);

void teamHtIndexRemove(TeamHT_node node);

void teamHtFree(TeamHtable table, int dim);

#endif