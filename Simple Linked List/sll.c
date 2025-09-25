#include "sll.h"

Node* initialize() {
    printf("\nList initialized\n");
    return NULL;
}

void printList(Node* list) {
    Node* aux = list;
    int i = 0;

    if (list == NULL)
        printf("\nEmpty list\n");
    else {
        while (aux != NULL) {
            i++;
            printf("\n--Object %d--", i);
            printf("\nID: %d", aux->obj.id);
            printf("\nPrice: %.2f", aux->obj.price);
            printf("\nStock: %d\n", aux->obj.stock);
            aux = aux->next;
        }
        printf("\n");
    }
}

Object getObject(Node* list, int id) {
    Node* aux = list;

    while (aux->obj.id != id) {
        if (aux->next == NULL) {
            printf("\nObject ID'd %d not found\n", id);
            return OBJECT_NULL;
        } else
            aux = aux->next;
    }

    printf("Object ID'd %d succesfully returned\n", id);

    return aux->obj;
}

Node* insertFirst(Node* list, Object obj) {
    Node* new;

    new = (Node*)malloc(sizeof(Node));

    new->obj = obj;
    new->next = list;

    printf("\nObject inserted\n");

    return new;
}

Node* insertLast(Node* list, Object obj) {
    Node* new;
    Node* aux = list;

    new = (Node*)malloc(sizeof(Node));

    new->obj = obj;
    new->next = NULL;

    if (list == NULL)
        list = new;
    else {
        while (aux->next != NULL)
            aux = aux->next;
    
        aux->next = new;
    }

    printf("\nObject inserted\n");

    return list;
}

Node* insertRandom(Node* list, Object obj, int pos) {
    Node* new;
    Node* aux = list;
    Node* prev;

    new = (Node*)malloc(sizeof(Node));

    new->obj = obj;

    if (pos == 0) {
        new->next = aux;
        printf("Inserted at the beginning (position 0)");
        return new;
    }
        

    for (int i = 0; i < pos; i++) {
        if (aux == NULL) {
            printf("Invalid position: inserted at the end (position %d)", i + 1);
            prev->next = new;
            new->next = NULL;
            return list;
        } else
            prev = aux;
            aux = aux->next;
    }

    prev->next = new;
    new->next = aux;

    printf("Inserted at position %d", pos);

    return list;
}

Node* removeObject(Node* list, int id) {
    Node* aux = list;
    Node* prev = NULL;

    if (list == NULL)
        return list;

    if (list->obj.id == id) {
        list = aux->next;
        free(aux);
        printf("\nObject ID'd %d removed\n", id);
        return list;
    }

    while (aux->obj.id != id) {
        if (aux->next == NULL) {
            printf("\nObject ID'd %d not found\n", id);
            return list;
        }
        prev = aux;
        aux = aux->next;
    }

    prev->next = aux->next;

    free(aux);
    
    printf("\nObject ID'd %d removed\n", id);

    return list;
}

Node* destruct(Node* list) {
    Node* aux = list;
    Node* next;

    while (aux != NULL) {
        next = aux->next;
        free(aux);
        aux = next;
    }

    printf("\nList destroyed\n");

    return NULL;
}