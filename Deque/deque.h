#pragma once

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#define type int

typedef enum {FRONT, REAR} Location;

typedef struct Node {
    struct Node* next;
    type data;
} Node;

typedef struct Deque {
    Node* front;
    Node* rear;
    int size;
} Deque;

void deque_initialize(Deque* deque);
bool deque_isEmpty(Deque deque);
void deque_insert(Deque* deque, type data, Location loc);
void deque_remove(Deque* deque, Location loc);
void deque_print(Deque deque);
void deque_front(Deque deque);
void deque_rear(Deque deque);
void deque_clear(Deque* deque);