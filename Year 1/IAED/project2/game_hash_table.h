#ifndef GAME_HASH_TABLE_H
#define GAME_HASH_TABLE_H

/* Defined type for each node of the hash table */
typedef struct stru_ht_node{
	GameLink link;
	struct stru_ht_node *next;
}*GameHT_node;

/* Defined type for the hash table */
typedef GameHT_node *GameHtable;

/* Functions for table indexing via hash function and a key */

int gameHash(char *str, int m);

char* gameKey(GameLink link);

/* Node-related functions */

GameHT_node gameHtNodeSelect(GameHT_node head, char *name);

GameHT_node gameHtNodeInsert(GameHT_node node, GameLink link);

GameHT_node gameHtNodeRemove(GameHT_node head, char *name);

/* Table-related functions */

GameHtable gameHtInit(int dim);

void gameHtIndexRemove(GameHT_node node);

void gameHtFree(GameHtable table, int dim);

#endif