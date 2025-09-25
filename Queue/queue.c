#include "queue.h"

void queue_initialize(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

bool queue_isEmpty(Queue queue) {
    if (queue.front == NULL)
        return true;
    else
        return false;
}

void queue_insert(Queue* queue, type data) {
    Node* new = (Node*)malloc(sizeof(Node));

    new->data = data;
    queue->size++;

    if (queue_isEmpty(*queue)) {
        queue->front = new;
        queue->rear = new;
    } else {
        queue->rear->next = new;
        queue->rear = new;
        new->next = NULL;
    }

    printf("New size: %d", queue->size);
}

type queue_remove(Queue* queue) {
    if (queue_isEmpty(*queue)) {
        printf("\nEmpty queue");
        return;
    }

    Node* aux = queue->front;
    type data = queue->front->data;

    queue->size--;

    aux = queue->front->next;
    free(queue->front);
    queue->front = aux;

    printf("\nNew size: %d", queue->size);

    return data;
}

void queue_print(Queue queue) {
    if (queue_isEmpty(queue)) {
        printf("\nEmpty queue");
        return;
    }

    printf("\n - PRINTING -");

    int i = 0;
    while (i < queue.size) {
        printf("\nNode %d:", i);
        printf("\n Int: %d", queue.front->data);
        queue.front = queue.front->next;
        i++;
    }

    printf("\n- END PRINTING -");
}

type queue_front(Queue queue) {
    if (queue_isEmpty(queue)) {
        printf("\nEmpty queue");
        return;
    }

    printf("\n- FIRST NODE -");
    printf("\n  Int: %d", queue.front->data);

    return queue.front->data;
}

void queue_clear(Queue* queue) {
    if (queue_isEmpty(*queue)) {
        printf("\nEmpty queue");
        return;
    }

    Node* aux = queue->front;

    while (aux != NULL) {
        queue->front = queue->front->next;
        free(aux);
        aux = queue->front;
    }

    queue->size = 0;

    printf("\nQueue emptied");
}