//
// Created by Nafany on 19.05.2021.
//

#include "graph.h"
#include "graphMassive.h"

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

void freeFrom(From* from){
    if(from == NULL)
        return;
    while(from != NULL){
        From* cleaner = from;
        from = from->next;
        free(cleaner);
    }
}

void freeHead(Head* head){
    if(head == NULL)
        return;
    freeNode(head->ways);
    freeFrom(head->from);
    free(head->name);
    free(head);
}

Head* headInit(int x, int y, char* name){
    Head* head = (Head*)malloc(sizeof(Head));
    head->x = x;
    head->y = y;
    head->name = name;
    head->ways = NULL;
    head->from = NULL;
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
        addFrom(from, to);
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
    addFrom(from, to);
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
        removeFrom(&(*pointer)->from, x, y);
        deleteNode(&(*pointer)->ways, x, y);
        pointer++;
    }
    if(delete != NULL)
        freeHead(delete);
    return isDel;
}

int deleteWay(Graph* graph, int startX, int startY, int finX, int finY){
    Head** pointer = graph->heads;
    int delT = 0;
    int delF = 0;
    for(int i = 0; i < graph->nsize; i++){
        if((*pointer)->x == startX && (*pointer)->y == startY){
            deleteNode(&(*pointer)->ways, finX, finY);
            delT = 1;
        }
        if((*pointer)->x == finX && (*pointer)->y == finY){
            removeFrom(&(*pointer)->from, startX, startY);
            delF = 1;
        }
        if(delF + delT > 1)
            return 1;
    }
    return 0;
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

void addArray(DynArray** array, HeadMassive* head);

int fillMass(HeadMassive* d, HeadMassive*** massive, DynArray** stack, Node* node, int i, int h){
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

void addArray(DynArray** array, HeadMassive* head){
    if((*array)->nsize == (*array)->size){
        (*array)->heads = (HeadMassive**)realloc((*array)->heads, (10 + (*array)->size) * sizeof(HeadMassive*));
        (*array)->size += 10;
    }
    (*array)->heads[(*array)->nsize] = head;
    (*array)->nsize += 1;
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
            addArray(&stack, root);
            k = fillMass(root, &root->heads, &stack, root->head->ways, 0, 0);
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
        (*find)->massSize = fillMass(*find, &(*find)->heads, &stack, (*find)->head->ways, 0, 0);
        find = stack->heads + i;
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

Heads* graphs(Graph* graph){
/*     TODO:
     *  Сделать структуру с массивом вершин.
     *  Сделать структуру с массивом массивов вершин.
     *  В 1 структуру пихнуть весь граф и по основному графу составлять массивчики с вершинами (R и Q)
     *  Потом сравнивать 2 массива и генерировать новый с общими вершинами, по нему пройтись и из 1 массива со всеми
     *  вершинами.
     *  Вот так ходить пока в 1 массиве со всеми вершинами не останется ни одного элемента.
                                          звучит просто, согласись                                                   */
    Heads* allHeads = (Heads*)malloc(sizeof(Heads));
    allHeads->heads = (Head**)malloc(sizeof(Head*) * graph->nsize);
    allHeads->nsize = graph->nsize;
    allHeads->maxsize = graph->nsize;
    Head** pointer = graph->heads;
    for(int i = 0; i < graph->nsize; i++){
        allHeads->heads[i] = *pointer;
        pointer++;
    }

    while(allHeads->nsize != 0){
        Head* main
    }
}

void randomGenerate(Graph* graph, int size){
    graph->heads = realloc(graph->heads, size * sizeof(Head*) + 10);
    graph->size = size + 10;
    for(int i = 0; i < size; i++){
        char* text = malloc(sizeof(char) * 2);
        *text = 33 + rand() % 90;
        *(text + 1) = '\0';
        addHead(graph, headInit(i + 1, i + 1, text));
    }
    for(int i = 0; i < size * 2; i++){
        int from = rand()%size + 1;
        int to = rand()%size + 1;
        if(from != to) {
            addWay(graph, from, from, to, to, rand());
        }
    }
}

void addFrom(Head* from, Head* to){
        From* f = (From*)malloc(sizeof(From));
        f->next = to->from;
        f->head = from;
        to->from = f;
}

void removeFrom(From** from, int x, int y){
    From* deleter = *from;
    From* before = deleter;
    while(deleter != NULL){
        if(deleter->head->x == x && deleter->head->y == y){
            if(deleter == before){
                *from = deleter->next;
                free(deleter);
                return;
            }
            before->next = deleter->next;
            free(deleter);
            return;
        }
        before = deleter;
        deleter = deleter->next;
    }
}