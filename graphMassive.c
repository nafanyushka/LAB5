//
// Created by Nafany on 31.05.2021.
//

#include "graphMassive.h"

GraphMassive* initGraphMassive(){
    GraphMassive* graphMassive = (GraphMassive*)malloc(sizeof(GraphMassive));
    graphMassive->heads = (Heads**)malloc(10 * sizeof(Heads*));
    graphMassive->maxsize = 10;
    graphMassive->nsize = 0;
    return graphMassive;
}

Heads* initHeads(){
    Heads* heads = (Heads*)malloc(sizeof(Heads));
    heads->heads = (Head**)malloc(10 * sizeof(Head*));
    heads->maxsize = 10;
    heads->nsize = 0;
    return heads;
}

int checkHead(Heads* heads, Head* check){
    Head** pointer = heads->heads;
    for(int i = 0; i < heads->nsize; i++){
        if((*pointer) == check)
            return i;
        pointer++;
    }
    return -1;
}


int addToHeads(Heads* heads, Head* head){
    if(checkHead(heads, head) == -1)
        return 0;
    if(heads->nsize == heads->maxsize) {
        heads->heads = (Head **) realloc(heads->heads, (heads->maxsize + 10) * sizeof(Head *));
        heads->maxsize += 10;
    }
    heads->heads[heads->nsize] = head;
    heads->nsize++;
    return 1;
}

///////

int max(int a, int b){
    if(a >= b)
        return a;
    return b;
}

void freeHeads(Heads* a){
    free(a->heads);
    free(a);
}
///////

Heads* findCross(Heads* a, Heads* b){
    Heads* head = initHeads();
    head->heads = (Head**)realloc(head->heads, max(a->nsize, b->nsize) * sizeof(Head*));
    head->maxsize = max(a->nsize, b->nsize);
    if(a->nsize >= b->nsize){
        Head** pointer = b->heads;
        for(int i = 0; i < b->nsize; i++){
            int k = checkHead(a, *pointer);
            if(k != -1){
                addToHeads(head, b->heads[k]);
            }
            pointer++;
        }
    }
    else {
        Head **pointer = a->heads;
        for (int i = 0; i < a->nsize; i++) {
            int k = checkHead(b, *pointer);
            if (k != -1) {
                addToHeads(head, a->heads[k]);
            }
            pointer++;
        }
    }
    freeHeads(a);
    freeHeads(b);
    return head;
}

int deleteFromHeads(Heads* heads, Head* head){
    int i = checkHead(heads, head);
    if(i == -1)
        return 0;
    heads->heads[i] = heads->heads[heads->nsize];
    heads->nsize--;
    return 1;
}

int addGraphMassive(GraphMassive* massive, Heads* heads){
    if(massive->nsize == massive->maxsize){
        massive->heads = (Heads**)realloc(massive->heads, (massive->maxsize + 10 * sizeof(Heads*)));
        massive->maxsize += 10;
    }
    massive->heads[massive->nsize] = heads;
    massive->nsize++;
    return 1;
}

void freeGraphMassive(GraphMassive* massive){
    Heads** pointer = massive->heads;
    for(int i = 0; i < massive->nsize; i++){
        freeHeads(*pointer);
        pointer++;
    }
    free(massive->heads);
    free(massive);
}

void printHeads(Heads* heads){
    Head** pointer = heads->heads;
    for(int i = 0; i < heads->nsize; i++){
        printf("{%d, %d}", (*pointer)->x, (*pointer)->y);
        if(i + 1 != heads->nsize)
            printf(" ");
        pointer++;
    }
}

void printGraphMassive(GraphMassive* massive){
    Heads** pointer = massive->heads;
    for(int i = 0; i < massive->nsize; i++){
        printf("КСС%d: ", i + 1);
        printHeads(*pointer);
        printf("\n");
        pointer++;
    }
}