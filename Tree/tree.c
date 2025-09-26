#include "Tree.h"

void tree_initialize(Tree* tree) {
    tree->root = NULL;
    tree->height = 0;
}

bool tree_empty(Tree tree) {
    if (tree.root == NULL) return true;
    else return false;
}

void tree_insert(Tree* tree, type data) {

};

void node_print(Node* node) {
    printf("\nData: %d", node->data);
}

void node_depth(Node* node) {
    printf("\nDepth: %d", node->depth);
}

void node_clear(Node* node) {
    Node* parent = node->parent;

    if (parent->left == node) parent->left = NULL;
    else parent->right = NULL;

    free(node);
}

void tree_inorder(Node* root, NodeFunction function) {
    if (root != NULL) {
        tree_inorder(root->left, function);
        function(root);
        tree_inorder(root->right, function);
    }
}

void tree_preorder(Node* root, NodeFunction function) {
    if (root != NULL) {
        function(root);
        tree_preorder(root->left, function);
        tree_preorder(root->right, function);
    }
}

void tree_postorder(Node* root, NodeFunction function) {
    if (root != NULL) {
        tree_postorder(root->left, function);
        tree_postorder(root->right, function);
        function(root);
    }
}

void tree_print(Tree tree) {
    tree_preorder(tree.root, node_print);
}

void tree_clear(Tree* tree) {
    tree_postorder(tree->root, node_clear);
    tree->root = NULL;
    tree->height = 0;
}