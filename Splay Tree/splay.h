#pragma once

#include <stdbool.h>

typedef int type;

typedef struct s_SplayNode {
    type key;
    struct s_SplayNode* parent;
    struct s_SplayNode* left;
    struct s_SplayNode* right;
} NodeSPT;

typedef struct s_SPT {
    NodeSPT* root;
    int height;
} SPT;

SPT sptInitialize();
void sptInsert(SPT* tree, type key);
NodeSPT* sptAccess(SPT* tree, type key);
int sptNodeDepth(NodeSPT* node);
void sptPrint(SPT tree);
void sptClear(SPT* tree);