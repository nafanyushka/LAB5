//
// Created by Nafany on 19.05.2021.
//

#include "dialogue.h"

void dialogue(){
    Graph* graph = graphInit();
    int x, y, choose;
    printf("Если хотите сгенерировать граф, введите число вершин, либо 0 и меньше, если нет.\n");
    choose = getInt();
    if(choose > 0){
        printf("Генерация графа.\n");
        randomGenerate(graph, choose);
    }
    char* name;
    do{
        printf("Введите 1, чтобы вывести граф.\n"
               "Введите 2, чтобы добавить вершину.\n"
               "Введите 3, чтобы добавить путь.\n"
               "Введите 4, чтобы удалить вершину.\n"
               "Введите 5, чтобы удалить путь.\n"
               "Введите 6, чтобы найти путь ИЗ В.\n"
               "Введите 0, чтобы выйти из программы.\n");
        Head* head;
        HeadMassive* tree;
        int finX, finY, m;
        choose = getInt();
        switch(choose){
            case 1:
                printGraph(graph);
                break;
            case 2:
                printf("Введите x: ");
                x = getInt();
                printf("Введите y: ");
                y = getInt();
                do {
                    printf("Введите имя высоты: ");
                    name = get_String();
                } while(strlen(name) < 1);
                head = headInit(x, y, name);
                addHead(graph, head);
                break;
            case 3:
                printf("Введите начальный x: ");
                x = getInt();
                printf("Введите начальный y: ");
                y = getInt();
                printf("Введите конечный x: ");
                finX = getInt();
                printf("Введите конечный y: ");
                finY = getInt();
                printf("Введите вес ребра: ");
                m = getInt();
                addWay(graph, x, y, finX, finY, m);
                break;
            case 4:
                printf("Введите x: ");
                x = getInt();
                printf("Введите y: ");
                y = getInt();
                deleteHead(graph, x, y);
                break;
            case 5:
                printf("Введите начальный x: ");
                x = getInt();
                printf("Введите начальный y: ");
                y = getInt();
                printf("Введите конечный x: ");
                finX = getInt();
                printf("Введите конечный y: ");
                finY = getInt();
                deleteWay(graph, x, y, finX, finY);
                break;
            case 6:
                printf("Введите начальный x: ");
                x = getInt();
                printf("Введите начальный y: ");
                y = getInt();
                printf("Введите конечный x: ");
                finX = getInt();
                printf("Введите конечный y: ");
                finY = getInt();
                tree = findFrom(graph, x, y, finX, finY);
                printf("\n");
                printWay(tree);
                printf("Конец пути!\n");
                if(tree != NULL) {
                    while (tree->prev != NULL) {
                        tree = tree->prev;
                    }
                    freeTree(tree);
                }
                break;
            default:
                break;
        }

    }while(choose != 0);
}