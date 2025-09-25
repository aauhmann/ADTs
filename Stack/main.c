#include "stack.h"

typedef enum {PUSH, POP, PRINT, PEEK, CLEAR, EXIT} MENU;

int main() {
    Stack stack;
    MENU menu;
    type popData;

    stack_initialize(&stack);

    while (1) {
        printf("\n--- MENU ---");
        printf("\n 1. Push");
        printf("\n 2. Pop");
        printf("\n 3. Print stack");
        printf("\n 4. Peek top");
        printf("\n 5. Clear");
        printf("\n 6. Exit");
        printf("\nOption: ");
        scanf("%d", &menu);
        menu--;

        switch (menu) {
            case PUSH:
                type data;
                printf("\nInsert int: ");
                scanf("%d", &data);
                stack_push(&stack, data);
                break;

            case POP:
                popData = stack_pop(&stack);
                break;

            case PRINT:
                stack_print(stack);
                break;

            case PEEK:
                stack_peek(stack);
                break;

            case CLEAR:
                stack_clear(&stack);
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