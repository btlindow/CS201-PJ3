/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef binheap_h
#define binheap_h

#include <stdio.h>
#include "node.h"
#include "cdll.h"

typedef struct binheap
{
    int size;
    int degree;
    int (*comparator)(void*, void*);
    void (*swapper)(void*, void*);
    Node* extreme;
    cdll* rootlist;
} binheap;



binheap *newBinHeap(int (*)(void *,void *), void (*)(void *, void *));
Node* insertBinHeap(binheap *,void *);
void *extractBinHeap(binheap *);
void decreaseKey(binheap *, Node *, void *);
void bubbleUp(binheap *, Node *);
void consolidate(binheap *);
void updateConsolidationArray(Node **, Node *, binheap *);
Node* combine(binheap *, Node *, Node *);
void deleteBinNode(binheap *, Node *);
void unionBinHeap(binheap *, binheap *);
void printHeap(binheap *);

#endif /* binheap_h */
