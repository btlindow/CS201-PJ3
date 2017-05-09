/* VERSION 1.1.9.9.5
 *
 * scanner.c - CDLL class functions
 *           - written by Ben Lindow
 *
 *    newCDLL()
 *      - creates allocated space for a new CDLL object
 *      - returns address of new CDLL
 *      - usage example: CDLL* c = newCDLL();
 *    insertNode(Node* n, cdll* c)
 *      - inserts a node into the CDLL
 *      - usage example: insertNode(n, c);
 *    removeNode(Node* n, cdll* c)
 *      - removes a node from a specific CDLL
 *      - returns a pointer to the removed Node
 *      - usage example: Node* n = removeNode(p, c);
 *    findNode(void* v, cdll* c)
 *      - finds a node in a CDLL of value v
 *      - returns a node pointed to that found value
 *      - Node* f = findNode(v, c);
 *    isEmptyCDLL(cdll* c)
 *      - boolean function to determine if a CDLL is empty
 *      - returns 0 if it is not empty
 *      - else returns 1
 *      - usage example: if(isEmptyCDLL(c));
 *    mergeCDLL(cdll* a, cdll* b)
 *      - merges all of the nodes of one CDLL to the other
 *      - usage example: mergeCDLL(c1, c2);
 */
 
#include <stdlib.h>

#include "cdll.h"


cdll* newCDLL()
{
    cdll *c = malloc(sizeof(cdll));
    if(!c) { fprintf(stderr,"out of memory"); exit(-1); }

    c->size = 0;
    c->head = NULL;
    c->tail = NULL;

    return c;
}

void insertNode(Node* n, cdll* c)
{
    if(c->size == 0)
    {
        c->head = n;
        c->tail = n;
    }
    else
    {
        c->tail->next = n;
        n->prev = c->tail;
        n->next = c->head;
        c->tail = c->tail->next;
    }

    c->head->prev = c->tail;
    c->size++;
}

Node* removeNode(Node* n, cdll* c)
{
    if(c->size == 1)
    {
        c->head = NULL;
        c->tail = NULL;
        c->size = 0;
    }
    else
    {
        if(n == c->head)
        {
            c->head = c->head->next;
            c->tail->next = c->head;
            c->head->prev = c->tail;
        }
        else if(n == c->tail)
        {
            c->tail = c->tail->prev;
            c->tail->next = c->head;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
        }
        c->size--;
    }
    n->next = NULL;
    n->prev = NULL;

    return n;
}

Node* findNode(void* v, cdll* c)
{
    if(isEmptyCDLL(c)) return NULL;

    Node* n = c->head;
    int count = c->size + 1;

    while(count)
    {
        if(*(int*)n->value == *(int*)v)
            break;
        n = n->next;
        count--;
    }

    if(count) return n;
    else return NULL;
}

int isEmptyCDLL(cdll* c)
{
    if(c->size == 0) return 1;
    else return 0;
}

void mergeCDLL(cdll* a, cdll* b)
{
    Node* n;
    while(!isEmptyCDLL(a))
    {
        n = removeNode(a->head, a);
        insertNode(n, b);
        if(b->head->parent == b->head)
            n->parent = n;
        else
            n->parent = b->head->parent;
    }
}
