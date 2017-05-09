/* VERSION 1.1.9.9.5
 *
 * scanner.c - Vertex Class
 *           - written by Ben Lindow
 *
 *    primMain(binheap* b, table* t, vertex** a)
 *      - main function to run prim's algorithm on an undirected graph
 *      - primMain(b, t, a);
 *    lessthan(void* a, void* b)
 *      - comparator function used to determine extreme between vertices
 *      - returns an int as decider
 *      - usage example: lessthan(v1, v2);
 *    vertswap(void* a, void* b)
 *      - callback function to swap to vertices' owners
 *      - usage example: vertswap(v1, v2);
 *    updateVertex(binheap* b, vertex* v, int a);
 *      - updates a vertex with a vew value
 *      - usage example: updateVertex(b, v, i);
 *    zeroVertexKey(vertex** a, binheap* b, int size)
 *      - scans the vertex array and finds the lowest vertex number in the PQ and zeroes it's key
 *      - usage example: zeroVertexKey(vArray, b, i);
 *    relaxEdges(binheap* b, table* t, vertex** a, vertex* v)
 *      - relaxes all of the vertices that are connected to a vertex
 *      - usage example: relaxEdges(b, t, a, v);
 *    createArray(int a)
 *      - creates an integer array to use as boolean flags
 *      - return address to first item in array
 *      - usage example: int** array = createArray(size);
 *    printWeight(int j)
 *      - cycles throught MST weight table and sums total weight of a tree
 *      - outputs weight to the screen
 *      - usage example: printWeight(size);
 *    printBFS(cdll* c)
 *      - Prints out the Breadth First Search Traversal of the nodes in a tree - stored in a CDLL
 *      - usage example: printBFS(c);
 *    outputNode(Node* n)
 *      - outputs a Node's name, key value, and predecessor name
 *      - usage example: outputNode(n);
 */
 
#include <stdlib.h>

#include "prim.h"


static void zeroVertexKey(vertex **, binheap *, int);
static void relaxEdges(binheap *, table *, vertex **, vertex *);
static int* createArray(int);
static void printWeight(int);
static void printBFS(cdll *);
static void outputNode(Node *);

int flag = 1;
int* weight;
int* MST;
cdll* BFS;
Node* n;

void primMain(binheap* b, table* t, vertex** a)
{
    weight = createArray(t->col);
    MST = createArray(t->col);
    BFS = newCDLL();
    vertex* v;

    zeroVertexKey(a, b, t->col);

    while(b->size)
    {
        v = (vertex*)b->extreme->value;
        if(v->key == t->extreme)
        {
            printBFS(BFS);
            printWeight(t->col);
            zeroVertexKey(a, b, t->col);
        }
        v = (vertex*)extractBinHeap(b);
        MST[v->name] = 1;
        relaxEdges(b, t, a, v);
        if(v->pred != v)
            v->level = v->pred->level + 1;
        n = newNode(v);
        insertNode(n, BFS);
        v->inQ = 0;
        weight[v->name] = v->key;
    }
    printBFS(BFS);
    printWeight(t->col);
}

int lessthan(void* a, void* b)
{
    vertex* v = (vertex*) a;
    vertex* w = (vertex*) b;

    int x = v->key;
    int y = w->key;

    if(x == y)
    {
        if(v->pred && w->pred)
        {
            if(v->pred->name < w->pred->name)return -1;
            if(v->pred->name > w->pred->name)return 1;
        }
        if(v->name < w->name) return -1;
        else return 1;
    }
    return x - y;
}

void vertswap(void* a, void* b)
{
    vertex* v = (vertex*)a;
    vertex* w = (vertex*)b;

    Node* t = v->owner;
    v->owner = w->owner;
    w->owner = t;
}

void updateVertex(binheap* b, vertex* v, int a)
{
    v->key = a;
    decreaseKey(b, v->owner, v);
}

static void zeroVertexKey(vertex** a, binheap* b, int size)
{
    vertex* v;

    for(int i = 0; i < size; i++)
    {
        v = a[i];
        if(v)
        {
            if(v->inQ)
            {
                updateVertex(b, v, 0);
                v->pred = v;
                return;
            }
        }
    }
}

static void relaxEdges(binheap* b, table* t, vertex** a, vertex* v)
{
    int begin = v->name;
    vertex* w;
    int weight;
    for(int i = 0; i < t->row; i++)
    {
        weight = getTableIndexWeight(t, begin, i);
        if(weight != t->initial)
        {
            w = a[i];
            if(w->key > weight && !MST[w->name])
            {
                updateVertex(b, w, weight);
                w->pred = v;
            }

        }
    }
}

static int* createArray(int a)
{
    int *b = malloc(sizeof(int) * a);
    for(int i = 0; i < a; i++)
        b[i] = 0;

    return b;
}

static void printWeight(int j)
{
    int gweight = 0;
    for(int i = 0; i < j; i++)
    {
        gweight = gweight + weight[i];
        weight[i] = 0;
    }

    printf("weight: %d\n", gweight);
}

static void printBFS(cdll* c)
{
    Node* min = NULL;
    Node* n;
    vertex* v;
    vertex* w;
    int level = 0;

    printf("0 : ");

    while(c->size)
    {
        min = NULL;
        n = c->head;
        v = NULL;
        w = NULL;
        for (int i = 1; i < c->size + 1; i++)
        {
            v = (vertex*)n->value;
            if(!min)
                min = n;
            else
            {
                w = (vertex*)min->value;
                if(v->level < w->level)
                    min = n;
                else if(v->level == w->level)
                {
                    if(v->name < w->name)
                        min = n;
                }
            }
            n = n->next;
        }
        min = removeNode(min, c);
        v = (vertex*)min->value;

        if(v->level != level)
            printf(";\n%d : ", ++level);
        else
        {
            if(level != 0)
                printf(", ");
        }
        outputNode(min);
    }
    printf(";\n");
}

static void outputNode(Node* n)
{
    vertex* v = (vertex*)n->value;
    if(v->pred == v)
        printf("%d", v->name);
    else
    {
        printf("%d(%d)%d", v->name, v->pred->name, v->key);
    }
}
