/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef Node_h
#define Node_h

#include <stdio.h>

#include "node.h"


struct cdll;

typedef struct Node
{
    void* value;
    struct Node* parent;
    struct Node* next;
    struct Node* prev;
    struct cdll* children;
}Node;

Node* newNode(void*);
void printNode(Node *);

#endif /* Node_h */
