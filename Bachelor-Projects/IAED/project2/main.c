/********************************************************************************/
/*					File: main.c 												*/												
/*					Author: Joao Caldeira (ist93729)							*/											
/*					Description: Friendly Football Games management system 		*/
/********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "custom_types.h"
#include "game_linked_list.h"
#include "team_linked_list.h"
#include "game_hash_table.h"
#include "team_hash_table.h"

#define NAMESIZE 1024
#define TEAMSIZE 1024
#define HASH_DIM1 1000
#define ADDGAME 'a'
#define ADDTEAM 'A'
#define LIST 'l'
#define SEARCHTEAM 'P'
#define SEARCHGAME 'p'
#define DELETEGAME 'r'
#define CHANGESCORE 's'
#define BESTTEAMS 'g'

/*command counter*/
int NL = 0;

 /* Represents compressed data (2 double linked lists + 2 hash tables)*/
typedef struct data{
	/* Double linked list */
	GameList Gamesdll;
	TeamList Teamsdll;

	/* Hash tables */
	GameHtable gamesHT;
	TeamHtable teamsHT;
}*Data;

/* Initializes the data and returns it */
Data data_init(){
	Data data = malloc(sizeof(struct data));
	data -> Gamesdll = gameListInit();
	data -> Teamsdll = teamListInit();
	data -> gamesHT = gameHtInit(HASH_DIM1);
	data -> teamsHT = teamHtInit(HASH_DIM1);
	return data;
}

/* Adds a game to data and updates it, returning the updated data */
Data adicionaJogo(Data data){
	char name[NAMESIZE], team1[TEAMSIZE], team2[TEAMSIZE];
	int scoreTeam1,scoreTeam2,h_name,h_team1,h_team2;
	GameLink linkG;
	TeamHT_node team1Node,team2Node;

	NL++;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name,team1,team2,&scoreTeam1,&scoreTeam2);
	h_name = gameHash(name,HASH_DIM1);
	h_team1 = teamHash(team1,HASH_DIM1);
	h_team2 = teamHash(team2,HASH_DIM1);

	/* Checks if there is a game with the same name */
	if (gameHtNodeSelect(data -> gamesHT[h_name], name)){
		printf("%d Jogo existente.\n",NL);
		return data;
	}

	team1Node = teamHtNodeSelect(data -> teamsHT[h_team1],team1);
	team2Node = teamHtNodeSelect(data -> teamsHT[h_team2],team2);

	/* Checks if both teams exist in the system */
	if (team1Node == NULL || team2Node  == NULL){
		printf("%d Equipa inexistente.\n",NL);
		return data;
	}

	/* Adds the game to the system */
	linkG = gameLinkCreate(game_create(name,team1,team2,scoreTeam1,scoreTeam2));
	data -> Gamesdll -> head = gameLinkInsert(data -> Gamesdll -> head, linkG);
	data -> gamesHT[h_name] = gameHtNodeInsert(data -> gamesHT[h_name],data -> Gamesdll -> head);
	if (gameListOneElement(data -> Gamesdll))
		data -> Gamesdll -> last = data -> Gamesdll -> head;

	/* Updates team winnings */
	if (scoreTeam1 != scoreTeam2){
		if(scoreTeam1 > scoreTeam2)
			team1Node -> link -> team -> games_won += 1;
		else
			team2Node -> link -> team -> games_won += 1;
	}
	return data;
}

/* Adds a team to data and updates it, returning the updated data */
Data adicionaTeam(Data data){
	char newTeam[TEAMSIZE];
	int h_team;
	TeamLink linkT;

	NL++;
	scanf(" %[^\n]",newTeam);
	h_team = teamHash(newTeam,HASH_DIM1);

	/* Checks if there is already a team with the same name */
	if (teamHtNodeSelect(data -> teamsHT[h_team],newTeam)){
		printf("%d Equipa existente.\n",NL);
		return data;
	}

	/* Adds the team to the system */
	linkT = teamLinkCreate(team_create(newTeam));
	data -> Teamsdll -> head = teamLinkInsert(data -> Teamsdll -> head,linkT);
	data -> teamsHT[h_team] = teamHtNodeInsert(data -> teamsHT[h_team],\
	data -> Teamsdll -> head);
	if (teamListOneElement(data -> Teamsdll))
		data -> Teamsdll -> last = data -> Teamsdll -> head;

	return data;
}

