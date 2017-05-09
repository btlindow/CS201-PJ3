/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef cdll_h
#define cdll_h

#include <stdio.h>
#include "node.h"

typedef struct cdll
{
    int size;
    Node* head;
    Node* tail;
}cdll;

cdll* newCDLL(void);
void insertNode(Node *, cdll *);
Node* removeNode(Node*, cdll *);
void printCDLL(cdll *);
Node* findNode(void *, cdll *);
int isEmptyCDLL(cdll *);
void mergeCDLL(cdll *, cdll *);




#endif /* cdll_h */
