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
        if (key < aux->key && aux->left != NULL)
            aux = aux->left;
        else if (key > aux->key && aux->right != NULL)
            aux = aux->right;
        else
            return aux; // Returns the last accessed node if the desired key isn't in the tree
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

    if (aux->key != key) {
        sptSplaying(aux->parent, tree); // Splays the searched node's parent
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

    if (aux->key != key) {
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

    if (aux->key != key) {
        printf("\nKey %d not in the tree", key);
        return;
    }

    printf("Key: %d", aux->key);
}

static void sptSplit(SPT* tree, SPT auxTrees[]) {
    auxTrees[0] = (SPT){tree->root, 0};
    auxTrees[1] = (SPT){tree->root->right, 0};

    // Cuts the connection between the new trees
    auxTrees[0].root->right = NULL;
    if (auxTrees[1].root != NULL) auxTrees[1].root->parent = NULL;
}

static SPT sptJoin(SPT auxTrees[], NodeSPT* root) {
    SPT tree = (SPT){root, 0};

    // Connects right tree to the new root
    root->right = auxTrees[1].root;
    if (auxTrees[1].root != NULL)
        auxTrees[1].root->parent = root;

    return tree;
}

void sptNodeDelete(SPT* tree, type key) {
    if (sptEmpty(*tree)) {
        // Checks if the splay tree is empty
        printf("\nEmpty splay tree");
        return;
    }

    NodeSPT* aux = sptAccess(tree, key); // The deleted node

    if (aux->key != key) {
        // Ends function in case the accessed node isn't the onde with the desired key
        printf("\nNode not found");
        return;
    }

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
    auxTrees[0].root->parent = NULL; // Cuts connection with the soon deleted node
    free(aux); // Deletes node

    NodeSPT* newRoot = auxTrees[0].root;
    // Stops when finds the rightmost node in the left tree
    while (newRoot->right != NULL) {
        // Searches for node with max key (the rightmost node)
        newRoot = newRoot->right;
    }
    // printf("\nOut of rightmost node while");

    sptSplaying(newRoot, &auxTrees[0]); // newRoot becomes the left tree's root
    // printf("\nOut of join splay");


    *tree = sptJoin(auxTrees, newRoot); // Reconnects the auxiliar trees
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