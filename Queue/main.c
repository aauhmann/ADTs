#include "queue.h"

typedef enum {INSERT, REMOVE, FRONT, PRINT, CLEAR, EXIT} MENU;

int main() {
    Queue queue;
    MENU menu;

    queue_initialize(&queue);

    while (1) {
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
                queue_insert(&queue, data);
                break;

            case REMOVE:
                queue_remove(&queue);
                break;

            case PRINT:
                queue_print(queue);
                break;

            case FRONT:
                queue_front(queue);
                break;

            case CLEAR:
                queue_clear(&queue);
                break;

            case EXIT:
                printf("\nExiting...\n");
                return 0;

                break;

            default:
                printf("\nInvalid option");
                break;
        }
        printf("\n");
    }
}