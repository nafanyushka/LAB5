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
    head->color = 'W';
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
        printf("\tГраф Снюсов. {%d, %d}\t \"%s\", цвет: \'%c\':\t Пути в:", (*printer)->x, (*printer)->y,
               (*printer)->name, (*printer)->color);
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
    Head** deleter = graph->heads;
    for(int i = 0; i < graph->nsize; i++){
        freeHead(*deleter);
        deleter++;
    }
}



HeadMassive* initHeadM(Head* head, int h){
    HeadMassive* hm;
    hm = (HeadMassive*)malloc(sizeof(HeadMassive));
    hm->h = h;
    hm->head = head;
    hm->heads = NULL;
    hm->massSize = 0;
    hm->prev = NULL;
    return hm;
}

void addArray(DynArray* array, HeadMassive* head);

int fillMass(HeadMassive* d, HeadMassive*** massive, DynArray* stack, Node* node, int i, int h){
    if(node == NULL) {
        (*massive) = (HeadMassive**)malloc(sizeof(Head*) * i);
        return 0;
    }
    if(node->way->to->color == 'W'){
        int k = fillMass(d, massive, stack, node->next, i + 1, h);
        node->way->to->color = 'G';
        (*massive)[i] = initHeadM(node->way->to, d->h + 1);
        (*massive)[i]->prev = d;
        addArray(stack, (*massive)[i]);
        return k + 1;
    }
    else{
        return fillMass(d, massive, stack, node->next, i, h);
    }

}

DynArray* initArray(){
    DynArray* array = (DynArray*)malloc(sizeof(struct DynArray));
    array->heads = (HeadMassive**)malloc(10 * sizeof(HeadMassive*));
    array->nsize = 0;
    array->size = 10;
    return array;
}

void addArray(DynArray* array, HeadMassive* head){
    if(array->nsize == array->size){
        array->heads = (HeadMassive**)realloc(array->heads, (10 + array->size) * sizeof(HeadMassive*));
        array->size += 10;
    }
    array->heads[array->nsize] = head;
    array->nsize += 1;
}

void freeTree(HeadMassive* root){
    for(int i = 0; i < root->massSize; i++){
        freeTree(root->heads[i]);
    }
    root->head->color = 'W';
    free(root->heads);
    free(root);
}

HeadMassive* findFrom(Graph* graph, int startX, int startY, int finX, int finY){
    int i;
    DynArray* stack = initArray();
    HeadMassive* start = NULL;
    Head** finder = graph->heads;
    HeadMassive* root = NULL;
    int k = 0;
    for(i = 0; i < graph->nsize; i++){
        if((*finder)->x == startX && (*finder)->y == startY){
            root = initHeadM(*finder, 0);
            addArray(stack, root);
            k = fillMass(root, &root->heads, stack, root->head->ways, 0, 0);
            root->massSize = k;
            root->head->color = 'B';
            break;
        }
        if(i + 1 == graph->nsize) {
            free(stack);
            return NULL;
        }
        finder++;
    }
    i = 1;
    HeadMassive** find = (stack->heads) + i;
    while(i != stack->nsize){
        if((*find)->head->x == finX && (*find)->head->y == finY)
            start = (*find);
        (*find)->massSize = fillMass(*find, &(*find)->heads, stack, (*find)->head->ways, 0, 0);
        (*find)->head->color = 'B';
        find++;
        i++;
    }
    if(start == NULL){
        for(int j = 0; j < stack->nsize; j++){
            stack->heads[j]->head->color = 'W';
            free(stack->heads[j]->heads);
            free(stack->heads[j]);
        }
    }
    free(stack->heads);
    free(stack);
   return start;
}

void printWay(HeadMassive* from){
    if(from == NULL)
        return;
    printWay(from->prev);
    printf("{%d, %d} -> ", from->head->x, from->head->y);
}

Way** findWay(Graph* graph, int startX, int startY, int finX, int finY){

}

Graph** graphs(Graph* graph){

}
