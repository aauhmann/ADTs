#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float price;
    int stock;
} Object;

typedef struct StructNode Node;
struct StructNode {
    Object obj;
    Node* next;
};

#define OBJECT_NULL (Object){0, 0, 0}

/// @brief ### Initializes a simple liked list
/// @return A pointer to the first node of the list
Node* initialize();

/// @brief ### Prints all current nodes of a simple linked list
/// @param list Pointer to the first node
void printList(Node* list);

/// @brief ### Searches an object through a simple linked list
/// @param list Pointer to the first node
/// @param id Object's identifier
/// @return The object with matching identifier or a NULL object
Object getObject(Node* list, int id);

/// @brief ### Insert a new node in the beginning of a simple linked list
/// @param list Pointer to the first node
/// @param obj Object to be inserted in the node
/// @return A pointer to the first node of the list
Node* insertFirst(Node* list, Object obj);

/// @brief ### Insert a new node at the end of a simple linked list
/// @param list Pointer to the first node
/// @param obj Object to be inserted in the node
/// @return A pointer to the first node of the list
Node* insertLast(Node* list, Object obj);

/// @brief ### Insert a new node in a desired position of a simple linked list
/// @param list Pointer to the first node
/// @param obj Object to be inserted in the node
/// @param pos Position desired
/// @return A pointer to the first node of the list
Node* insertRandom(Node* list, Object obj, int pos);

/// @brief ### Removes an object's corresponding node from a simple linked list
/// @param list Pointer to the first node
/// @param id Object's identifier
/// @return A pointer to the first node of the list
Node* removeObject(Node* list, int id);

/// @brief ### Destructs a simple linked list
/// @param list Pointer to the first node
/// @return NULL to the list's pointer
Node* destruct(Node* list);