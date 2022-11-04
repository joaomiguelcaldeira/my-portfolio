/********************************************************************************/
/*					File: game_linked_list.c 									*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: game double linked list code					*/
/********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_types.h"
#include "game_linked_list.h"
#include "game_hash_table.h"

/************************************************************************************************/
/*                                    Links related functions                         			*/
/************************************************************************************************/

/* Initializes and returns a new link with the given contact */
GameLink gameLinkCreate(Game *game){
	GameLink new = malloc(sizeof(struct node));
	new -> game = game;
	return new;
}


/* Returns the created link with the given contact and the given head */
GameLink gameLinkInsert(GameLink head, GameLink link){
	link -> next = head;
	link -> previous = NULL;
	if (head)
		head -> previous = link;
	return link;
}

/* Returns 1 iff the given links' keys match, else returns 0 */
int gameLinksEqual(GameLink l1, GameLink l2){
	return !strcmp(gameKey(l1), gameKey(l2));
}

/* Removes the given link and frees the memory associated with it */
void gameLinkRemove(GameLink link){
	if (link -> previous)
		link -> previous -> next = link -> next;
	if (link -> next)
		link -> next -> previous = link -> previous;
	game_remove(link -> game);
	free(link);
}

/* Given the head of a double linked list, removes every link in it */
void gameLinkDestroy(GameLink head){
	GameLink aux;

	while (head){
		aux = head;
		head = head -> next;
		gameLinkRemove(aux);
	}
}

/************************************************************************************************/
/*                                    List related functions                        			*/
/************************************************************************************************/

/* Initializes and returns a list */
GameList gameListInit(){
	GameList list = malloc(2*sizeof(struct node));
	list -> head = NULL;
	list -> last = NULL;
	return list;
}

/* Returns 1 if the given list has only one element */
int gameListOneElement(GameList list){
	return list -> head -> next == NULL;
}

/* Returns 1 if the given link is the head of the given list, else returns 0 */
int gameListIsHead(GameList list, GameLink link){
	return gameLinksEqual(list -> head, link);
}

/* Returns 1 if the given link is the last element of the given list, else 0 */
int gameListIsLast(GameList list, GameLink link){
	return gameLinksEqual(list -> last, link);
}

/* Returns the new head if the given value is 1, else returns the given head */
GameLink gameListChangeHead(GameLink head, int value){
	return value == 1 ? head -> next : head;
}

/* Returns the new last element if the given value is 1, else returns the given link */
GameLink gameListChangeLast(GameLink last, int value){
	return value == 1 ? last -> previous : last;
}

/* Changes the head and the last element of the given list according to the other arguments */
GameList gameListUpdate(GameList list, int changehead, int changelast){
	list -> head = gameListChangeHead(list -> head, changehead);
	list -> last = gameListChangeLast(list -> last, changelast);
	return list;
}

/* Prints the list information in the pretended format */ 
void gameListDisplayInfo(GameList list,int NL){
	GameLink temp = list -> last;
	for(; temp; temp = temp -> previous)
		game_print(temp -> game,NL);
}

/* Frees the memory allocated for the given list */
void gameListFree(GameList list){
	free(list);
}