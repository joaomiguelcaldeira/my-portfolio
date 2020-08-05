/********************************************************************************/
/*					File: team_linked_list.c 									*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: team double linked list code					*/
/********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_types.h"
#include "team_linked_list.h"
#include "team_hash_table.h"

/************************************************************************************************/
/*                                    Links related functions                         			*/
/************************************************************************************************/

/* Initializes and returns a new link with the given contact */
TeamLink teamLinkCreate(Team *team){
	TeamLink new = malloc(sizeof(struct teamnode));
	new -> team = team;
	return new;
}


/* Returns the created link with the given contact and the given head */
TeamLink teamLinkInsert(TeamLink head, TeamLink link){
	link -> next = head;
	link -> previous = NULL;
	if (head)
		head -> previous = link;
	return link;
}

/* Returns 1 iff the given links' keys match, else returns 0 */
int teamLinksEqual(TeamLink l1, TeamLink l2){
	return !strcmp(teamKey(l1), teamKey(l2));
}

/* Removes the given link and frees the memory associated with it */
void teamLinkRemove(TeamLink link){
	if (link -> previous)
		link -> previous -> next = link -> next;
	if (link -> next)
		link -> next -> previous = link -> previous;
	teamRemove(link -> team);
	free(link);
}

/* Given the head of a double linked list, removes every link in it */
void teamLinkDestroy(TeamLink head){
	TeamLink aux;

	while (head){
		aux = head;
		head = head -> next;
		teamLinkRemove(aux);
	}
}

/************************************************************************************************/
/*                                    List related functions                        			*/
/************************************************************************************************/

/* Initializes and returns a list */
TeamList teamListInit(){
	TeamList list = malloc(2*sizeof(struct teamnode));
	list -> head = NULL;
	list -> last = NULL;
	return list;
}

/* Returns 1 if the given list has only one element */
int teamListOneElement(TeamList list){
	return list -> head -> next == NULL;
}

/* Returns the new head if the given value is 1, else returns the given head */
TeamLink teamListChangeHead(TeamLink head, int value){
	return value == 1 ? head -> next : head;
}

/* Returns the new last element if the given value is 1, else returns the given link */
TeamLink teamListChangeLast(TeamLink last, int value){
	return value == 1 ? last -> previous : last;
}

/* Returns the max number of wins by a team in the system */
int teamBest(TeamList list){
	int max = 0;
	TeamLink temp = list -> last;
	for(; temp; temp = temp -> previous){
		if(temp -> team -> games_won > max)
			max = temp -> team -> games_won;
	}
	return max;
}

/* Returns the number of teams with the maximum ammount of wins */
int teamNumberBest(TeamList list,int max){
	int count = 0;
	TeamLink temp = list -> last;
	for(; temp; temp = temp -> previous){
		if(temp -> team -> games_won == max)
			count++;
	}
	return count;
}

/* Frees the memory allocated for the given list */
void teamListFree(TeamList list){
	free(list);
}