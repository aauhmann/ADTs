#include "avl.h"
#include <stdio.h>

#define EXIT 9

int main() {
    AVL tree = avlInitialize();
    int menu, key;
    NodeAVL* node;

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
                avlNodePrint(tree, key);
                break;

            case 3:
                printf("\nKey: ");
                scanf("%d", &key);
                getchar();
                avlNodePrintDepth(tree, key);
                break;

            case 4:
                printf("\nKey: ");
                scanf("%d", &key);
                node = avlNodeGet(tree, key);
                break;

            case 5:
                printf("\nKey: ");
                scanf("%d", &key);
                avlNodeDelete(&tree, key);
                break;

            case 6:
                printf("\nTree height: %d", tree.height);
                break;

            case 7:
                avlPrint(tree);
                break;

            case 8:
                avlClear(&tree);
                break;

            case EXIT:
                printf("\nExiting...\n");
                return 0;
        }
        printf("\n");
    }

    return 0;
}