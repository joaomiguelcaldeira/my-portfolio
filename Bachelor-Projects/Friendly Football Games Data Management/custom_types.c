/********************************************************************************/
/*					File: custom_types.c 										*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: codigo referente aos tipos jogo e equipa		*/
/********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "custom_types.h"

/************************************************************************************************/
/*                                Teams related functions                           			*/
/************************************************************************************************/

/* Given two strings, inicializes and returns a pointer to the created Teams struct */
Team* team_create(char *team_name) {
	Team *team = malloc(sizeof(Team));
	char *new_team;

	new_team = team_name;
	team -> name = malloc(sizeof(char)*(strlen(new_team)+1));
	strcpy(team -> name, new_team);
	team -> games_won = 0;
	return team;
}

/* Given a team, removes it from the system */
void teamRemove(Team *team){
	free(team->name);
	free(team);
}

/* Given a team prints it’s name */
void team_print(Team *team){
	printf("%s\n",team -> name);
}

/************************************************************************************************/
/*                              	Game related functions                            			*/
/************************************************************************************************/

/* Returns a pointer to a game with the given information on its name, teams and score */
Game* game_create(char *name, char *team1,char *team2, int score_team1,int score_team2){ 
	Game *newgame = malloc(sizeof(Game));
	newgame -> name = malloc(sizeof(char)*(strlen(name)+1));
	newgame -> team1 = malloc(sizeof(char)*(strlen(team1)+1));
	newgame -> team2 = malloc(sizeof(char)*(strlen(team2)+1));

	strcpy(newgame -> name, name);
	strcpy(newgame -> team1,team1); 
	strcpy(newgame -> team2,team2);
	newgame -> score1 = score_team1;
	newgame -> score2 = score_team2;
	return newgame;
}

/* Prints the argument's information in the desired format*/
void game_print(Game *game,int NL){
	printf("%d %s %s %s %d %d\n",NL,game -> name,game -> team1,game -> team2,\
	game -> score1,game -> score2);
}

/* Frees all allocated memory related to the given argument */
void game_remove(Game *game){
	free(game -> team1);
	free(game -> team2);
	free(game -> name);
	free(game);
}

/* Given two scores, returns the winner or 0 in case of tie */
int findWinner(int score1,int score2){
	if (score1 > score2)
		return 1;
	if (score1 < score2)
		return 2;
	else
		return 0;
}