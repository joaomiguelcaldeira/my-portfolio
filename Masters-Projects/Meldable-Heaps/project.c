/* João Caldeira 93729 P1-Solution*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 100 

typedef struct node *node;
struct node
{
    int v;           /* The value to store */
    node leftChild;  /* Left child */
    node rightChild; /* Right child */
    node *hook;      /* Pointer to field in the father node */
};

node A;

static int randBit(void)
{
    static unsigned int M = 0;
    static unsigned int P;
    int r;
    if (0 == M)
    {
        M = ~0;
        P = random();
    }
    r = P & 1;
    M = M >> 1;
    P = P >> 1;
    printf("Flipped a %d\n", r);
    return r;
}

int ptr2loc(node v, node A)
{
    int r;
    r = -1;
    if (NULL != v)
        r = ((size_t)v - (size_t)A) / sizeof(struct node);
    return (int)r;
}

void showNode(node v)
{
    int f;
    if (NULL == v)
        printf("NULL\n");
    else
    {
        printf("node: %d ", ptr2loc(v, A));
        printf("v: %d ", v->v);
        printf("leftChild: %d ", ptr2loc(v->leftChild, A));
        printf("rightChild: %d ", ptr2loc(v->rightChild, A));
        f = ptr2loc((node)v->hook, A);
        printf("father: %c %d",
               &(A[f].leftChild) == v->hook ? 'l' : 'r',
               f);
        printf("\n");
    }
}

void showHeaps(node v)
{
    if (v != NULL)
    {
        showNode(v);
        showHeaps(v->leftChild);
        showHeaps(v->rightChild);
    }
}

void Set(node v, int new_v)
{
    if (v->hook == NULL && v->leftChild == NULL && v->rightChild == NULL)
    {
        v->v = new_v;
    }
}

/* Auxiliary function to return the father node of a node c */
node getFather(node c){
    int cF = ptr2loc((node)c->hook, A);
    return &A[cF];
}

static void link(node f, node c, int d)
{
    /* unlinks the child node from the previous father node if existed */
    if(c->hook != NULL){
        node fatherV = getFather(c);
        if (fatherV->rightChild == c)
        {
            fatherV->rightChild = NULL;
        }
        if (fatherV->leftChild == c)
        {
            fatherV->leftChild = NULL;
        }
    }
    /* links the child node to the "new" father node */
    if (d)
    {
        f->rightChild = c;
    }
    else
    {
        f->leftChild = c;
    }

    printf("link A[%d] as %s of A[%d]\n",
           ptr2loc(c, A),
           d ? "rightChild" : "leftChild",
           ptr2loc(f, A));
}

node Meld(node v, node v2)
{
    int coinFlip;
    printf("Meld A[%d] A[%d]\n", ptr2loc(v, A), ptr2loc(v2, A));

    if (v == NULL)
    {
        return v2;
    }
    if (v2 == NULL)
    {
        return v;
    }

    if (v2->v < v->v)
    {
        node swap = v;
        v = v2;
        v2 = swap;
        printf("Swap to A[%d] A[%d]\n", ptr2loc(v, A), ptr2loc(v2, A));
    }

    coinFlip = randBit();
    if (coinFlip == 1)
    {
        v->rightChild = Meld(v->rightChild, v2);
        if (v->rightChild != NULL)
        {
            link(v, v->rightChild, coinFlip);
            v->rightChild->hook = &(v->rightChild);
        }
        return v;
    }
    else
    {
        v->leftChild = Meld(v->leftChild, v2);
        if (v->leftChild != NULL)
        {
            link(v, v->leftChild, coinFlip);
            v->leftChild->hook = &(v->leftChild);
        }
        return v;
    }
}

/* Function that finds the root of a given node v */
node findRoot(node v)
{
    int f;
    if (v->hook == NULL)
    {
        return v;
    }
    f = ptr2loc((node)v->hook, A);
    return findRoot(&A[f]);
}

int ArgMin(node v)
{
    node root = findRoot(v);
    printf("root A[%d] is A[%d]\n", ptr2loc(v, A), ptr2loc(root, A));
    return ptr2loc(root, A);
}

