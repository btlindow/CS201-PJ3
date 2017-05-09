/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef prim_h
#define prim_h

#include <stdio.h>

#include "binheap.h"
#include "vertex.h"
#include "table.h"
#include "cdll.h"

void primMain(binheap *, table *, vertex **);
int lessthan(void *, void *);
void updateVertex(binheap *, vertex *, int);
void vertswap(void *, void *);



#endif /* prim_h */
