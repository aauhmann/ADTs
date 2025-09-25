#include "sll.h"

#define FALSE 0
#define TRUE 1

int main() {
    Node* list;
    int menu, listInitialized = FALSE;
    Object selectedObj;

    do {
        printf("\n\n--- MENU ---\n 1. Initialize List\n 2. Add Object\n 3. Remove Object\n 4. Get Object\n 5. Print Objects\n 6. Destruct List\n 7. Exit");
        printf("\nOption: ");
        scanf("%d", &menu);

        if (listInitialized == FALSE && menu != 1 && menu != 7)
            printf("\nList not initialized\n");
        else {
            switch (menu) {
                case 1:
                    list = initialize();
                    listInitialized = TRUE;
                    break;

                case 2:
                    int opt, pos;
                    Object obj;

                    printf("\nID: ");
                    scanf("%d", &obj.id);
                    printf("Price: ");
                    scanf("%f", &obj.price);
                    printf("Stock: ");
                    scanf("%d", &obj.stock);

                    printf("\nInsert:\n 1. Beginning\n 2. End\n 3. Other\n Option: ");
                    scanf("%d", &opt);
                    
                    switch (opt) {
                        case 1:
                            list = insertFirst(list, obj);
                            break;
                        case 2:
                            list = insertLast(list, obj);
                            break;
                        case 3:
                            printf("\nPosition desired (Beginning = 0): ");
                            scanf("%d", &pos);
                            list = insertRandom(list, obj, pos);
                            break;
                    }
                    break;

                case 3:
                    int id;

                    printf("\nRemoving Object ID: ");
                    scanf("%d", &id);
                    list = removeObject(list, id);
                    break;

                case 4:
                    printf("\nSelected Object ID: ");
                    scanf("%d", &id);
                    selectedObj = getObject(list, id);
                    break;

                case 5:
                    printf("\n");
                    printList(list);
                    break;

                case 6:
                    list = destruct(list);
                    printf("Destructed list pointer: %p\n", list);
                    listInitialized = FALSE;
                    break;

                case 7:
                    printf("\nExiting...\n");
                    break;

                default:
                    printf("\nInvalid option\n");
                    break;
            }
        }
    } while (menu != 7);
    
    return 0;
}