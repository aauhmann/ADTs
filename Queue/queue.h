#pragma once

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

typedef int type;

typedef struct s_QueueNode {
    struct s_QueueNode* next;
    type data;
} QNode;

typedef struct s_Queue {
    QNode* head;
    QNode* tail;
    int size;
} Queue;

Queue queueInitialize();
void queueInsert(Queue* queue, type data);
void queueNodeRemove(Queue* queue);
void queuePrint(Queue queue);
QNode* queuePeek(Queue queue);
void queueClear(Queue* queue);