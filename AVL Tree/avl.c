#include "avl.h"

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
    bool needRotation = false;

    new->key = key;
    new->left = new->right = NULL;
    new->factor = 0;

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
                new->depth = aux->depth + 1;
                if (aux->right == NULL)
                    needRotation = node_fixFactor(aux);
                else aux->factor++;
                break;
            }
            else aux = aux->left;
        }
        else if (key > aux->key) {
            if (aux->right == NULL) {
                aux->right = new;
                new->depth = aux->depth + 1;
                if (aux->left == NULL)
                    needRotation = node_fixFactor(aux);
                else aux->factor--;
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

    printf("Key %d inserted at depth %d", key, new->depth);
    
    if (needRotation) {
        subtree_rotate(tree, aux);
        tree_height(tree);
    }
    else if (tree->height < new->depth)
        tree->height = new->depth;
}

bool node_fixFactor(Node* node) {
    bool needRotation = false;

    while (node != NULL) {
        node->factor = node_factor(node);

        if (abs(node->factor) > 1)
            needRotation = true;

        node = node->parent;
    }

    return needRotation;
}

void node_print(Node* node) {
    printf("\n");
    for (int i = 0; i < node->depth; i++)
        printf("=");
    printf("%d", node->key);
}

void node_depthAndFactor(Node* node) {
    printf("\nDepth: %d", node->depth);
    printf("\nFactor: %d", node->factor);
}

void node_depthDec(Node* node) {
    node->depth--;
}

void node_depthInc(Node* node) {
    node->depth++;
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
    type key = 0;
    int d = 0;
    bool needRotation = false;

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
    
    printf("Key %d removed (possible tree rearrange)", node->key);
    
    free(node);

    if (tree_factorCheck(tree->root, &d, &key, &needRotation)) {
        Node* rotAux = tree_searchByKey(tree, key, NULL);
        subtree_rotate(tree, rotAux);
    }

    tree_height(tree);
}

bool tree_factorCheck(Node* root, int* currentDepth, type* key, bool* needRotation) {
    if (abs(root->factor) > 1 && root->depth > *currentDepth) {
        *currentDepth = root->depth;
        *key = root->key;
        *needRotation = true;
    }
    tree_factorCheck(root->left, currentDepth, key, needRotation);
    tree_factorCheck(root->right, currentDepth, key, needRotation);
    
    return *needRotation;
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
        subtree_maxDepth(tree->root, &tree->height);
    }
}

void subtree_maxDepth(Node* root, int* maxDepth) {
    if (root != NULL) {
        if (root->depth > *maxDepth) *maxDepth = root->depth;
        subtree_maxDepth(root->left, maxDepth);
        subtree_maxDepth(root->right, maxDepth);
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

void subtree_rotate(Tree* tree, Node* root) {
    Node* parent;

    printf("\nenter rotate");

    while (root != NULL) {
        parent = root->parent;

        if (root->factor > 1) {
            if (root->left->factor > 0)
                subtree_rotateRight(tree, root);
            else
                subtree_doubleRotateRight(tree, root);

            break;
        }
        else if (root->factor < -1) {
            if (root->right->factor < 0)
                subtree_rotateLeft(tree, root);
            else
                subtree_doubleRotateLeft(tree, root);

            break;
        }

        root = parent;
    }
}

void subtree_rotateRight(Tree* tree, Node* root) {
    Node* aux = root->left;
    Node* parent = root->parent;

    printf("\nRight rotation at key %d", root->key);

    if (root == tree->root)
        tree->root = aux;

    root->left = aux->right;
    if (root->left != NULL)
        root->left->parent = root;
    aux->parent = parent;
    if (parent != NULL) {
        if (parent->left == root) parent->left = aux;
        else parent->right = aux;
    }
    aux->right = root;
    root->parent = aux;

    root->depth++;
    aux->depth--;
    tree_inorder(root->right, node_depthInc);
    tree_inorder(aux->left, node_depthDec);

    root->factor = 0;
    aux->factor = node_factor(aux);
}

void subtree_rotateLeft(Tree* tree, Node* root) {
    Node* aux = root->right;
    Node* parent = root->parent;

    printf("\nLeft rotation at key %d", root->key);

    if (root == tree->root)
        tree->root = aux;

    root->right = aux->left;
    if (root->right != NULL)
        root->right->parent = root;
    aux->parent = parent;
    if (parent != NULL) {
        if (parent->left == root) parent->left = aux;
        else parent->right = aux;
    }
    aux->left = root;
    root->parent = aux;

    root->depth++;
    aux->depth--;
    tree_inorder(root->left, node_depthInc);
    tree_inorder(aux->right, node_depthDec);

    root->factor = 0;
    aux->factor = node_factor(aux);
}

void subtree_doubleRotateRight(Tree* tree, Node* root) {
    Node* auxL = root->left;
    Node* auxR = auxL->right;
    Node* parent = root->parent;

    printf("\nDouble right rotation at key %d", root->key);

    if (root == tree->root)
        tree->root = auxR;

    auxL->right = auxR->left;
    if (auxL->right != NULL)
        auxL->right->parent = auxL;
    root->left = auxR->right;
    if (root->left != NULL)
        root->left->parent = root;
    auxR->parent = root->parent;
    if (parent != NULL) {
        if (parent->left == root) parent->left = auxR;
        else parent->right = auxR;
    }
    root->parent = auxR;
    auxL->parent = auxR;
    auxR->left = auxL;
    auxR->right = root;

    root->depth++;
    auxL->depth -= 2;
    tree_inorder(root->right, node_depthInc);
    tree_inorder(root->left, node_depthDec);
    tree_inorder(auxL->right, node_depthDec);

    if (auxR->factor == 1) root->factor = -1;
    else root->factor = 0;

    if (auxR->factor == -1) auxL->factor = 1;
    else auxL->factor = 0;

    auxR->factor = node_factor(auxR);
}

void subtree_doubleRotateLeft(Tree* tree, Node* root) {
    Node* auxR = root->right;
    Node* auxL = auxR->left;
    Node* parent = root->parent;

    printf("\nDouble left rotation at key %d", root->key);

    if (root == tree->root)
        tree->root = auxL;

    root->right = auxL->left;
    if (root->right != NULL)
        root->right->parent = root;
    auxR->left = auxL->right;
    if (auxR->left != NULL) 
        auxR->left->parent = auxR;
    auxL->parent = root->parent;
    if (parent != NULL) {
        if (parent->left == root) parent->left = auxL;
        else parent->right = auxL;
    }
    root->parent = auxL;
    auxR->parent = auxL;
    auxL->left = root;
    auxL->right = auxR;

    root->depth++;
    auxL->depth -= 2;
    tree_inorder(root->left, node_depthInc);
    tree_inorder(root->right, node_depthDec);
    tree_inorder(auxR->left, node_depthDec);

    if (auxL->factor == -1) root->factor = 1;
    else root->factor = 0;

    if (auxL->factor == 1) auxR->factor = -1;
    else auxR->factor = 0;

    auxL->factor = node_factor(auxL);
}

int node_factor(Node* node) {
    int hl = node->depth, hr = node->depth;

    subtree_maxDepth(node->left, &hl);

    subtree_maxDepth(node->right, &hr);

    return (hl - hr);
}

void tree_factor(Node* root, int* factor) {
    int aux = node_factor(root);

    if (aux > *factor) *factor = aux;

    if (root->left != NULL) tree_factor(root->left, factor);
    if (root->right != NULL) tree_factor(root->right, factor);
}