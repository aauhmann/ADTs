#pragma once

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

typedef int type;

typedef struct Node {
    struct Node* next;
    type data;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

void queue_initialize(Queue* queue);
bool queue_isEmpty(Queue queue);
void queue_insert(Queue* queue, type data);
type queue_remove(Queue* queue);
void queue_print(Queue queue);
type queue_front(Queue queue);
void queue_clear(Queue* queue);