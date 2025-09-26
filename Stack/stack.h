#pragma once

#include <stdlib.h>
#include <stdio.h>

#define DATA_NULL 0

typedef int type;

typedef struct Node {
    struct Node* prev;
    type data;
} Node;

typedef struct Stack {
    Node* top;
    int size;
} Stack;

void stack_initialize(Stack* stack);
void stack_push(Stack* stack, type data);
type stack_pop(Stack* stack);
void stack_peek(Stack stack);
void stack_print(Stack stack);
void stack_clear(Stack* stack);