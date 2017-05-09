/* VERSION 1.1.9.9.5
 *
 * scanner.c - binheap class functions
 *           - written by Ben Lindow
 *
 *    *newBinHeap(int (*c)(void *,void *), void (*s)(void*, void*))
 *      - allocates memory for a new binomial heap object
 *      - returns address to allocated space
 *      - usage example: binheap* b = *newBinHeap(function1, function2);
 *    insertBinHeap(binheap* b, void* v)
 *      - inserts a value into the binomial heap
 *      - returns a node to the newly inserted value
 *      - usage example: Node* n = insertBinHeap(b, v);
 *    *extractBinHeap(binheap* b)
 *      - extractMin operation for binheap acting as priority queue
 *      - returns a void* of the value on the top of the queue
 *      - usage example: void* v = extractBinHeap(b);
 *    decreaseKey(binheap* b, Node* n, void* v)
 *      - decrease key operation for biheap acting as priority queue
 *      - decreases a Node's value and bubles up the binheap
 *      - usage example: decreaseKey(b, n, v);
 *    bubbleUp(binheap* b, Node* n)
 *      - bubbles up a value until it's appropriate spot in the binheap
 *      - usage example: bubbleUp(b, n);
 *    deleteBinNode(binheap* b, Node* n)
 *      - deletes a node from the binheap
 *      - usage example: deleteBinNode(b, n);
 *    consolidate(binheap* b)
 *      - consolidates the rootlist of the binheap
 *      - usage example: consolidate(b);
 *    updateConsolidationArray(Node** array, Node* n, binheap* b)
 *      - updates the array with correct degree'd rootlist item that is used in consolidation
 *      - usage example: updateConsolidationArray(N, n, b);
 *    combine(binheap* b, Node* x, Node* y)
 *      - combines two nodes together making one the parent
 *      - return the Node of the "winning" parent
 *      - usage example: Node* p = combine(b, x, y);
 *    unionBinHeap(binheap* a, binheap* b)
 *      - combines two binheap objects together
 *      - usage example: unionBinHeap(b1, b2);
 *    makeArray(int a)
 *      - creates the consolidation array of size "a"
 *      - returns allocated space to the new Node array
 *      - usage example: Node** N = makeArray(size);
 *    updateExtreme(binheap* b)
 *      - updates the extreme value in the rootlist of a binheap
 *      - usage example: updateExtreme(b);
 *
 */

#include <stdlib.h>
#include <math.h>

#include "binheap.h"

/*static prototypes*/
static Node** makeArray(int);
static void updateExtreme(binheap *);

binheap *newBinHeap(int (*c)(void *,void *), void (*s)(void*, void*))
{
    binheap *b = malloc(sizeof(binheap));
    if (!b) { fprintf(stderr,"out of memory"); exit(-1); }

    b->comparator = c;
    b->swapper = s;
    b->rootlist = newCDLL();
    b->extreme = NULL;
    b->size = 0;

    return b;
}

Node* insertBinHeap(binheap* b, void* v)
{
    Node* n = newNode(v);
    n->parent = n;
    insertNode(n, b->rootlist);
    b->size++;
    consolidate(b);

    return n;
}

void *extractBinHeap(binheap* b)
{
    Node* n = b->extreme;
    n = removeNode(n, b->rootlist);
    mergeCDLL(n->children, b->rootlist);
    if(b->size == 1)
        b->extreme = NULL;
    else
        consolidate(b);
    b->size--;
    return n->value;
}

void decreaseKey(binheap* b, Node* n, void* v)
{
    n->value = v;
    bubbleUp(b, n);
    updateExtreme(b);
}

void bubbleUp(binheap* b, Node* n)
{
    if(n == n->parent) return;
    if(b->comparator(n->value, n->parent->value) >= 0) return;
    else
    {
        void* t = n->value;
        n->value = n->parent->value;
        n->parent->value = t;
        b->swapper(n->value, n->parent->value);
        bubbleUp(b, n->parent);
    }
}

void deleteBinNode(binheap* b, Node* n)
{
    decreaseKey(b, n, NULL);
    extractBinHeap(b);
}


void consolidate(binheap* b)
{
    int size = (int)log2((double)b->size) + 1;
    Node** array = makeArray(size);
    Node* n;

    while(!isEmptyCDLL(b->rootlist))
    {
        n = removeNode(b->rootlist->head, b->rootlist);
        updateConsolidationArray(array, n, b);
    }

    b->extreme = NULL;

    for(int i = 0; i < size; i++)
    {
        if(array[i])
        {
            if(!b->extreme || (b->comparator(array[i], b->extreme) < 0))
            {
                b->extreme = array[i];
                b->extreme->parent = b->extreme;
            }

            insertNode(array[i], b->rootlist);
            array[i]->parent = array[i];
        }
    }

    updateExtreme(b);
}

void updateConsolidationArray(Node** array, Node* n, binheap* b)
{
    int degree = n->children->size;
    while(array[degree])
    {
        n = combine(b, n, array[degree]);
        array[degree] = NULL;
        degree++;
    }
    array[degree] = n;
}

Node* combine(binheap* b, Node* x, Node* y)
{
    if(b->comparator(x->value, y->value) < 0)
    {
        insertNode(y, x->children);
        y->parent = x;
        return x;
    }
    else
    {
        insertNode(x, y->children);
        x->parent = y;
        return y;
    }
}

void unionBinHeap(binheap* a, binheap* b)
{
    b->size = b->size + a->size;
    mergeCDLL(a->rootlist, b->rootlist);
    a->extreme = NULL;
    consolidate(b);
}

static Node** makeArray(int a)
{
    Node** array = malloc(sizeof(Node*) * a);
    for (int i = 0; i < a; i++)
        array[i] = NULL;
    return array;
}

static void updateExtreme(binheap* b)
{
    if(b->rootlist->size == 1)
    {
        b->extreme = b->rootlist->head;
        b->extreme->parent = b->extreme;
        return;
    }

    b->extreme = b->rootlist->head;
    Node* n = b->rootlist->head;
    for(int i = 0; i < b->rootlist->size + 1; i++)
    {
        if(b->comparator(n->value, b->extreme->value) < 0)
            b->extreme = n;
        n->parent = n;
        n = n->next;
    }
}
