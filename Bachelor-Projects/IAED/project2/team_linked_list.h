#ifndef TEAM_LINKED_LIST_H
#define TEAM_LINKED_LIST_H

/* Defined type for a list link */
typedef struct teamnode{
	Team *team;
	struct teamnode *previous, *next;
}*TeamLink;

/* Defined type for a list */
typedef struct teamlist{
	TeamLink head, last;
}*TeamList;

/* Link-related functions */

TeamLink teamLinkCreate(Team *team);

TeamLink teamLinkInsert(TeamLink head, TeamLink link);

int teamLinksEqual(TeamLink l1, TeamLink l2);

void teamLinkRemove(TeamLink link);

void teamLinkDestroy(TeamLink head);

/* List-related functions */

TeamList teamListInit();

int teamListOneElement(TeamList list);

TeamLink teamListIsHead(TeamLink head, int value);

TeamLink teamListChangeLast(TeamLink last, int value);

int teamBest(TeamList list);

int teamNumberBest(TeamList list,int max);

void teamListFree(TeamList link);

#endif