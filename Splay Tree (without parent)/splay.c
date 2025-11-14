#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

SPT sptInitialize() {
    return (SPT){NULL, 0}; // Returns an empty splay tree with 0 height
}

static bool sptEmpty(SPT tree) {
    return tree.root == NULL; // Returns true in case the tree is empty and false in case it isn't
}

static int sptHeightRecursive(NodeSPT* node) {
    if (node == NULL)
        return 0;
    
    int leftHeight = sptHeightRecursive(node->left);
    int rightHeight = sptHeightRecursive(node->right);
    
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else // rightHeight > leftHeight
        return rightHeight + 1;
}

static void sptHeight(SPT* tree) {
    tree->height = sptHeightRecursive(tree->root);
}

static void sptZig(NodeSPT* aux, NodeSPT* node, NodeSPT* father) {
    node->left = aux->right;
    aux->right = node;
    if (father != NULL) { 
        if (node == father->left)
            father->left = aux;
        else // If (node == father->right)
            father->right = aux;
    }
}

static void sptZag(NodeSPT* aux, NodeSPT* node, NodeSPT* father) {
    node->right = aux->left;
    aux->left = node;
    if (father != NULL) { 
        if (node == father->left)
            father->left = aux;
        else // If (node == father->right)
            father->right = aux;
    }
}

static void sptSplaying(NodeSPT* aux, NodeSPT* node, NodeSPT* father) {
    if (aux == node->left)
        sptZig(aux, node, father);
    else // If (aux == node->right)
        sptZag(aux, node, father);
}

static void sptSplit(SPT* tree, SPT auxTrees[]) {
    auxTrees[0] = (SPT){tree->root, 0};
    auxTrees[1] = (SPT){tree->root->right, 0};

    // Cuts the connection between the new trees
    auxTrees[0].root->right = NULL;
}

static SPT sptJoin(SPT auxTrees[], NodeSPT* root) {
    SPT tree = (SPT){root, 0};

    if (root != NULL)
        // Connects right tree to the new root
        root->right = auxTrees[1].root;
    else
        tree.root = auxTrees[1].root;

    return tree;
}

static NodeSPT* sptAccessSearch(NodeSPT* node, NodeSPT* father, type key) {
    if (node == NULL) // Node with key not found
        return father;
    
    if (node->key == key) // Node with key found
        return node;
    
    NodeSPT* aux;

    if (key < node->key) 
        aux = sptAccessSearch(node->left, node, key);
    else // If (key > node->key)
        aux = sptAccessSearch(node->right, node, key);

    if (aux != node)
        sptSplaying(aux, node, father);

    return aux;
}

