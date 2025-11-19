#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int type;

typedef struct Node {
    type key;
    int factor;
    int depth;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Tree {
    Node* root;
    int height;
} Tree;

typedef void (*NodeFunction)(Node*);

void tree_initialize(Tree* tree);
bool tree_empty(Tree tree);
void tree_insert(Tree* tree, type key);
bool node_fixFactor(Node* node);
void node_print(Node* node);
void node_depthAndFactor(Node* node);
void node_depthDec(Node* node);
void node_depthInc(Node* node);
void node_clear(Node* node);
void node_clearByKey(Tree* tree, Node* node);
bool tree_factorCheck(Node* root, int* currentDepth, type* key, bool* needRotation);
Node* tree_searchByKey(Tree* tree, type key, NodeFunction function);
void tree_inorder(Node* root, NodeFunction function);
void tree_preorder(Node* root, NodeFunction function);
void tree_postorder(Node* root, NodeFunction function);
void tree_height(Tree* tree);
void subtree_maxDepth(Node* root, int* maxDepth);
void tree_print(Tree tree);
void tree_clear(Tree* tree);
void subtree_rotate(Tree* tree, Node* root);
void subtree_rotateRight(Tree* tree, Node* root);
void subtree_rotateLeft(Tree* tree, Node* root);
void subtree_doubleRotateRight(Tree* tree, Node* root);
void subtree_doubleRotateLeft(Tree* tree, Node* root);
int node_factor(Node* root);
void tree_factor(Node* root, int* factor);