/* Searches for a game with a given name in the system and prints it */
void procuraJogo(Data data){
	char gameName[NAMESIZE];
	int h_name;
	GameHT_node node;

	NL++;
	scanf(" %[^\n]",gameName);
	h_name = gameHash(gameName,HASH_DIM1);

	/* Searches the game name in the system */
	if((node = gameHtNodeSelect(data -> gamesHT[h_name],gameName)))
		printf("%d %s %s %s %d %d\n",NL,node -> link -> game -> name,node -> link -> game -> team1,\
		node -> link -> game -> team2, node -> link -> game -> score1,node -> link -> game -> score2);
	else
		printf("%d Jogo inexistente.\n",NL);
}

/* Searches for a team with a given name in the system and prints it */
void procuraTeam(Data data){
	char teamName[NAMESIZE];
	int h_name;
	TeamHT_node node;

	NL++;
	scanf(" %[^\n]",teamName);
	h_name = gameHash(teamName,HASH_DIM1);

	/* Searches the team name in the system */
	if((node = teamHtNodeSelect(data -> teamsHT[h_name],teamName)))
		printf("%d %s %d\n",NL,node -> link -> team -> name, node -> link -> team -> games_won);
	else
		printf("%d Equipa inexistente.\n",NL);
}

/* Deletes a game from the data system returning the updated data */
Data apagaJogo(Data data){
	char name[NAMESIZE];
	int h_name,h_team1,h_team2;
	GameHT_node gameNode;
	TeamHT_node team1,team2;
	GameLink linkG;

	NL++;
	scanf(" %[^\n]",name);
	h_name = gameHash(name, HASH_DIM1);
	gameNode = gameHtNodeSelect(data -> gamesHT[h_name],name);

	/* Verify if the game is in the data system */
	if(gameNode == NULL){
		printf("%d Jogo inexistente.\n",NL);
		return data;
	}
	linkG = gameNode -> link;
	h_team1 = teamHash(gameNode -> link -> game -> team1,HASH_DIM1);
	h_team2 = teamHash(gameNode -> link -> game -> team2,HASH_DIM1);
	team1 = teamHtNodeSelect(data -> teamsHT[h_team1],gameNode -> link -> game -> team1);
	team2 = teamHtNodeSelect(data -> teamsHT[h_team2],gameNode -> link -> game -> team2);

	/* Updates team winnings */
	if(gameNode -> link -> game -> score1 > gameNode -> link-> game -> score2){
		team1 -> link -> team -> games_won -= 1;
	} 
	if(gameNode -> link -> game -> score1 < gameNode -> link-> game -> score2)
		team2 -> link -> team -> games_won -= 1;

	/* Deletes game from the system */
	data -> gamesHT[h_name] = gameHtNodeRemove(data -> gamesHT[h_name],name);
	data -> Gamesdll = gameListUpdate(data -> Gamesdll,gameListIsHead(data -> Gamesdll, linkG),\
	gameListIsLast(data -> Gamesdll, linkG));
	gameLinkRemove(linkG);

	return data;
}

