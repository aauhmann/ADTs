#include "dll.h"

int main() {
    List list;
    type searchedData, data;
    int menu, pos;

    list_initialize(&list);

    while (true) {
        printf("\n--- MENU ---");
        printf("\n 1. Add node");
        printf("\n 2. Remove node");
        printf("\n 3. Search for node");
        printf("\n 4. Print list");
        printf("\n 5. Get data");
        printf("\n 6. Clear list");
        printf("\n 7. Exit program");
        printf("\nAction: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1: 
                /*Insert data inputs*/
                printf("\nInsert int: ");
                scanf("%d", &data);
                printf("List position (Beginning == 0): ");
                scanf("%d", &pos);

                list_insert(&list, pos, data);
                break;

            case 2:
                printf("\nList position (Beginning == 0): ");
                scanf("%d", &pos);

                list_remove(&list, pos);
                break;

            case 3:
                printf("\nList position (Beginning == 0): ");
                scanf("%d", &pos);

                list_searchNode(list, pos);
                break;

            case 4:
                list_print(list);
                break;

            case 5:
                printf("\nList position (Beginning == 0): ");
                scanf("%d", &pos);

                searchedData = list_getNode(list, pos);
                break;

            case 6:
                list_clear(&list);
                break;

            case 7:
                printf("\nExiting...\n");
                return 0;
                break;

            default:
                printf("\nInvalid action number");
                break;
        }

        printf("\n");
    }
}