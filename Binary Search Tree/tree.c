#include "Tree.h"

void tree_initialize(Tree* tree) {
    tree->root = NULL;
    tree->height = 0;
}

bool tree_empty(Tree tree) {
    if (tree.root == NULL) return true;
    else return false;
}

void tree_insert(Tree* tree, type key) {
    Node* new = (Node*)malloc(sizeof(Node));
    Node* aux = tree->root;

    new->key = key;
    new->left = new->right = NULL;
    if (tree_empty(*tree)) {
        tree->root = new;
        tree->height = 1;
        new->parent = NULL;
        new->depth = 1;
        printf("Inserted at root");
        return;
    }
    
    while (true) {
        if (key < aux->key) {
            if (aux->left == NULL) {
                aux->left = new;
                break;
            }
            else aux = aux->left;
        }
        else if (key > aux->key) {
            if (aux->right == NULL) {
                aux->right = new;
                break;
            }
            else aux = aux->right;
        }
        else {
            printf("Key %d already in tree", key);
            return;
        }
    }

    new->parent = aux;
    new->depth = aux->depth + 1;

    if (tree->height < new->depth)
        tree->height = new->depth;

    printf("Key %d inserted at depth %d", key, new->depth);
}

void node_print(Node* node) {
    printf("\nKey: %d", node->key);
}

void node_depth(Node* node) {
    printf("\nDepth: %d", node->depth);
}

void node_clear(Node* node) {
    Node* parent = node->parent;

    if (parent != NULL) {
        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;
    }

    if (node->left != NULL)
        tree_postorder(node->left, node_clear);
    if (node->right != NULL)
        tree_postorder(node->right, node_clear);

    free(node);
}

Node* tree_bykey(Tree* tree, type key, NodeFunction function) {
    if (tree_empty(*tree)) {
        printf("\nEmpty tree");
        return NULL;
    }

    Node* aux = tree->root;

    while (aux != NULL) {
        if (key < aux->key)
            aux = aux->left;
        else if (key > aux->key)
            aux = aux->right;
        else {
            Node* node = aux;
            if (function != NULL)
                function(aux);
            return node;
        }
    }

    printf("Key not found");
    return NULL;
}

void tree_inorder(Node* root, NodeFunction function) {
    if (root != NULL && function != NULL) {
        tree_inorder(root->left, function);
        function(root);
        tree_inorder(root->right, function);
    }
}

void tree_preorder(Node* root, NodeFunction function) {
    if (root != NULL && function != NULL) {
        function(root);
        tree_preorder(root->left, function);
        tree_preorder(root->right, function);
    }
}

void tree_postorder(Node* root, NodeFunction function) {
    if (root != NULL && function != NULL) {
        tree_postorder(root->left, function);
        tree_postorder(root->right, function);
        function(root);
    }
}

void tree_print(Tree tree) {
    if (tree_empty(tree)) printf("\nEmpty tree");
    else tree_preorder(tree.root, node_print);
}

void tree_clear(Tree* tree) {
    if (tree_empty(*tree))
        printf("\nEmpty tree");
    else {
        tree_postorder(tree->root, node_clear);
        tree->root = NULL;
        tree->height = 0;
        printf("\nTree cleared");
    }
}