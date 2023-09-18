/* João Caldeira 93729 P3-Solution */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node *node;
struct node
{
    int head;     /**< The path-label start at &(Ti[head]) */
    int sdep;     /**< String-Depth, from the root down to node */
    node child;   /**< First child */
    node brother; /**< Brother */
    node slink;   /**< Suffix-Link */
    node *hook;   /**< What keeps this node linked? */
};

typedef struct point *point;
struct point
{
    node a; /**< node above */
    node b; /**< node bellow */
    int s;  /**< String-Depth */
};

node root;
int n;
char* T;
node last_internal_node;

int ptr2loc(node v, node A)
{
    int r;
    r = -1;
    if (NULL != v)
        r = ((size_t)v - (size_t)A) / sizeof(struct node);
    return (int)r;
}

void shownode(node v)
{
    if (NULL == v)
        printf("NULL\n");
    else
    {
        printf("node: %d ", ptr2loc(v, root));
        printf("head: %d ", v->head);
        printf("sdep: %d ", v->sdep);
        printf("child: %d ", ptr2loc(v->child, root));
        printf("brother: %d ", ptr2loc(v->brother, root));
        printf("slink: %d", ptr2loc(v->slink, root));
        printf("\n");
    }
}

void initNode(node n){
    n->head = 0;
    n->sdep = 0;
    n->child = NULL;
    n->brother = NULL;
    n->slink = NULL;
    n->hook = NULL;
}

int DescendQ(point p, char t){
    /* we can always descend from the sentinel node */
    if (ptr2loc(p->a, root) == 1)
    {
        p->a = root;
        p->b = root;
        return 1;
    }
    if (p->a == p->b)
    {
        node c = p->a->child;
        while (c != NULL)
        {
            if (T[c->head + p->s] == t)
            { 
                p->b = c;
                return 1;
            }
            c = c->brother;
        }
        return 0;
    }
    else
    {
        return T[p->b->head + p->s] == t;
    }
}

void Descend(point p, char t){
    p->s += 1;
    if(p->s == p->b->sdep){
        p->a = p->b;
    }
}

int AddLeaf(point p, node addNode, int inputIndex){
    /* Verifies if point is in the middle of two nodes and if there is, create Internal node */
    int numAdded = 0;
    if (p->a != p->b && p->s != p->b->sdep)
    {
        addNode->child = p->b;
        addNode->head = p->b->head;
        addNode->sdep = p->s;
        addNode->brother = p->b->brother;
    
    if (p->a->child == p->b)
    {
        p->a->child = addNode;
    }
    else
    {
        node c = p->a->child;
        while (c->brother != p->b)
        {
            c = c->brother;
        }
        c->brother = addNode;
    }

    p->b->brother = NULL;
    p->b->hook = &(addNode->child);
    p->b = addNode;

    printf("Internal ");
    shownode(addNode);

    if (last_internal_node)
    {
        last_internal_node->slink = addNode;
    }
    last_internal_node = addNode;

    numAdded++;
    }
    addNode = &(root[ptr2loc(addNode, root) + numAdded]);

    addNode->brother = p->b->child;
    addNode->hook = &(p->b->child);
    p->b->child = addNode;

    addNode->head = inputIndex - p->s;
    addNode->sdep = n - addNode->head;
    printf("Leaf ");
    shownode(addNode);
    numAdded++;

    return numAdded;
}

void SuffixLink(point p)
{
    char *pHead = &T[p->b->head + 1];
    int search_sdep = p->s - 1;
    p->a = p->a->slink;
    p->b = p->a;
    p->s = p->a->sdep;

    while (p->b->sdep < search_sdep)
    {
        p->a = p->b;
        p->s = p->a->sdep;
        DescendQ(p, pHead[p->a->sdep]);
    }

    p->s = search_sdep;
    if (p->s == p->b->sdep)
    {

    p->a = p->b;
        if (last_internal_node)
        {
            last_internal_node->slink = p->a;
            last_internal_node = NULL;
        }
    }
}

void smallest_cycle_rotation(point p, int nDep)
{
    while(p->s < nDep){
        node c = p->a->child;
        char t = T[0]; 
        while (c != NULL)
        {
            if (T[c->head + p->s] <= t && T[c->head + p->s] != '\0')
            {
                p->b = c;
                t = T[c->head + p->s];
            }
            c = c->brother;
        }
        p->s += 1;
        p->a = p->b;
    }
}

int main()
{
    int i, a, init_n;
    char* readT;

    scanf("%d", &init_n);

    readT = (char *)calloc(init_n + 1, sizeof(char));

    n = 2*init_n;

    T = (char *)calloc(n + 1, sizeof(char));

    scanf(" %s",readT);

    strcpy(T,readT);
    strcat(T,readT);
    

    root = (node)calloc(2*n + 3, sizeof(struct node));

    for(i = 0; i < 2*n + 3;i++){
        initNode(&(root[i]));
    }

    root->slink = &(root[1]);
    root->slink->sdep = -1;
    root->slink->child = root;

    point p = malloc(sizeof(struct point));
    p->a = &(root[0]);
    p->b = &(root[0]);
    p->s = 0;

    last_internal_node = NULL;

    /* actual number of nodes here is root + sentinel = 2 */
    a = 2;

    /* add "$" to perform Ukkonen's algorithm */
    n++;

    i = 0;
    while (i < n)
    {
        printf("Letter %c\n", '\0' == T[i] ? '$' : T[i]);
        while (!DescendQ(p, T[i]))
        {
            a += AddLeaf(p, &(root[a]), i);
            SuffixLink(p);
        }
        Descend(p, T[i]);
        i++;
    }
    
    p->a = &(root[0]);
    p->b = &(root[0]);
    p->s = 0;

    smallest_cycle_rotation(p,init_n);


    printf("%.*s\n", init_n, &T[p->b->head]);

    printf("Final version\n");
    i = 0;
    while (i < a)
    {
        shownode(&(root[i]));
        i++;
    }

    free(readT);
    free(T);
    free(root);
    free(p);
    return 0;
}