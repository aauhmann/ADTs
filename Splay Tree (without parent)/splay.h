#pragma once

#include <stdbool.h>

typedef int type;

typedef struct s_SplayNode {
    type key;
    struct s_SplayNode* left;
    struct s_SplayNode* right;
} NodeSPT;

typedef struct s_SplayTree {
    NodeSPT* root;
    int height;
} SPT;

SPT sptInitialize();
void sptInsert(SPT* tree, type key);
NodeSPT* sptAccess(SPT* tree, type key);
void sptNodePrintDepth(SPT tree, type key);
void sptNodePrint(SPT tree, type key);
void sptPrint(SPT tree);
void sptNodeDelete(SPT* tree, type key);
void sptClear(SPT* tree);