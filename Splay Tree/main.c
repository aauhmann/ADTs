#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

#define EXIT 9

int main() {
    SPT spt = sptInitialize();
    NodeSPT* node = NULL;
    int menu = 0;

    while (menu != EXIT) {
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
            int key;
            NodeSPT* aux;

            case 1:
                printf("\nKey: ");
                scanf("%d", &key);
                sptInsert(&spt, key);
                break;

            case 2:

                printf("\nKey: ");
                scanf("%d", &key);
                getchar();
                aux = sptAccess(&spt, key);
                printf("\nKey: %d", aux->key);
                break;

            case 3:
                printf("\nKey: ");
                scanf("%d", &key);
                getchar();
                aux = sptAccess(&spt, key);
                printf("\nDepth: ", sptNodeDepth(aux));
                break;

            case 4:
                printf("\nKey: ");
                scanf("%d", &key);
                node = sptAccess(&spt, key);
                break;

            case 5:
                break;

            case 6:
                printf("\nTree height: %d", spt.height);
                break;

            case 7:
                sptPrint(spt);
                break;

            case 8:
                sptClear(&spt);
                break;

            case EXIT:
                printf("\nExiting...\n");
                break;
        }
        printf("\n");
    }

    return 0;
}