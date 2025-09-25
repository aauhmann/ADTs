#include "dll.h"

void list_initialize(List* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_insert(List* list, int pos, type data) {
    Node* new = (Node*)malloc(sizeof(Node));
    Node* aux = list->head;

    new->data = data;

    list->size++;
    
    if (pos <= 0 || list->head == NULL) {
        if (list->head != NULL)
            aux->prev = new;
        new->next = aux;
        new->prev = NULL;
        list->head = new;
        list->tail = new;
        printf("\nInserted at position %d", 0);
        return;
    }

    for (int i = 1; i <= pos; i++) {
        if (aux->next == NULL) {
            new->prev = aux;
            new->next = NULL;
            aux->next = new;
            list->tail = new;
            printf("\nInserted at position %d", i + 1);
            return;
        }
        if (i != pos)
            aux = aux->next;
    }

    new->prev = aux;
    new->next = aux->next;
    aux->next->prev = new;
    aux->next = new;

    printf("\nInserted at position %d", pos);
}

void list_remove(List* list, int pos) {
    Node* aux = list->head;

    if (list->head == NULL) {
        printf("Empty list");
        return;
    }

    if (pos <= 0) {
        list->head = aux->next;
        pos = 0;
    }

    for (int i = 0; i < pos; i++) {
        if (aux->next == NULL) {
            if (i == pos) {
                list->tail = aux->prev;
                break;
            }
            printf("Invalid position. List size: %d", list->size);
            return;
        }
            aux = aux->next;
    }

    list->size--;

    if (aux->next != NULL)
        aux->next->prev = aux->prev;
    if (aux->prev != NULL)
        aux->prev->next = aux->next;
    free(aux);

    printf("Removed position %d", pos);
}

void list_print(List list) {
    Node* aux = list.head;

    if (list.head == NULL) {
        printf("\nEmpty list");
        return;
    }

    printf("\n- PRINTING -");

    int i = 0;
    while (aux != NULL) {
        printf("\nNode %d:", i);
        printf("\n Int: %d\n", aux->data);
        i++;
        aux = aux->next;
    }

    printf("- END PRINTING -");
}

void list_reversePrint(List list) {
    Node* aux = list.tail;

    if (list.head == NULL) {
        printf("\nEmpty list");
        return;
    }

    printf("\n- REVERSE PRINTING -");

    int i = list.size - 1;
    while (i >= 0) {
        printf("\nNode %d:", i);
        printf("\n Int: %d\n", aux->data);
        i--;
        aux = aux->prev;
    }

    printf("- END PRINTING -");
}

void list_searchNode(List list, int pos) {
    Node* aux = list.head;

    if (list.head == NULL) {
        printf("Empty list");
        return;
    }

    printf("\n- SEARCHING -");

    for (int i = 0; i <= pos; i++) {
        if (aux->next == NULL) {
            if (i == pos)
                break;
            printf("Invalid position. List size: %d", list.size);
            return;
        }
        if (i != pos)
            aux = aux->next;
    }

    printf("\nNode %d", pos);
    printf("\nInt: %d", aux->data);

    printf("\n- END SEARCH -");
}

type list_getNode(List list, int pos) {

}

void list_clear(List* list) {
    Node* aux = list->head;

    if (list->head == NULL) {
        printf("\nEmpty list");
        return;
    }

    while (aux != NULL) {
        list->head = aux->next;
        free(aux);
        aux = list->head;
    }

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    printf("\nList emptied");
    printf("\nList Head: %p", list->head);
}