/* Changes a game’s score returning the updated data */ 
Data alteraScore(Data data){
	char name[NAMESIZE];
	int newScore1,newScore2,h_name,h_team1,h_team2,oldScore1,oldScore2;
	GameHT_node gameNode;
	TeamHT_node team1,team2;

	NL++;
	scanf(" %[^:\n]:%d:%d",name,&newScore1,&newScore2);
	h_name = gameHash(name,HASH_DIM1);
	gameNode = gameHtNodeSelect(data -> gamesHT[h_name],name);

	/* Verify if the game is in the data system */
	if(gameNode == NULL){
		printf("%d Jogo inexistente.\n",NL);
		return data;
	}

	h_team1 = teamHash(gameNode -> link -> game -> team1,HASH_DIM1);
	h_team2 = teamHash(gameNode -> link -> game -> team2,HASH_DIM1);
	team1 = teamHtNodeSelect(data -> teamsHT[h_team1],gameNode -> link -> game -> team1);
	team2 = teamHtNodeSelect(data -> teamsHT[h_team2],gameNode -> link -> game -> team2);
	oldScore1 = gameNode -> link -> game -> score1;
	oldScore2 = gameNode -> link -> game -> score2;

	/* Updates team winnings */
	if (findWinner(oldScore1,oldScore2) != findWinner(newScore1,newScore2)){
		if(findWinner(oldScore1,oldScore2) == 0){
			if(newScore1 > newScore2)
				team1 -> link -> team -> games_won += 1;
			else
				team2 -> link -> team -> games_won += 1;	
		}
		else if(findWinner(newScore1,newScore2) == 0){
			if(oldScore1 > oldScore2)
				team1 -> link -> team -> games_won -= 1;
			else
				team2 -> link -> team -> games_won -= 1;
		}
		else{
			if(findWinner(oldScore1,oldScore2) > findWinner(newScore1,newScore2)){
				team1 -> link -> team -> games_won += 1;
				team2 -> link -> team -> games_won -= 1;
			}
			else{
				team2 -> link -> team -> games_won += 1;
				team1 -> link -> team -> games_won -= 1;
			}

		}
	}

	/* Updates game’s score */
	gameNode -> link -> game -> score1 = newScore1;
	gameNode -> link -> game -> score2 = newScore2;

	return data;
}

/* Prints the teams with the most winngins in the system */
void printBest(Data data){
	int max,n,i,j,contador = 0;
	char comp[TEAMSIZE];
	char **v;	
	TeamLink temp = data -> Teamsdll -> last;

	NL++;

	/* Obtains max wins and the number of teams with max wins */
	max = teamBest(data -> Teamsdll);
	n = teamNumberBest(data -> Teamsdll,max);

	/* Checks if there are teams in the system*/
	if(n > 0){
		v = malloc(n * sizeof(char*));
		for(i = 0; i < n;i++)
			v[i] = malloc(TEAMSIZE*sizeof(char));

		/* Get the best teams */
		for(; temp; temp = temp -> previous){
			if(temp -> team -> games_won == max){
				strcpy(v[contador],temp -> team -> name);
				contador++;
			}
		}
		 /* Orders the teams lexicographically */
		for(i = 0; i < n; i++){
			for(j = i + 1; j < n; j++){
				if(strcmp( v[i],v[j] )> 0){
					strcpy(comp , v[i]);
					strcpy(v[i] , v[j]);
					strcpy(v[j] , comp);
				}
			}
		}

		/* Prints the teams */
		printf("%d Melhores %d\n",NL,max);
		for(i = 0; i < n; i++)
			printf("%d * %s\n",NL,v[i]);
		for(i = 0; i < n; i++)
			free(v[i]);
		free(v);
	}
}

/* Frees the memory allocated for the given data */
void data_free(Data data){
	gameLinkDestroy(data -> Gamesdll -> head);
	gameListFree(data -> Gamesdll);
	teamLinkDestroy(data -> Teamsdll -> head);
	teamListFree(data -> Teamsdll);
	teamHtFree(data -> teamsHT, HASH_DIM1);
	gameHtFree(data -> gamesHT, HASH_DIM1);
	free(data);
}

/* Main function */
int main(){
	int comando;
	Data data = data_init();
	while((comando = getchar()) != 'x'){
		switch(comando){
			case ADDGAME:
				data = adicionaJogo(data);
				break;
			case ADDTEAM:
				data = adicionaTeam(data);
				break;
			case LIST:
				NL++;
				gameListDisplayInfo(data -> Gamesdll,NL);
				break;
			case SEARCHGAME:
				procuraJogo(data);
				break;
			case SEARCHTEAM:
				procuraTeam(data);
				break;
			case DELETEGAME:
				data = apagaJogo(data);
				break;
			case CHANGESCORE:
				data = alteraScore(data);
				break;
			case BESTTEAMS:
				printBest(data);
				break;
		}
	}
	data_free(data);
	return 0;
}