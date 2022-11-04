/********************************************************************************/
/*					File: game_hash_table.c 									*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: games hash table code							*/
/********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_types.h"
#include "game_linked_list.h"
#include "game_hash_table.h"

#define MAXLEN 20			/* Maximum dimension defined in case the given string is too long */


/************************************************************************************************/
/*                                    Hashing related functions                         		*/
/************************************************************************************************/

/* Returns the obtained number related to the given string and integer */
int gameHash(char *str, int m){
	int i, dim, len = strlen(str), res = 0;

	dim = len > MAXLEN ? MAXLEN : len;
	for(i = 0; i < dim; i++)
		res += str[i]*(i+1);
	return res%m;
}

/* Returns the link's key according to the given character */
char* gameKey(GameLink link){
	return link -> game -> name;
}

/************************************************************************************************/
/*                                    Node related functions                            		*/
/************************************************************************************************/

/* Given a link, inicializes a new node, inserts it as the new head and returns it */
GameHT_node gameHtNodeInsert(GameHT_node head, GameLink link){
	GameHT_node newnode = malloc(sizeof(struct stru_ht_node));
	newnode -> link = link;
	newnode -> next = head;
	return newnode;
}

/* Returns the node whose name matches with the given name if it exists, else returns NULL */
GameHT_node gameHtNodeSelect(GameHT_node head, char *name){
	for(; head; head = head -> next)
		if (!strcmp(gameKey(head -> link), name))
			return head;
	return NULL;
}

/* Returns the number of nodes with equal parameter according to the given character */

/* Removes the node with the given name and returns the head */
GameHT_node gameHtNodeRemove(GameHT_node head, char *name){
	GameHT_node previous, temp;

	for (previous = NULL, temp = head; temp; previous = temp, temp = temp -> next)
		if (!strcmp(gameKey(temp -> link), name)){
			if (previous)
				previous -> next = temp -> next;
			else
				head = temp -> next;
			free(temp);
			break;
		}
	return head;
}

/************************************************************************************************/
/*                                    Table related functions                       			*/
/************************************************************************************************/

/* Inicializes an hash table with the given dimension and returns it */
GameHtable gameHtInit(int dim){
	int i;
	GameHtable table = malloc(dim*sizeof(struct stru_ht_node));
	for (i = 0; i < dim; i++)
		table[i] = NULL;
	return table;
}

/* Frees the allocated memory relative to the given table index nodes */
void gameHtIndexRemove(GameHT_node head){
	GameHT_node temp;

	while (head){
		temp = head;
		head = head -> next;
		free(temp);
	}
}

/* Frees the allocated memory for the table with the given dimension */
void gameHtFree(GameHtable table, int dim){
	int i;

	for(i = 0; i < dim; i++)
		table[i] ? gameHtIndexRemove(table[i]) : free(table[i]);
	free(table);
}