/* VERSION 1.1.9.9.5
 *
 * scanner.c - Node class for C
 *           - written by Ben Lindow
 *
 *    newNode(void* v)
 *      - creates allocated space for a new Node object with value v
 *      - returns address to newly created Node
 *      - usage example: Nodes* n = newNode(v)
 */

#include <stdlib.h>

#include "node.h"
#include "cdll.h"
#include "vertex.h"

Node* newNode(void* v)
{
    Node* n = malloc(sizeof(Node));
    if(!n) { fprintf(stderr,"out of memory"); exit(-1); }

    n->value = v;
    n->children = newCDLL();
    n->parent = NULL;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

