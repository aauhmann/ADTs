#include "queue.h"

typedef enum {INSERT, REMOVE, FRONT, PRINT, CLEAR, EXIT} MENU;

int main() {
    Queue queue = queueInitialize();
    QNode* node = NULL;
    MENU menu = 0;

    while (menu != EXIT) {
        printf("\n--- MENU ---");
        printf("\n 1. Insert");
        printf("\n 2. Remove");
        printf("\n 3. Get front");
        printf("\n 4. Print");
        printf("\n 5. Clear");
        printf("\n 6. Exit");
        printf("\nOption: ");
        scanf("%d", &menu);
        menu--;

        switch (menu) {
            case INSERT:
                type data;
                printf("\nInsert int: ");
                scanf("%d", &data);
                queueInsert(&queue, data);
                break;

            case REMOVE:
                queueNodeRemove(&queue);
                break;

            case PRINT:
                queuePrint(queue);
                break;

            case FRONT:
                node = queuePeek(queue);
                break;

            case CLEAR:
                queueClear(&queue);
                break;

            case EXIT:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid option");
                break;
        }
        printf("\n");
    }

    return 0;
}