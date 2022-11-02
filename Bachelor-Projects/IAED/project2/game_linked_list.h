#ifndef GAME_LINKED_LIST_H
#define GAME_LINKED_LIST_H

/* Defined type for a list link */
typedef struct node{
	Game *game;
	struct node *previous, *next;
}*GameLink;

/* Defined type for a list */
typedef struct list{
	GameLink head, last;
}*GameList;

/* Link-related functions */

GameLink gameLinkCreate(Game *game);

GameLink gameLinkInsert(GameLink head, GameLink link);

int gameLinksEqual(GameLink l1, GameLink l2);

void gameLinkRemove(GameLink link);

void gameLinkDestroy(GameLink head);

/* List-related functions */

GameList gameListInit();

int gameListOneElement(GameList list);

int gameListIsHead(GameList list, GameLink link);

int gameListIsLast(GameList list, GameLink link);

GameLink gameListChangeHead(GameLink head, int value);

GameLink gameListChangeLast(GameLink last, int value);

GameList gameListUpdate(GameList list, int changehead, int changelast);

void gameListDisplayInfo(GameList list,int NL);

void gameListFree(GameList link);

#endif