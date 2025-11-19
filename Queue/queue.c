#include "queue.h"

Queue queueInitialize() {
    return (Queue){NULL, NULL, 0};
}

static bool queueIsEmpty(Queue queue) {
    if (queue.head == NULL)
        return true;
    else
        return false;
}

void queueInsert(Queue* queue, type data) {
    QNode* new = (QNode*)malloc(sizeof(QNode));

    new->data = data;
    new->next = NULL;
    queue->size++;

    if (queueIsEmpty(*queue)) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }

    printf("New size: %d", queue->size);
}

void queueNodeRemove(Queue* queue) {
    if (queueIsEmpty(*queue)) {
        printf("\nEmpty queue");
        return;
    }

    QNode* aux = queue->head;

    queue->size--;

    aux = queue->head->next;
    free(queue->head);
    queue->head = aux;

    printf("\nNew size: %d", queue->size);
}

void queuePrint(Queue queue) {
    if (queueIsEmpty(queue)) {
        printf("\nEmpty queue");
        return;
    }

    printf("\n - PRINTING -");
    printf("\n\n->");

    while (queue.head != NULL) {
        printf("\n%d", queue.head->data);
        queue.head = queue.head->next;
    }

    printf("\n<-");
    printf("\n\n- END PRINTING -");
}

QNode* queuePeek(Queue queue) {
    if (queueIsEmpty(queue)) {
        printf("\nEmpty queue");
        return NULL;
    }

    printf("\n- FIRST NODE -");
    printf("\n  Int: %d", queue.head->data);

    return queue.head;
}

void queueClear(Queue* queue) {
    if (queueIsEmpty(*queue)) {
        printf("\nEmpty queue");
        return;
    }

    QNode* aux = queue->head;

    while (aux != NULL) {
        queue->head = queue->head->next;
        free(aux);
        aux = queue->head;
    }

    queue->size = 0;

    printf("\nQueue emptied");
}