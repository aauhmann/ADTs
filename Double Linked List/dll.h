#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int type;

typedef struct Node {
    type data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

void list_initialize(List* list);
void list_insert(List* list, int pos, type data);
void list_remove(List* list, int pos);
void list_print(List list);
void list_reversePrint(List list);
void list_searchNode(List list, int pos);
type list_getNode(List list, int pos);
void list_clear(List* list);