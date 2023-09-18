/*João Caldeira 93729 P2-Solution*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

struct Graph {
    int V;
    int E;
    int A;
    struct Edge* edge;
    struct Edge* portEdges;
};

struct Subset{
    int parent;
    int rank;
};

struct Graph* createGraph(int V, int E, int A) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->A = A;
    graph->edge = (struct Edge*) calloc(E,sizeof(struct Edge));
    graph->portEdges = (struct Edge *)calloc(A, sizeof(struct Edge));
    return graph;
}

/* Find the subset of an element */
int find(struct Subset subsets[], int i){
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

/* Union of 2 subsets */
void unionSubsets(struct Subset subsets[], int x, int y){
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
    }
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

/* Function that applies the Union-Find by rank and retrieves the updated index */
int Union_Find(struct Subset subsets[],struct Edge edge, struct Edge *res, int index){
    int subsetSrc = find(subsets, edge.src);
    int subsetDest = find(subsets, edge.dest);

    if (subsetSrc != subsetDest)
    {
        res[index++] = edge;
        unionSubsets(subsets, subsetSrc, subsetDest);
    }
    return index;
}

/* Function to compare two edges based on their weights*/
int compare(const void *a, const void *b)
{
    struct Edge *a_edge = (struct Edge *)a;
    struct Edge *b_edge = (struct Edge *)b;
    return a_edge->weight - b_edge->weight;
}

/* Function that solves the problem with the respective built graph, using kruskal algorithm with sorting and Union-Find by rank */
void solveNetwork(struct Graph* graph) {
    int i;
    int V = graph->V;
    int E = graph->E;
    struct Subset subsets[V];       /* Union-Find Subsets */
    struct Edge *result = (struct Edge *)calloc(V, sizeof(struct Edge));        /* array to store the edges of the MST*/
    int indexNumberMST = 0;                      /* index of the edge to be added to the MST*/
    int finalCost = 0;              /* final cost of the MST*/
    int numPorts = 0;               /* number of shipping ports on the MST*/
    int numHighways = 0;            /* number of highways on the MST*/

    /* Create and initialize the subsets for Union-Find */
    for (i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    /* Sort the edges by weight */
    qsort(graph->edge, E, sizeof(struct Edge), compare);

    /* Inserts all of the shipping port opportunites into the MST */
    for (i = 0; i < graph->A; i++)
    {
        indexNumberMST = Union_Find(subsets, graph->portEdges[i], result, indexNumberMST);
    }

    /* Computes the need for highways to complete the MST */
    for (i = 0; i < E; i++)
    {
        if (indexNumberMST == V - 1)
            break;
        indexNumberMST = Union_Find(subsets, graph->edge[i], result, indexNumberMST);
    }

    /* The MST only has all the nodes of the graph (cities) if the number of edges of the MST is equal to the number of graph vertexes - 1 */
    if (indexNumberMST != V - 1)
    {
        printf("Impossible\n");
        free(result);
        return;
    }

    /* Calculates Total Cost and number of ports and highways to build */
    for (i = 0; i < indexNumberMST; i++)
    {
        finalCost = finalCost + result[i].weight;
        if(result[i].src == 0 || result[i].dest == 0)
        {
            numPorts = numPorts + 1;
        }
        else
        {
            numHighways = numHighways + 1;
        }
    }
    printf("%d\n",finalCost);
    printf("%d %d\n",numPorts,numHighways);
    free(result);
}


int main (){
    int N, A, E , i , a, b, c;
    struct Edge edge;
    struct Edge *portEdges;
    struct Graph *graph;

    scanf("%d\n", &N);
    scanf("%d\n", &A);

    /* If there are no shipping ports then the program stops, printing impossible */
    if (A == 0)
    {
        printf("Impossible\n");
        return 0;
    }

    /* Store cities with potential ship ports to further add to the graph */
    portEdges = (struct Edge *)calloc(A, sizeof(struct Edge));
    for(i = 0; i < A; i++)
    {
        scanf("%d %d\n", &a, &c);
        
        /* Vertex 0 will be the vertex associated to the cities with shiping ports */
        edge.src = 0;
        edge.dest = a;
        edge.weight = c;
        portEdges[i] = edge;
    }

    /* Create and add edges (highways) to the graph */
    scanf("%d\n", &E);
    graph = createGraph(N + 1, E, A);
    for (i = 0; i < E; i++)
    {
        scanf("%d %d %d\n", &a, &b, &c);
        graph->edge[i].src = a;
        graph->edge[i].dest = b;
        graph->edge[i].weight = c;
    }

    /* Add the shipping ports to the graph */
    for (i = 0; i < A; i++)
    {
        graph->portEdges[i].src = portEdges[i].src;
        graph->portEdges[i].dest = portEdges[i].dest;
        graph->portEdges[i].weight = portEdges[i].weight;
    }

    solveNetwork(graph);

    free(portEdges);
    free(graph->edge);
    free(graph->portEdges);
    free(graph);
    return 0;
}