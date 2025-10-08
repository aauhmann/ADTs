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
    printf("\n");
    for (int i = 0; i < node->depth; i++)
        printf("=");
    printf("%d", node->key);
}

void node_depth(Node* node) {
    printf("\nDepth: %d", node->depth);
}

void node_depthDec(Node* node) {
    node->depth--;
}

void node_clear(Node* node) {
    Node* parent = node->parent;

    if (parent != NULL) {
        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;
    }

    free(node);
}

void node_clearByKey(Tree* tree, Node* node) {
    Node* parent = node->parent;
    Node* aux;

    if (node->left != NULL && node->right != NULL) {
        aux = node->left;

        while (aux->right != NULL)
            aux = aux->right;

        tree_preorder(aux, node_depthDec);
        
        if (aux->parent != node) {
            aux->parent->right = aux->left;
            if (aux->left != NULL) aux->left->parent = aux->parent;
        } else {
            node->left = aux->left;
            if (aux->left != NULL) aux->left->parent = node;
        }

        aux->parent = parent;
        aux->left = node->left;
        aux->right = node->right;
        aux->depth = node->depth;

        if (aux->left != NULL) aux->left->parent = aux;
        if (aux->right != NULL) aux->right->parent = aux;

        if (parent != NULL) {
            if (parent->left == node) parent->left = aux;
            else parent->right = aux;
        }

        if (node == tree->root) tree->root = aux;
    }

    else if (node->left != NULL) {
        if (parent != NULL) {
            if (parent->left == node) parent->left = node->left;
            else parent->right = node->left;
        }
        node->left->parent = parent;
        tree_preorder(node->left, node_depthDec);

        if (node == tree->root) tree->root = node->left;
    }

    else if (node->right != NULL) {
        if (parent != NULL) {
            if (parent->left == node) parent->left = node->right;
            else parent->right = node->right;
        }
        node->right->parent = parent;
        tree_preorder(node->right, node_depthDec);

        if (node == tree->root) tree->root = node->right;
    }

    else {
        if (parent != NULL) {
            if (parent->left == node) parent->left = NULL;
            else parent->right = NULL;
        }

        if (node == tree->root) tree->root = NULL;
    }
    
    printf("Key %d removed (possible tree reestruturation)", node->key);
    
    free(node);

    tree_height(tree);
}

Node* tree_searchByKey(Tree* tree, type key, NodeFunction function) {
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

void tree_height(Tree* tree) {
    if (tree_empty(*tree)) {
        tree->height = 0;
    } else {
        tree->height = 0;
        tree_maxDepth(tree->root, &tree->height);
    }
}

void tree_maxDepth(Node* root, int* maxDepth) {
    if (root != NULL) {
        if (root->depth > *maxDepth) *maxDepth = root->depth;
        tree_maxDepth(root->left, maxDepth);
        tree_maxDepth(root->right, maxDepth);
    }
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