#include "deque.h"

void deque_initialize(Deque* deque) {
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

bool deque_isEmpty(Deque deque) {
    if (deque.front == NULL)
        return true;
    else
        return false;
}

void deque_insert(Deque* deque, type data, Location loc) {
    Node* new = (Node*)malloc(sizeof(Node));

    new->data = data;
    deque->size++;

    if (deque_isEmpty(*deque)) {
        deque->front = new;
        deque->rear = new;
    } else if (loc == REAR) {
        deque->rear->next = new;
        deque->rear = new;
        new->next = NULL;
    } else {
        Node* aux = deque->front;
        deque->front = new;
        new->next = aux;
    }

    printf("New size: %d", deque->size);
}

void deque_remove(Deque* deque, Location loc) {
    if (deque_isEmpty(*deque)) {
        printf("Empty deque");
        return;
    }

    Node* aux = deque->front;

    deque->size--;

    if (loc == FRONT) {
        aux = deque->front->next;
        free(deque->front);
        deque->front = aux;
    } else {
        while (aux->next != deque->rear)
            aux = aux->next;

            aux->next = NULL;
            free(deque->rear);
            deque->rear = aux;
    }

    printf("\nNew size: %d", deque->size);
}

void deque_print(Deque deque) {
    if (deque_isEmpty(deque)) {
        printf("\nEmpty deque");
        return;
    }

    printf("\n - PRINTING -");

    int i = 0;
    while (i < deque.size) {
        printf("\nNode %d:", i);
        printf("\n Int: %d", deque.front->data);
        deque.front = deque.front->next;
        i++;
    }

    printf("\n- END PRINTING -");
}

void deque_front(Deque deque) {
    if (deque_isEmpty(deque)) {
        printf("\nEmpty deque");
        return;
    }

    printf("\n- FRONT NODE -");
    printf("\n  Int: %d", deque.front->data);
}

void deque_rear(Deque deque) {
    if (deque_isEmpty(deque)) {
        printf("\nEmpty deque");
        return;
    }

    printf("\n- REAR NODE -");
    printf("\n  Int: %d", deque.rear->data);
}

void deque_clear(Deque* deque) {
    if (deque_isEmpty(*deque)) {
        printf("\nEmpty deque");
        return;
    }

    Node* aux = deque->front;

    while (aux != NULL) {
        deque->front = deque->front->next;
        free(aux);
        aux = deque->front;
    }

    deque->size = 0;

    printf("\nDeque emptied");
}