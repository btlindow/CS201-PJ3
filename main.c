//  Created by Benjamin Lindow on 11/22/16.
//  Copyright © 2016 Benjamin Lindow. All rights reserved.
//
//  Project3 Driver File
//
//  A program to exercise prim's algorithm on an undirected graph.
//
//
//
//  Program Execution
//  -----------------
//                                                          |
//  prim [FILENAME]                                         |
//                                                          |
//  [FILENAME] - "graph1.txt"                               |
//                                                          |
//  *********************************************************
//                                                          |
//                                                          |
//  Sample Call                                             |
//  -----------                                             |
//                                                          |
//  prim graph1.txt                                         |
//  prim graph2.txt                                         |
//                                                          |
//  *********************************************************
//                                                         
//
//
//
/* VERSION 1.1.9.9.5
 *
 * main.c    - driver file for Prim's Algorithm
 *           - written by Ben Lindow
 *
 *    validateOptions(int, char **)
 *      - verifies correct count and type of arguments passed
 *      - usage example: validateOptions(argc, argv);
 *
 *    readFile()
 *      - reads from file and populates the vertex array and adjaceny matrix
 *      - usage example: readFile()
 *
 *    readWeight()
 *      - reads weight of a Node. Burns a token if it reads an integer
 *      - usage example: readWeight()
 *
 *    createTable()
 *      - creates the adjacency matrix from sizes found in readFile()
 *      - usage example: createTable()
 *
 *    newVertArray(int size)
 *      - creates vertex array from size fround in readFile()
 *      - usage example: newVertArray(int size)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "binheap.h"
#include "scanner.h"
#include "node.h"
#include "prim.h"
#include "table.h"
#include "vertex.h"

/*global variable*/
FILE* fp;
binheap* b;
table* t;
char* filename;
vertex** a;

/*static prototypes*/
void validateOptions(int, char **);
void readFile(void);
int readWeight(void);
void createTable(void);
vertex** newVertArray(int);

int main(int argc, char **argv)
{
    validateOptions(argc, argv);
    b = newBinHeap(lessthan, vertswap);
    validateOptions(argc, argv);
    createTable();
    readFile();
    primMain(b, t, a);
    
    return 0;
}

void validateOptions(int argc, char **argv)
{
    if(argc != 2) {fprintf(stderr, "Invalid Argument Count\n"); exit(-1);}
    fp = fopen(argv[1], "r");
    filename = argv[1];
    if(!fp) {fprintf(stderr, "Invalid File Name\n"); exit(-1);}
    fclose(fp);
}

void readFile()
{
    fp = fopen(filename, "r");
    vertex* v;
    int line[3];
    line[0] = readInt(fp);
    while(!feof(fp))
    {
        line[1] = readInt(fp);
        line[2] = readWeight();
        
        updateTableValue(line[0], line[1], line[2], t);
        updateTableValue(line[1], line[0], line[2], t);
        
        
        if(!a[line[0]])
        {
            v = newVertex(line[0]);
            a[line[0]] = v;
            v->key = t->extreme;
            v->owner = insertBinHeap(b, v);
        }
        
        if(!a[line[1]])
        {
            v = newVertex(line[1]);
            a[line[1]] = v;
            v->key = t->extreme;
            v->owner = insertBinHeap(b, v);
        }
        
        line[0] = readInt(fp);
    }
}

int readWeight()
{
    char* str = readToken(fp);
    if (str[0] == ';') return 1;
    else
    {
        int a = atoi(str);
        str = readToken(fp);
        return a;
    }
}

void createTable()
{
    fp = fopen(filename, "r");
    
    int line[3];
    int maxWeight = 0;
    
    line[0] = readInt(fp);
    int max = line[0];
    
    while(!feof(fp))
    {
        line[1] = readInt(fp);
        line[2] = readWeight();
        
        if(line[0] >= line[1])
        {
            if(line[0] > max)
                max = line[0];
        }
        else if(line[1] > max)
            max = line[1];
        
        if(line[2] > maxWeight)
            maxWeight = line[2];

        
        line[0] = readInt(fp);
    }
    fclose(fp);
    
    t = newTable(max+1, max+1, -1);
    t->extreme = maxWeight + 1;
    a = newVertArray(t->col);
}

vertex** newVertArray(int size)
{
    vertex** v = malloc(sizeof(vertex*) * size);
    for(int i = 0; i < size; i++) v[i] = NULL;
    return v;
}

