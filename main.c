#include <stdio.h>
#include "product.h"
#include "file.h"

void adminMenu() {
    int choice;

    while(1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Product\n");
        printf("2. Show Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Save & Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: showProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: saveToFile(); return;
            default: printf("Invalid choice!\n");
        }
    }
}

void customerMenu() {
    int choice;

    while(1) {
        printf("\n--- Customer Menu ---\n");
        printf("1. Show Products\n");
        printf("2. Search Product\n");
        printf("3. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: showProducts(); break;
            case 2: searchProduct(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    loadFromFile();

    while(1) {
        printf("\n=== Stock Management System ===\n");
        printf("1. Customer\n");
        printf("2. Admin\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: customerMenu(); break;
            case 2: adminMenu(); break;
            case 3: 
                saveToFile();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}