#include "stack.h"

void stack_initialize(Stack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

void stack_push(Stack* stack, type data) {
    Node* aux = stack->top;
    Node* new = (Node*)malloc(sizeof(Node));
    
    new->data = data;
    stack->size++;

    if (aux == NULL) {
        stack->top = new;
        new->prev = NULL;
    } else {
        new->prev = stack->top;
        stack->top = new;
    }

    printf("New stack size: %d", stack->size);
}

type stack_pop(Stack* stack) {
    Node* aux = stack->top;
    type data = stack->top->data;

    if (aux == NULL) {
        printf("\nEmpty stack");
        return DATA_NULL;
    }

    stack->size--;

    stack->top = aux->prev;
    free(aux);

    printf("\nNew stack size: %d", stack->size);

    return data;
}

void stack_peek(Stack stack) {
    printf("\n- STACK TOP -");
    printf("\n %d", stack.top->data);
}

void stack_print(Stack stack) {
    Node* aux = stack.top;

    if (aux == NULL) {
        printf("\nEmpty list");
        return;
    }
    
    printf("\n- PRINTING STACK -");
    
    while (aux != NULL) {
        printf("\n %d", aux->data);
        aux = aux->prev;
    }

    printf("\n- END PRINTING -");
}

void stack_clear(Stack* stack) {
    Node* aux;

    if (stack->top == NULL) {
        printf("\nStack empty");
        return;
    }

    while (stack->top != NULL) {
        aux = stack->top->prev;
        free(stack->top);
        stack->top = aux;
    }

    printf("\nStack cleared");

    stack->size = 0;
}