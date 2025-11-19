#pragma once

#include <stdbool.h>

typedef int type;

typedef struct s_NodeAVL {
    type key;
    int factor;
    struct s_NodeAVL* left;
    struct s_NodeAVL* right;
} NodeAVL;

typedef struct AVL {
    NodeAVL* root;
    int height;
    int factor;
} AVL;

typedef void (*NodeFunction)(NodeAVL*);

AVL avlInitialize();
void avlInsert(AVL* tree, type key);
NodeAVL* avlNodeGet(AVL tree, type key);
void avlNodePrintDepth(AVL tree, type key);
void avlNodePrint(AVL tree, type key);
void avlNodeDelete(AVL* tree, type key);
void avlPrint(AVL tree);
void avlClear(AVL* tree);