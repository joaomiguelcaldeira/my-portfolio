#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

/* Defined type for teams */
typedef struct team{
	char *name;
	int games_won;
}Team;


/* Defined type for the game */
typedef struct game{
	char *name;
	char *team1,*team2;
	int score1,score2;
}Game;

/* Email-related functions */

Team* team_create(char *team_name);

void teamRemove(Team *team);

void team_print(Team *team);

/* Game-related functions */

Game* game_create(char *name, char *team1,char *team2, int score_team1,int score_team2);

void game_print(Game *game,int NL);

void game_remove(Game *game);

int findWinner(int score1,int score2);

#endif