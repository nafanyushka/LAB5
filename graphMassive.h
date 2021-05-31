//
// Created by Nafany on 31.05.2021.
//

#ifndef LAB5_GRAPHMASSIVE_H
#define LAB5_GRAPHMASSIVE_H

#include "graph.h"

typedef struct Heads Heads;
typedef struct GraphMassive GraphMassive;

struct GraphMassive{
    Heads** heads;
    int nsize;
    int maxsize;
};

struct Heads{
    Head** heads;
    int nsize;
    int maxsize;
};


GraphMassive* initGraphMassive();

Heads* initHeads();

int checkHead(Heads* heads, Head* check);

void printGraphMassive(GraphMassive* massive);

void printHeads(Heads* heads);

void freeGraphMassive(GraphMassive* massive);

int addGraphMassive(GraphMassive* massive, Heads* heads);

int deleteFromHeads(Heads* heads, Head* head);

Heads* findCross(Heads* a, Heads* b);

int addToHeads(Heads* heads, Head* head);

void freeHeads(Heads* a);



#endif //LAB5_GRAPHMASSIVE_H
