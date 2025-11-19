#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

AVL avlInitialize() {
    return (AVL){NULL, 0, 0}; // Returns an empty splay tree with height and factor 0
}

static bool avlEmpty(AVL tree) {
    return (tree.root == NULL); // Returns true in case the tree is empty and false in case it isn't
}

static int avlNodeHeight(NodeAVL* node) {
    if (node == NULL)
        return 0;
    
    int leftHeight = avlHeightRecursive(node->left);
    int rightHeight = avlHeightRecursive(node->right);
    
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else // rightHeight > leftHeight
        return rightHeight + 1;
}

static void avlTreeHeight(AVL* tree) {
    tree->height = avlNodeHeight(tree->root);
}

static int avlNodeFactorBalance(NodeAVL* node) {
    int leftHeight = avlNodeHeight(node->left);
    int rightHeight = avlNodeHeight(node->right);

    node->factor = leftHeight - rightHeight;

    return node->factor;
}

static void avlTreeFactorRecursion(NodeAVL* node, int* maxFactor) {
    if (node == NULL) return;

    if (abs(node->factor) > abs(*maxFactor))
        *maxFactor = node->factor;
        
    avlTreeFactorRecursion(node->left, maxFactor);
    avlTreeFactorRecursion(node->right, maxFactor);
}

static void avlTreeFactor(AVL* tree) {
    if (avlEmpty(*tree)) {
        printf("\nEmpty AVL tree");
        return;
    }

    avlTreeFactorRecursion(tree->root, &tree->factor);
}

static void avlRotateRight(NodeAVL* child, NodeAVL* node, NodeAVL* father) {
    node->left = child->right;
    child->right = node;
    child->factor = 0;

    if (father != NULL) {
        // Parent conncetion
        if (node == father->left)
            father->left = child;
        else // If (node == father->right)
            father->right = child;
    }
}

static void avlRotateLeft(NodeAVL* child, NodeAVL* node, NodeAVL* father) {
    node->right = child->left;
    child->left = node;
    child->factor = 0;

    if (father != NULL) {
        // Parent connection
        if (node == father->left)
            father->left = child;
        else // If (node == father->right)
            father->right = child;
    }
}

static void avlRotation(NodeAVL* node, NodeAVL* father) {
    if (node->factor > 1) {
        if (node->left->factor > 0) {
            // Right rotation case
            avlRotateRight(node->left, node, father);
        }
        else { // If node->left->factor < 0
            // Double right rotation case
            avlRotateLeft(node->left->right, node->left, node);
            avlRotateRight(node->left, node, father);
        }
    }
    else { // node->factor < -1
        if (node->right->factor < 0) {
            // Left rotation case
            avlRotateLeft(node->right, node, father);
        }
        else { // If node->right->factor > 0
            // Double left rotation case
            avlRotateRight(node->right->left, node->right, node);
            avlRotateLeft(node->right, node, father);
        }
    }
}

static NodeAVL* avlInsertRecursion(NodeAVL* node, NodeAVL* father, type key) {
    if (node == NULL) {
        // Empty space to insertion
        NodeAVL* new = (NodeAVL*)malloc(sizeof(NodeAVL));
        new->left = new->right = NULL;
        new->key = key;
        new->factor = 0;

        // Father connection
        if (key < father->key)
            father->left = new;
        else // If key > father->key
            father->right = new;

        return new;
    }
    
    if (node->key == key) { // Node with key found
        printf("\nNode with key %d already in tree", key);
        return NULL;
    }
    
    NodeAVL* aux;

    if (key < node->key)
        aux = avlInsertRecursion(node->left, node, key);
    else // If (key > node->key)
        aux = avlInsertRecursion(node->right, node, key);

    // If a node has been inserted
    if (aux != NULL) {
        avlNodeFactorBalance(node);

        // Case the node's unbalanced
        if (abs(node->factor) > 1)
            avlRotation(node, father);
    }

    return aux;
}

void avlInsert(AVL* tree, type key) {    
    if (avlEmpty(*tree)) {
        // Empty tree case
        NodeAVL* new = (NodeAVL*)malloc(sizeof(NodeAVL));
        new->left = new->right = NULL;
        new->key = key;
        tree->root = new;
        return;
    }

    NodeAVL* aux = avlInsertRecursion(tree->root, NULL, key);

    if (aux == NULL) {
        printf("\nNode with key %d already in tree", key);
        return;
    }

    avlTreeFactor(tree);
    avlTreeHeight(tree);
}

