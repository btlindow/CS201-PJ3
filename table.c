/* VERSION 1.1.9.9.5
 *
 * scanner.c - Vertex Class
 *           - written by Ben Lindow
 *
 *    newTable(int nrow, int ncol, int init)
 *      - creates allocated space for a new table object
 *      - returns address to newly created table object
 *      - usage example: table* t = newTable(rows, cols, initialValue);
 *    newMatrix(int row, int col, int initial)
 *      - creates allocated space for a new N x M integer matrix inside the table
 *      - returns address of the table
 *      - usage example: int** matrix = newMatrix(rows, cols, initialValue);
 *    updateTableValue(int rown, int coln, int val, table* t)
 *      - updates a table value with a given integer
 *      - usage example: updateTableValue(rowNum, colNum, value, table);
 *    getTableIndexWeight(table* t, int a, int b)
 *      - serves as a table look up function
 *      - returns integer of table location
 *      - usage example: int weight = getTableIndexWeight(t, row, col);
 */

#include "table.h"

#include <stdlib.h>


table* newTable(int nrow, int ncol, int init)
{
    table* t = malloc(sizeof(table));
    if(!t) { fprintf(stderr, "out of memory"); exit(-1);}

    t->row = nrow;
    t->col = ncol;
    t->extreme = 0;
    t->initial = init;

    t->matrix = newMatrix(nrow, ncol, t->initial);

    return t;
}

int** newMatrix(int row, int col, int initial)
{
    int** t = malloc(sizeof(int*) * row);
    if(!t) { fprintf(stderr,"out of memory"); exit(-1);}

    for (int i = 0; i < row; i++)
    {
        t[i] = malloc(sizeof(int) * col);
        if(!t[i]) { fprintf(stderr,"out of memory"); exit(-1); }
    }

    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            t[i][j] = initial;

    return t;
}

void updateTableValue(int rown, int coln, int val, table* t)
{
    if(rown > t->row || coln > t->col) {fprintf(stderr, "out of table bound"); return;}
    if(t->matrix[rown][coln] != t->initial) return;
        t->matrix[rown][coln] = val;
}

int getTableIndexWeight(table* t, int a, int b)
{
    return t->matrix[a][b];
}
