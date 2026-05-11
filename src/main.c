#include <stdio.h>
#include <string.h>
#include "product.h"
#include "file.h"
#include "cart.h"
#include "user.h"

void adminMenu() {

    int choice;

    while(1) {

        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Product\n");
        printf("2. Show Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Sort Products\n");
        printf("6. Undo Delete\n");
        printf("7. Sales Report\n");
        printf("8. Show Orders\n");
        printf("9. Process Next Order\n");
        printf("10. Save & Back\n");
        printf("Choose: ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addProduct();
                break;

            case 2:
                showProducts();
                break;

            case 3:
                updateProduct();
                break;

            case 4:
                deleteProduct();
                break;

            case 5:
                sortProducts();
                break;

            case 6:
                undoDelete();
                break;

            case 7:
                salesReport();
                break;

            case 8:
                showOrders();
                break;

            case 9:
                processOrder();
                break;

            case 10:
                saveToFile();
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}

void customerMenu() {

    int choice;

    while(1) {

        printf("\n--- Customer Menu ---\n");
        printf("1. Show Products\n");
        printf("2. Search Product By ID\n");
        printf("3. Search Product By Name\n");
        printf("4. Add to Cart\n");
        printf("5. Show Cart\n");
        printf("6. Checkout\n");
        printf("7. Recommend Products\n");
        printf("8. Back\n");
        printf("Choose: ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
                showProducts();
                break;

            case 2:
                searchProduct();
                break;

            case 3:
                searchProductByName();
                break;

            case 4:
                addToCart();
                break;

            case 5:
                showCart();
                break;

            case 6:
                checkout(currentUser);
                break;

            case 7:
                recommendProducts();
                break;

            case 8:
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {

    int choice;

    loadFromFile();

    loadUsersToHash();

    loadOrdersFromFile();

    while(1) {

        printf("\n=== Stock Management System ===\n");
        printf("1. Register Customer\n");
        printf("2. Register Admin\n");
        printf("3. Login Customer\n");
        printf("4. Login Admin\n");
        printf("5. Exit\n");
        printf("Choose: ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
                registerUser(0);
                break;

            case 2:
                registerUser(1);
                break;

            case 3:
                if(loginUser(0))
                    customerMenu();
                break;

            case 4:
                if(loginUser(1))
                    adminMenu();
                break;

            case 5:
                saveToFile();
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}