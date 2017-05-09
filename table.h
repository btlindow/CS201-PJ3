/* VERSION 1.2
 *
 * scanner.h - public interface to scanner.c, the scanner module
 *
 */

#ifndef table_h
#define table_h

#include <stdio.h>

typedef struct table
{
    int row;
    int col;
    int extreme;
    int initial;
    int** matrix;
}table;

table* newTable(int, int, int);
int** newMatrix(int, int, int);
void printTable(table *);
void updateTableValue(int, int, int, table *);
int getTableIndexWeight(table *, int, int);

#endif /* table_h */
