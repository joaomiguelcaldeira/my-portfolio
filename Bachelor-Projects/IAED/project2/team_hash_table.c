/********************************************************************************/
/*					File: team_hash_table.c 									*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: teams hash table code							*/
/********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_types.h"
#include "team_hash_table.h"
#include "team_linked_list.h"

#define MAXLEN 20			/* Maximum dimension defined in case the given string is too long */

/*************************************************************************************************/
/*                                             Hashing related functions                         */
/*************************************************************************************************/

/* Returns the obtained number related to the given string and integer */
int teamHash(char *str, int m){
	int i, dim, len = strlen(str), res = 0;

	dim = len > MAXLEN ? MAXLEN : len;
	for(i = 0; i < dim; i++)
		res += str[i]*(i+1);
	return res%m;
}

/* Returns the link's key according to the given character */
char* teamKey(TeamLink link){
	return link -> team -> name;
}

/************************************************************************************************/
/*                                    Node related functions                            		*/
/************************************************************************************************/

/* Given a link, inicializes a new node, inserts it as the new head and returns it */
TeamHT_node teamHtNodeInsert(TeamHT_node head, TeamLink link){
	TeamHT_node newnode = malloc(sizeof(struct stru_Teamht_node));
	newnode -> link = link;
	newnode -> next = head;
	return newnode;
}

/* Returns the node whose name matches with the given name if it exists, else returns NULL */
TeamHT_node teamHtNodeSelect(TeamHT_node head, char *name){
	for(; head; head = head -> next)
		if (!strcmp(teamKey(head -> link), name))
			return head;
	return NULL;
}

/************************************************************************************************/
/*                                    Table related functions                       			*/
/************************************************************************************************/

/* Inicializes an hash table with the given dimension and returns it */
TeamHtable teamHtInit(int dim){
	int i;
	TeamHtable table = malloc(dim*sizeof(struct stru_Teamht_node));
	for (i = 0; i < dim; i++)
		table[i] = NULL;
	return table;
}

/* Frees the allocated memory relative to the given table index nodes */
void teamHtIndexRemove(TeamHT_node head){
	TeamHT_node temp;

	while (head){
		temp = head;
		head = head -> next;
		free(temp);
	}
}

/* Frees the allocated memory for the table with the given dimension */
void teamHtFree(TeamHtable table, int dim){
	int i;

	for(i = 0; i < dim; i++)
		table[i] ? teamHtIndexRemove(table[i]) : free(table[i]);
	free(table);
}