int Min(node v)
{
    node root = findRoot(v);
    printf("root A[%d] is A[%d]\n", ptr2loc(v, A), ptr2loc(root, A));
    return root->v;
}

int ExtractMin(node v)
{
    node root;
    node rootLeftChild;
    node rootRightChild;

    printf("extractMin A[%d]\n", ptr2loc(v, A));
    root = findRoot(v);
    printf("root A[%d] is A[%d]\n", ptr2loc(v, A), ptr2loc(root, A));

    rootLeftChild = root->leftChild;
    rootRightChild = root->rightChild;
    root->v = 0;
    root->leftChild = NULL;
    root->rightChild = NULL;
    root->hook = NULL;

    if (rootLeftChild == NULL && rootRightChild == NULL)
    {
        return ptr2loc(v, A);
    }
    else if (rootLeftChild == NULL)
    {
        rootRightChild->hook = NULL;
        return ptr2loc(rootRightChild, A);
    }
    else if (rootRightChild == NULL)
    {
        rootLeftChild->hook = NULL;
        return ptr2loc(rootLeftChild, A);
    }
    else
    {
        node new_root = Meld(rootLeftChild, rootRightChild);
        new_root->hook = NULL;
        return ptr2loc(new_root, A);
    }
}

int DecreaseKey(node v, int val)
{
    if (v->hook == NULL)
    {
        v->v = val;
        return ptr2loc(v, A);
    }
    else
    {
        node fatherV = getFather(v);
        node root = findRoot(v);
        printf("root A[%d] is A[%d]\n", ptr2loc(v, A), ptr2loc(root, A));
        v->v = val;

        if (fatherV->leftChild == v)
        {
            fatherV->leftChild = NULL;
        }
        else
        {
            fatherV->rightChild = NULL;
        }
        v->hook = NULL;
        return ptr2loc(Meld(root, v), A);
    }
}

int Delete(node v)
{
    node root;
    node fatherV;
    node subTree; 

    if (v->hook == NULL)
    {
        return ExtractMin(v);
    }

    root = findRoot(v);
    printf("root A[%d] is A[%d]\n", ptr2loc(v, A), ptr2loc(root, A));

    fatherV = getFather(v);
    if (fatherV->leftChild == v)
    {
        fatherV->leftChild = NULL;
    }
    else
    {
        fatherV->rightChild = NULL;
    }
    v->hook = NULL;

    subTree = &A[ExtractMin(v)];
    if(subTree == v){
        return ptr2loc(root, A);
    }

    return ptr2loc(Meld(root, subTree), A);
}


int main()
{
    char op;
    char line[MAX_LINE];
    int val, val2, n_nodes, i_nodes;

    scanf("%d %d", &n_nodes, &val);

    A = (node)calloc(n_nodes, sizeof(struct node));
    srandom(val);
    
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        sscanf(line, "%c %d %d\n", &op, &val, &val2);
        switch (op)
        {
        case 'S':
            showNode(&A[val]);
            break;
        case 'P':
            showHeaps(&A[val]);
            break;
        case 'V':
            Set(&A[val], val2);
            printf("set A[%d] to %d\n", val, val2);
            break;
        case 'U':
            printf("%d\n", ptr2loc(Meld(&A[val], &A[val2]), A));
            break;
        case 'R':
            printf("decKey A[%d] to %d\n", val, val2);
            printf("%d\n", DecreaseKey(&A[val], val2));
            break;
        case 'M':
            printf("min A[%d]\n", val);
            printf("%d\n", Min(&A[val]));
            break;
        case 'A':
            printf("%d\n", ArgMin(&A[val]));
            break;
        case 'E':
            printf("%d\n", ExtractMin(&A[val]));
            break;
        case 'D':
            printf("delete A[%d]\n", val);
            printf("%d\n", Delete(&A[val]));
            break;
        case 'X':
            printf("Final configuration:\n");
            for (i_nodes = 0; i_nodes < n_nodes; i_nodes++)
            {
                showNode(&A[i_nodes]);
            }
            free(A);
            exit(EXIT_SUCCESS);
        default:
            break;
        }
    }

    printf("Final configuration:\n");
    for (i_nodes = 0; i_nodes < n_nodes; i_nodes++)
    {
        showNode(&A[i_nodes]);
    }
    free(A);
    return 0;
}