NodeAVL* avlNodeGet(AVL tree, type key) {
    if (avlEmpty(tree)) {
        // Checks if the avl tree is empty
        printf("\nEmpty AVL tree");
        return NULL;
    }

    NodeAVL* aux = tree.root;

    // Stops if the node isn't on the tree or if it's found
    while (aux != NULL && aux->key != key) {
        if (key < aux->key)
            aux = aux->left;
        else // If key > aux->right
            aux = aux->right;
    }

    if (aux == NULL) { // Node with key not found
        printf("\nKey %d not in the tree", key);
        return NULL;
    }

    // Node with the key is found
    return aux;
}

static int avlNodeDepth(AVL tree, type key) {
    int depth = 1;

    NodeAVL* aux = tree.root;

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

void avlNodePrintDepth(AVL tree, type key) {
    if (avlEmpty(tree)) {
        // Checks if the avl tree is empty
        printf("\nEmpty AVL tree");
        return;
    }

    int depth = avlNodeDepth(tree, key);

    if (depth == -1) {
        printf("\nKey %d not in the tree", key);
        return;
    }



    printf("Depth: %d", depth);
}

void avlNodePrint(AVL tree, type key) {
    if (avlEmpty(tree)) {
        // Checks if the avl tree is empty
        printf("\nEmpty AVL tree");
        return;
    }

    NodeAVL* aux = tree.root;

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

static NodeAVL* avlNodeSubstitution(NodeAVL* node, NodeAVL* father) {
    if (node == NULL) return father;

    NodeAVL* rightmost = avlNodeSubstitution(node->right, node);

    if (node == rightmost)
        father->right = node->left;
    else {
        avlNodeFactorBalance(node);
        // Case the node's unbalanced
        if (abs(node->factor) > 1)
            avlRotation(node, father);
    }

    return rightmost;
}

static NodeAVL* avlNodeDeleteRecursion(NodeAVL* node, NodeAVL* father, type key) {
    if (node == NULL) {
        printf("\nNode with key %d not in tree", key);
        return NULL;
    }
    
    if (node->key == key) { // Node with key found
        if (node->left == NULL) {
            if (node == father->left)
                father->left = node->right;
            else
                father->right = node->right;
        }
        else if (node->right == NULL) {
            if (node == father->left)
                father->left = node->left;
            else
                father->right = node->left;
        }
        else { // Node has both subtrees not NULL
            NodeAVL* rightmost;

            if (node->left->right == NULL)
                rightmost = node->left;
            else
                rightmost = avlNodeSubstitution(node->left->right, node);

            rightmost->right = node->right;
            rightmost->left = node->left;
            
            if (node == father->left)
                father->left = rightmost;
            else
                father->right = rightmost;
        }

        return node;
    }
    
    NodeAVL* aux;

    if (key < node->key)
        aux = avlDeleteRecursion(node->left, node, key);
    else // If (key > node->key)
        aux = avlDeleteRecursion(node->right, node, key);

    // If the node exists and will be deleted
    if (aux != NULL) {
        // Case the node's unbalanced
        if (abs(avlNodeFactorBalance(node)) > 1)
            avlRotation(node, father);
    }

    return aux;
}

void avlNodeDelete(AVL* tree, type key) {
    if (avlEmpty(*tree)) {
        // Checks if the avl tree is empty
        printf("\nEmpty AVL tree");
        return;
    }

    NodeAVL* aux = avlNodeDeleteRecursion(tree->root, NULL, key);

    if (aux == NULL) {
        printf("\nNode with key %d not in tree", key);
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

    avlTreeFactor(tree);
    avlTreeHeight(tree);

    printf("\nNode with key %d deleted", key);
}

static void avlPrintRecursive(NodeAVL* node, int depth) {
    if (node != NULL) {
        for (int i = 0; i < depth; i++) // Prints '=' equal times to the node's depth count
            printf("=");

        printf("%d", node->key);
        printf(" - FB: %d", node->factor);
        if (node->left != NULL) printf(" (%d", node->left->key);
        else printf(" (Nan");
        if (node->right != NULL) printf(", %d)", node->right->key);
        else printf(", Nan)");
        printf("\n");

        avlPrintRecursive(node->left, depth + 1);
        avlPrintRecursive(node->right, depth + 1);
    }
}

void avlPrint(AVL tree) {
    if (avlEmpty(tree))
        printf("\n\nEmpty AVL tree");
    else {
        printf("\n\n----- PRINTING AVL TREE -----\n");
        avlPrintRecursive(tree.root, 1);
    }
}

static void avlClearRecursion(NodeAVL* node) {
    if (node != NULL) {
        avlClearRecursive(node->left);
        avlClearRecursive(node->right);

        free(node);
    }
}

void avlClear(AVL* tree) {
    if (avlEmpty(*tree)) {
        // Checks if the tree is empty
        printf("\nEmpty AVL tree");
        return;
    }

    avlClearRecursive(tree->root);

    tree->root = NULL;
    tree->height = tree->factor = 0;

    printf("\nAVL tree successfully cleared");
}