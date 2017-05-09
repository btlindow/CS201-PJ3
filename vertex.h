/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef vertex_h
#define vertex_h

#include <stdio.h>
#include "binheap.h"

struct Node;
typedef struct vertex
{
    int key;
    int name;
    int inQ;
    int level;
    struct vertex* pred;
    struct Node* owner;
}vertex;

vertex* newVertex(int);
#endif /* vertex_h */
