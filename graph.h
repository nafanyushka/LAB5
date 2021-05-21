//
// Created by Nafany on 19.05.2021.
//

#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#define DEFAULT_SIZE 10;

typedef struct Head Head;
typedef struct Way Way;
typedef struct Node Node;
typedef struct Graph Graph;


///////////////////////////////////////
typedef struct HeadMassive HeadMassive;
typedef struct DynArray DynArray;

struct HeadMassive{
    int h;
    Head* head;
    HeadMassive** heads;
    HeadMassive* prev;
    int massSize;
};

struct DynArray{
    HeadMassive** heads;
    int size;
    int nsize;
};
///////////////////////////////////////

struct Graph{
    Head** heads;
    int size;
    int nsize;
};

struct Node{
    Way* way;
    Node* next;
};

struct Way{
    int m;
    Head* to;
};

struct Head{
    Node* ways;
    int x;
    int y;
    char* name;
    char color;
};

Head* headInit(int x, int y, char* name);
Graph* graphInit();
int addHead(Graph* graph, Head* head);
int addWay(Graph* graph, int startX, int startY, int finX, int finY, int m);
int deleteHead(Graph* graph, int x, int y);
int deleteWay(Graph* graph, int startX, int startY, int finX, int finY);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);
HeadMassive* findFrom(Graph* graph, int startX, int startY, int finX, int finY);
void printWay(HeadMassive* from);
void freeTree(HeadMassive* root);
Way** findWay(Graph* graph, int startX, int startY, int finX, int finY);
Graph** graphs(Graph* graph);

#endif //LAB5_GRAPH_H
