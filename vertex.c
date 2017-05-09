/* VERSION 1.1.9.9.5
 *
 * scanner.c - Vertex Class
 *           - written by Ben Lindow
 *
 *    newVertex(int n)
 *      - creates a new vertex object with integer value
 *      - returns address to newly created vertex object
 *      - usage example: vertex* v = newVertex(i);
 */

#include "vertex.h"

#include <stdlib.h>

vertex* newVertex(int n)
{
    vertex* v = malloc(sizeof(vertex));
    if (!v) {fprintf(stderr, "out of memory\n"); exit(-1);}

    v->key = 0;
    v->level = 0;
    v->inQ = 1;
    v->owner = NULL;
    v->pred = NULL;
    v->name = n;

    return v;
}
