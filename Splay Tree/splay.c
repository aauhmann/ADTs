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

static void sptZig(NodeSPT* node, SPT* tree) {
    NodeSPT* father = node->parent;
    NodeSPT* grandpa = father->parent;

    father->left = node->right;
    if (father->left != NULL)
        father->left->parent = father;
    node->right = father;

    node->parent = grandpa;
    father->parent = node;

    if (grandpa == NULL) // Means there's no one above the node, so it must be the tree's root
        tree->root = node;
    else if (father == grandpa->left)
        grandpa->left = node;
    else // father == grandpa->right
        grandpa->right = node;
}

static void sptZag(NodeSPT* node, SPT* tree) {
    NodeSPT* father = node->parent;
    NodeSPT* grandpa = father->parent;

    father->right = node->left;
    if (father->right != NULL)
        father->right->parent = father;
    node->left = father;

    node->parent = grandpa;
    father->parent = node;

    if (grandpa == NULL) // Means there's no one above the node, so it must be the tree's root
        tree->root = node;
    else if (father == grandpa->left)
        grandpa->left = node;
    else // father == grandpa->right
        grandpa->right = node;
}

static void sptSplaying(NodeSPT* node, SPT* tree) {
    NodeSPT* father;
    NodeSPT* grandpa;

    while (tree->root != node) {
        father = node->parent;
        grandpa = father->parent;

        if (father->left == node) {
            // Left child node cases
            if (father == tree->root) {
                // Zig rotation case
                sptZig(node, tree);
                // printf("\nZig");
            }
            else if (grandpa->left == father) {
                // Zig-Zig rotation case
                sptZig(father, tree);
                sptZig(node, tree);
                // printf("\nZig-Zig");
            }
            else if (grandpa->right == father) {
                // Zig-Zag rotation case
                sptZig(node, tree);
                sptZag(node, tree);
                // printf("\nZig-Zag");
            }
        }
        else {
            // Right child node cases
            if (father == tree->root) {
                // Zag rotation case
                sptZag(node, tree);
                // printf("\nZag");
            }
            else if (grandpa->right == father) {
                // Zag-Zag rotation case
                sptZag(father, tree);
                sptZag(node, tree);
                // printf("\nZag-Zag");
            }
            else if (grandpa->left == father) {
                // Zag-Zig rotation case
                sptZag(node, tree);
                sptZig(node, tree);
                // printf("\nZag-Zig");
            }
        }
        // sptPrint(*tree);
    }
}

void sptInsert(SPT* tree, type key) {
    NodeSPT* new = (NodeSPT*)malloc(sizeof(NodeSPT));

    new->left = new->right = NULL;
    new->key = key;

    if (sptEmpty(*tree)) {
        // Empty tree case
        tree->root = new;
        new->parent = NULL;
        return;
    }

    NodeSPT* aux = tree->root;
    
    // Breakes after finding the insertion spot (or when key is already in tree)
    while (true) {
        // Insertion spot yet undefined
        if (key < aux->key) {
            if (aux->left == NULL) {
                // Insertion spot identified
                aux->left = new;
                break;
            }
            else
                aux = aux->left;
        }
        else if (key > aux->key) {
            if (aux->right == NULL) {
                // Insertion spot identified
                aux->right = new;
                break;
            }
            else
                aux = aux->right;
        }
        else {
            // Key's already in the tree
            printf("\nKey's already in tree");
            free(new); // Release the unused new node
            return;
        }
    }

    new->parent = aux;

    // Not empty tree case
    sptSplaying(new, tree);
    // printf("\nOut of splaying");
    sptHeight(tree);
    // printf("\nOut of height count");
}

static NodeSPT* sptNodeSearch(SPT tree, type key) {
    NodeSPT* aux = tree.root;

    // Iterates ultil it finds the node with the same key
    while (aux->key != key) {
        // Searches for the node with the key
        if (key < aux->key)
            aux = aux->left;
        else // key > aux->key
            aux = aux->right;

        // Checks if the search ends in a dead end
        if (aux == NULL) {
            // Node with the key isn't in the tree
            return NULL;
        }
    }

    return aux;
}

NodeSPT* sptAccess(SPT* tree, type key) {
    if (sptEmpty(*tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return NULL;
    }

    NodeSPT* aux = sptNodeSearch(*tree, key);

    if (aux == NULL) {
        printf("\nKey %d not in the tree", key);
        return NULL;
    }

    // Node with the key is found
    sptSplaying(aux, tree);
    sptHeight(tree);

    return aux;
}

static int sptNodeDepth(NodeSPT* node) {
    int depth = 0;

    while (node != NULL) {
        // Counts the node's depth by counting how many antecessor it has
        depth++;
        node = node->parent;
    }

    return depth;
}

void sptNodePrintDepth(SPT tree, type key) {
    if (sptEmpty(tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = sptNodeSearch(tree, key);

    if (aux == NULL) {
        printf("\nKey %d not in the tree", key);
        return;
    }

    printf("Depth: %d", sptNodeDepth(aux));
}

void sptNodePrint(SPT tree, type key) {
    if (sptEmpty(tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = sptNodeSearch(tree, key);

    if (aux == NULL) {
        printf("\nKey %d not in the tree", key);
        return;
    }

    printf("Key: %d", aux->key);
}

static void sptSplit(SPT* tree, SPT auxTrees[]) {
    auxTrees[0] = (SPT){tree->root->left, 0};
    auxTrees[1] = (SPT){tree->root->right, 0};
}

static SPT sptJoin(SPT auxTrees[]) {
    NodeSPT* aux = auxTrees[0].root;

    // Stops when finds the rightmost node
    while (aux->right != NULL) {
        // Searches for node with max key (the rightmost node)
        aux = aux->right;
    }

    // printf("\nOut of join while");

    sptSplaying(aux, &auxTrees[0]);
    // printf("\nOut of join splay");

    SPT tree = (SPT){aux, 0};
    aux->right = auxTrees[1].root;
    if (auxTrees[1].root != NULL)
        auxTrees[1].root->parent = aux;

    return tree;
}

void sptNodeDelete(SPT* tree, type key) {
    if (sptEmpty(*tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = sptAccess(tree, key);

    SPT auxTrees[2];
    sptSplit(tree, auxTrees);
    // printf("\nSuccesfull split");
    *tree = sptJoin(auxTrees);
    // printf("\nSuccessfull join");

    sptHeight(tree);

    printf("\nNode with key %d deleted", key);
}

static void sptPrintRecursive(NodeSPT* node) {
    if (node != NULL) {
        for (int i = 0; i < sptNodeDepth(node); i++) // Prints '=' equal times to the node's depth count
            printf("=");

        printf("%d", node->key);
        if (node->left != NULL) printf(" (%d", node->left->key);
        else printf(" (Nan");
        if (node->right != NULL) printf(", %d)", node->right->key);
        else printf(", Nan)");
        printf("\n");

        sptPrintRecursive(node->left);
        sptPrintRecursive(node->right);
    }
}

void sptPrint(SPT tree) {
    if (sptEmpty(tree))
        printf("\n\nEmpty splay tree");
    else {
        printf("\n\n----- PRINTING SPLAY TREE -----\n");
        sptPrintRecursive(tree.root);
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