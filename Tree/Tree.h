#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int type;

typedef struct Node {
    type data;
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
void tree_insert(Tree* tree, type data);
void tree_nodeData(Node* node);
void tree_nodeDepth(Node* node);
void tree_inorder(Node* root, NodeFunction function);
void tree_preorder(Node* root, NodeFunction function);
void tree_postorder(Node* root, NodeFunction function);