NodeSPT* sptAccess(SPT* tree, type key) {
    if (sptEmpty(*tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return NULL;
    }

    NodeSPT* aux = sptAccessSearch(tree->root, NULL, key);

    tree->root = aux;
    sptHeight(tree);

    if (aux->key != key) { // Node with key not found
        printf("\nKey %d not in the tree", key);
        return NULL;
    }

    // Node with the key is found
    return aux;
}

void sptInsert(SPT* tree, type key) {
    NodeSPT* new = (NodeSPT*)malloc(sizeof(NodeSPT));

    new->left = new->right = NULL;
    new->key = key;

    if (sptEmpty(*tree)) {
        // Empty tree case
        tree->root = new;
        return;
    }

    NodeSPT* aux = sptAccessSearch(tree->root, NULL, key);

    tree->root = aux;

    if (aux->key == key) {
        printf("\nNode with key %d already in tree", key);
        return;
    }

    SPT auxTrees[2]; // Array of the auxiliar trees
    sptSplit(tree, auxTrees);
    // printf("\nSuccesfull split");

    // Case when the new node key would be inserted as the left child of what would be his father (now the left tree's root)
    if (key < auxTrees[0].root->key) {
        auxTrees[0].root->right = auxTrees[1].root;
        auxTrees[1].root = auxTrees[0].root;
        auxTrees[0].root = auxTrees[0].root->left;
        auxTrees[1].root->left = NULL;
    }

    new->left = auxTrees[0].root;
    auxTrees[0].root = new;

    *tree = sptJoin(auxTrees, new); // Reconnects the auxiliar trees
    // printf("\nSuccessfull join");

    sptHeight(tree);
}

static int sptNodeDepth(SPT tree, type key) {
    int depth = 1;

    NodeSPT* aux = tree.root;

    while (aux != NULL && aux->key != key) {
        if (key < aux->key)
            aux = aux->left;
        else
            aux = aux->right;

        depth++;
    }

    if (aux == NULL) // Node not found
        return -1;
    else // Node found
        return depth;
}

void sptNodePrintDepth(SPT tree, type key) {
    if (sptEmpty(tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    int depth = sptNodeDepth(tree, key);

    if (depth == -1) {
        printf("\nKey %d not in the tree", key);
        return;
    }

    printf("Depth: %d", depth);
}

void sptNodePrint(SPT tree, type key) {
    if (sptEmpty(tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = tree.root;

    while (aux != NULL && aux->key != key) {
        if (key < aux->key)
            aux = aux->left;
        else
            aux = aux->right;
    }

    if (aux == NULL) {
        printf("\nKey %d not in the tree", key);
        return;
    }

    printf("Key: %d", aux->key);
}

void sptNodeDelete(SPT* tree, type key) {
    if (sptEmpty(*tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = sptAccess(tree, key); // The to be deleted node
    
    // Ends function in case the accessed node isn't the one with the desired key
    if (aux->key != key)
        return;

    // Case there's only one node on the tree
    if (aux->right == NULL && aux->left == NULL) {
        free(aux);
        printf("\nNode with key %d (tree root) deleted", key);
        tree->root = NULL;
        tree->height = 0;
        return;
    }

    SPT auxTrees[2]; // Array of the auxiliar trees
    sptSplit(tree, auxTrees);
    // printf("\nSuccesfull split");

    auxTrees[0].root = aux->left;
    free(aux); // Deletes node

    NodeSPT* newRoot = auxTrees[0].root;
    if (newRoot != NULL) {
        // Stops when finds the rightmost node in the left tree
        while (newRoot->right != NULL)
            // Searches for node with max key (the rightmost node)
            newRoot = newRoot->right;
        // printf("\nOut of rightmost node while");

        sptAccessSearch(auxTrees[0].root, NULL, newRoot->key); // newRoot becomes the left tree's root
        // printf("\nOut of join splay");
    }

    *tree = sptJoin(auxTrees, newRoot); // Reconnects the auxiliar trees
    // printf("\nSuccessfull join");

    sptHeight(tree);

    printf("\nNode with key %d deleted", key);
}

static void sptPrintRecursive(NodeSPT* node, int depth) {
    if (node != NULL) {
        for (int i = 0; i < depth; i++) // Prints '=' equal times to the node's depth count
            printf("=");

        printf("%d", node->key);
        if (node->left != NULL) printf(" (%d", node->left->key);
        else printf(" (Nan");
        if (node->right != NULL) printf(", %d)", node->right->key);
        else printf(", Nan)");
        printf("\n");

        sptPrintRecursive(node->left, depth + 1);
        sptPrintRecursive(node->right, depth + 1);
    }
}

void sptPrint(SPT tree) {
    if (sptEmpty(tree))
        printf("\n\nEmpty splay tree");
    else {
        printf("\n\n----- PRINTING SPLAY TREE -----\n");
        sptPrintRecursive(tree.root, 1);
    }
}

static void sptClearRecursive(NodeSPT* node) {
    if (node != NULL) {
        sptClearRecursive(node->left);
        sptClearRecursive(node->right);

        free(node);
    }
}

void sptClear(SPT* tree) {
    if (sptEmpty(*tree)) {
        // Checks if the tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    sptClearRecursive(tree->root);

    tree->root = NULL;
    tree->height = 0;

    printf("\nSplay tree successfully cleared");
}