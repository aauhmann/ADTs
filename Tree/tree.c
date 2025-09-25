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

void tree_nodeData(Node* node) {
    printf("\nData: %d", node->data);
}

void tree_nodeDepth(Node* node) {
    printf("\nDepth: %d", node->depth);
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