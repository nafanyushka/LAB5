//
// Created by Nafany on 19.05.2021.
//

#include "graph.h"

void freeWay(Way* way){
    if(way == NULL)
        return;
    free(way);
}

void freeNode(Node* node){
    if(node == NULL)
        return;
    while(node != NULL){
        Node* cleaner = node;
        node = node->next;
        freeWay(cleaner->way);
        free(cleaner);
    }
}

void freeHead(Head* head){
    if(head == NULL)
        return;
    freeNode(head->ways);
    free(head->name);
    free(head);
}

Head* headInit(int x, int y, char* name){
    Head* head = (Head*)malloc(sizeof(Head));
    head->x = x;
    head->y = y;
    head->name = name;
    head->ways = NULL;
    return head;
}

Graph* graphInit(){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->heads = (Head**)malloc(10 * sizeof(Head*));
    graph->size = DEFAULT_SIZE;
    graph->nsize = 0;
    return graph;
}

int addHead(Graph* graph, Head* head){
    int i = 0;
    Head** placer = graph->heads;
    while(i < graph->nsize){
        if((**placer).x == head->x && (**placer).y == head->y){
            freeHead(head);
            return 0;
        }
        placer++;
        i++;
    }
    if(i > graph->size){
        graph->heads = (Head**)realloc(graph->heads, graph->size + sizeof(Head*) * 10);
        graph->size = graph->size + DEFAULT_SIZE;
    }
    (graph->heads)[i] = head;
    graph->nsize++;
    return 1;
}

int addWay(Graph* graph, int startX, int startY, int finX, int finY, int m){
    Head* from = NULL;
    Head* to = NULL;
    Head** finder = graph->heads;
    for(int i = 0; i < graph->nsize; i++){
        if((*finder)->x == startX && (*finder)->y == startY){
            from = *finder;
            if(to != NULL)
                break;
        }
        if((*finder)->x == finX && (*finder)->y == finY){
            to = *finder;
            if(from != NULL)
                break;
        }
        finder++;
    }
    if(to == NULL || from == NULL)
        return 0;
    Node* find = from->ways;
    Node* helper;
    if(from->ways == NULL){
        from->ways = (Node*)malloc(sizeof(Node));
        Way* way = (Way*)malloc(sizeof(Way));
        Node* node = from->ways;
        node->next = NULL;
        node->way = way;
        way->to = to;
        way->m = m;
        return 1;
    }
    while(find != NULL){
        if(find->way->to == to){
            return 0;
        }
        helper = find;
        find = find->next;
    }
    helper->next = (Node*)malloc(sizeof(Node));
    Node* node = helper->next;
    Way* way = (Way*)malloc(sizeof(Way));
    node->next = NULL;
    node->way = way;
    node->way->to = to;
    node->way->m = m;
    return 1;
}

void deleteNode(Node** node, int x, int y){
    Node* deleter = *node;
    Node* before = deleter;
    while(deleter != NULL){
        if(deleter->way->to->x == x && deleter->way->to->y == y) {
            if(before == deleter){
                *node = deleter->next;
                freeWay(deleter->way);
                free(deleter);
                return;
            }
            else{
                before->next = deleter->next;
                freeWay(deleter->way);
                free(deleter);
                return;
            }

        }
        deleter = deleter->next;
    }
}

int deleteHead(Graph* graph, int x, int y){
    Head** pointer = graph->heads;
    Head* delete = NULL;
    int isDel = 0;
    for(int i = 0; i < graph->nsize; i++){
        if((*pointer)->x == x && (*pointer)->y == y){
            delete = *pointer;
            *pointer = (graph->heads)[graph->nsize - 1];
            graph->nsize--;
            isDel = 1;
        }
        deleteNode(&(*pointer)->ways, x, y);
        pointer++;
    }
    if(delete != NULL)
        freeHead(delete);
    return isDel;
}

int deleteWay(Graph* graph, int startX, int startY, int finX, int finY){
    Head** pointer = graph->heads;
    for(int i = 0; i < graph->nsize; i++){
        if((*pointer)->x == startX && (*pointer)->y == startY){
            deleteNode(&(*pointer)->ways, finX, finY);
            return 1;
        }
    }
    return 1;
}

void printGraph(Graph* graph){
    Head** printer = graph->heads;
    printf("\nГРАФ:\n");
    for(int i = 0; i < graph->nsize; i++){
        printf("\tГраф Снюсов. {%d, %d}\t \"%s\":\t Пути в:", (*printer)->x, (*printer)->y, (*printer)->name);
        Node* printWay = (*printer)->ways;
        while(printWay != NULL){
            printf(" {%d, %d}", printWay->way->to->x, printWay->way->to->y);
            printWay = printWay->next;
        }
        printer++;
        printf("\n");
    }
    printf("\n");
}

void freeGraph(Graph* graph){

}

Head* findFrom(Graph* graph, int startX, int startY, int finX, int finY){

}

Way** findWay(Graph* graph, int startX, int startY, int finX, int finY){

}

Graph** graphs(Graph* graph){

}
