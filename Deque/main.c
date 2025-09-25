#include "deque.h"

typedef enum {INSERT, REMOVE, PEEK_FRONT, PEEK_REAR, PRINT, CLEAR, EXIT} MENU;

int main() {
    Deque deque;
    MENU menu;
    int loc;

    deque_initialize(&deque);

    while (true) {
        printf("\n--- MENU ---");
        printf("\n 1. Insert");
        printf("\n 2. Remove");
        printf("\n 3. Get front");
        printf("\n 4. Get rear");
        printf("\n 5. Print");
        printf("\n 6. Clear");
        printf("\n 7. Exit");
        printf("\nOption: ");
        scanf("%d", &menu);
        menu--;

        switch (menu) {
            case INSERT:
                type data;

                do {
                    printf("\nInsert at:");
                    printf("\n 1. Front");
                    printf("\n 2. Rear");
                    printf("\nOption: ");
                    scanf("%d", &loc);
                } while (loc != 1 && loc != 2);
                loc--;
                printf("\nInsert int: ");
                scanf("%d", &data);

                deque_insert(&deque, data, loc);
                break;

            case REMOVE:
                do {
                    printf("\nRemove at:");
                    printf("\n 1. Front");
                    printf("\n 2. Rear");
                    printf("\nOption: ");
                    scanf("%d", &loc);
                } while (loc != 1 && loc != 2);
                loc--;

                deque_remove(&deque, loc);
                break;

            case PRINT:
                deque_print(deque);
                break;

            case PEEK_FRONT:
                deque_front(deque);
                break;

            case PEEK_REAR:
                deque_rear(deque);
                break;

            case CLEAR:
                deque_clear(&deque);
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