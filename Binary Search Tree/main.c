#include "Tree.h"

#define EXIT 9

int main() {
    Tree tree;
    int menu, key;
    Node* node;

    tree_initialize(&tree);

    while (true) {
        do {
            printf("\n--- MENU ---");
            printf("\n 1. Insert node");
            printf("\n 2. Print node");
            printf("\n 3. Node depth");
            printf("\n 4. Get node");
            printf("\n 5. Remove node");
            printf("\n 6. Tree height");
            printf("\n 7. Print tree");
            printf("\n 8. Clear tree");
            printf("\n 9. Exit");
            printf("\nOption: ");
            scanf("%d", &menu);
        } while (menu < 1 || menu > EXIT);

        switch (menu) {
            case 1:
                printf("\nKey: ");
                scanf("%d", &key);
                tree_insert(&tree, key);
                break;

            case 2:
                printf("\nKey: ");
                scanf("%d", &key);
                getchar();
                tree_bykey(&tree, key, node_print);
                break;

            case 3:
                printf("\nKey: ");
                scanf("%d", &key);
                getchar();
                tree_bykey(&tree, key, node_depth);
                break;

            case 4:
                printf("\nKey: ");
                scanf("%d", &key);
                node = tree_bykey(&tree, key, NULL);
                break;

            case 5:
                printf("\nKey: ");
                scanf("%d", &key);
                if (!tree_empty) printf("Node cleared (and all of its descendants)");
                tree_bykey(&tree, key, node_clear);
                break;

            case 6:
                printf("\nTree height: %d", tree.height);
                break;

            case 7:
                tree_print(tree);
                break;

            case 8:
                tree_clear(&tree);
                break;

            case EXIT:
                printf("\nExiting...\n");
                return 0;
        }
        printf("\n");
    }
}