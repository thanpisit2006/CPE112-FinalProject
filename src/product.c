#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "product.h"
#include "file.h"

Node* head = NULL;

Node* createNode(Product p) {

    Node* newNode = malloc(sizeof(Node));

    if(newNode == NULL) {

        printf("Memory allocation failed!\n");

        exit(1);
    }

    newNode->data = p;
    newNode->next = NULL;

    return newNode;
}

void saveDeletedProduct(Product p) {

    FILE* fp =
        fopen("data/deletedproducts.txt", "a");

    if(fp == NULL) {

        printf("Error opening deleted file.\n");

        return;
    }

    fprintf(fp,
            "%d|%s|%.2f|%d|%d\n",
            p.id,
            p.name,
            p.price,
            p.stock,
            p.soldCount);

    fclose(fp);
}

void showDeletedProducts() {

    FILE* fp =
        fopen("data/deletedproducts.txt", "r");

    if(fp == NULL) {

        printf("No deleted products file.\n");

        return;
    }

    Product p;

    printf("\n===== DELETED PRODUCTS =====\n");

    int found = 0;

    while(fscanf(fp,
                 "%d|%49[^|]|%f|%d|%d",
                 &p.id,
                 p.name,
                 &p.price,
                 &p.stock,
                 &p.soldCount) == 5) {

        printf("ID: %d | %s | Price: %.2f | Stock: %d\n",
               p.id,
               p.name,
               p.price,
               p.stock);

        found = 1;
    }

    if(!found) {

        printf("No deleted products.\n");
    }

    fclose(fp);
}

void undoDelete() {

    FILE* fp =
        fopen("data/deletedproducts.txt", "r");

    if(fp == NULL) {

        printf("No deleted products.\n");

        return;
    }

    Product products[100];

    int count = 0;

    while(fscanf(fp,
                 "%d|%49[^|]|%f|%d|%d",
                 &products[count].id,
                 products[count].name,
                 &products[count].price,
                 &products[count].stock,
                 &products[count].soldCount) == 5) {

        count++;
    }

    fclose(fp);

    if(count == 0) {

        printf("No deleted products.\n");

        return;
    }

    showDeletedProducts();

    int restoreId;

    printf("\nEnter product ID to restore: ");

    scanf("%d", &restoreId);

    int found = 0;

    FILE* tempFile =
        fopen("data/temp.txt", "w");

    for(int i = 0; i < count; i++) {

        if(products[i].id == restoreId) {

            Node* newNode =
                createNode(products[i]);

            if(head == NULL) {

                head = newNode;
            }
            else {

                Node* temp = head;

                while(temp->next != NULL) {

                    temp = temp->next;
                }

                temp->next = newNode;
            }

            found = 1;

            continue;
        }

        fprintf(tempFile,
                "%d|%s|%.2f|%d|%d\n",
                products[i].id,
                products[i].name,
                products[i].price,
                products[i].stock,
                products[i].soldCount);
    }

    fclose(tempFile);

    remove("data/deletedproducts.txt");

    rename("data/temp.txt",
           "data/deletedproducts.txt");

    if(found) {

        saveToFile();

        printf("Product restored successfully!\n");
    }
    else {

        printf("Product ID not found.\n");
    }
}

void addProduct() {

    Product p;

    printf("Enter ID: ");

    scanf("%d", &p.id);

    Node* check = head;

    while(check != NULL) {

        if(check->data.id == p.id) {

            printf("Product ID already exists!\n");

            return;
        }

        check = check->next;
    }

    printf("Enter Name: ");

    scanf(" %[^\n]", p.name);

    printf("Enter Price: ");

    scanf("%f", &p.price);

    if(p.price <= 0) {

        printf("Invalid price!\n");

        return;
    }

    printf("Enter Stock: ");

    scanf("%d", &p.stock);

    if(p.stock < 0) {

        printf("Invalid stock!\n");

        return;
    }

    p.soldCount = 0;

    Node* newNode = createNode(p);

    if(head == NULL) {

        head = newNode;
    }
    else {

        Node* temp = head;

        while(temp->next != NULL) {

            temp = temp->next;
        }

        temp->next = newNode;
    }

    saveToFile();

    printf("Product added successfully!\n");
}

void showProducts() {

    Node* temp = head;

    if(temp == NULL) {

        printf("No products available.\n");

        return;
    }

    printf("\n");
    printf("====================================================\n");
    printf("                    PRODUCT LIST                    \n");
    printf("====================================================\n");

    while(temp != NULL) {

        printf("ID: %-3d Name: %-15s Price: %-8.2f Stock: %-5d Sold: %-5d\n",
               temp->data.id,
               temp->data.name,
               temp->data.price,
               temp->data.stock,
               temp->data.soldCount);

        temp = temp->next;
    }
}

void searchProduct() {

    int id;

    printf("Enter ID to search: ");

    scanf("%d", &id);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.id == id) {

            printf("Found: %s | %.2f | Stock: %d\n",
                   temp->data.name,
                   temp->data.price,
                   temp->data.stock);

            return;
        }

        temp = temp->next;
    }

    printf("Product not found.\n");
}

void toLowerCase(char* str) {

    for(int i = 0; str[i]; i++) {

        str[i] = tolower(str[i]);
    }
}

void searchProductByName() {

    char keyword[50];

    int found = 0;

    printf("Enter product name: ");

    scanf(" %[^\n]", keyword);

    toLowerCase(keyword);

    Node* temp = head;

    while(temp != NULL) {

        char productName[50];

        strcpy(productName,
               temp->data.name);

        toLowerCase(productName);

        if(strstr(productName,
                  keyword) != NULL) {

            printf("ID: %d | %s | %.2f | Stock: %d | Sold: %d\n",
                   temp->data.id,
                   temp->data.name,
                   temp->data.price,
                   temp->data.stock,
                   temp->data.soldCount);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found) {

        printf("No matching products found.\n");
    }
}

void updateProduct() {

    int id;

    printf("Enter ID to update: ");

    scanf("%d", &id);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.id == id) {

            float newPrice;

            int newStock;

            printf("New Price: ");

            scanf("%f", &newPrice);

            printf("New Stock: ");

            scanf("%d", &newStock);

            temp->data.price = newPrice;

            temp->data.stock = newStock;

            saveToFile();

            printf("Updated!\n");

            return;
        }

        temp = temp->next;
    }

    printf("Product not found.\n");
}

void deleteProduct() {

    int id;

    printf("Enter ID to delete: ");

    scanf("%d", &id);

    Node* temp = head;

    Node* prev = NULL;

    while(temp != NULL) {

        if(temp->data.id == id) {

            saveDeletedProduct(temp->data);

            if(prev == NULL) {

                head = temp->next;
            }
            else {

                prev->next = temp->next;
            }

            free(temp);

            saveToFile();

            printf("Deleted successfully!\n");

            return;
        }

        prev = temp;

        temp = temp->next;
    }

    printf("Product not found.\n");
}

void sortProducts() {

    if(head == NULL || head->next == NULL) {

        printf("Not enough products to sort.\n");

        return;
    }

    int choice;

    printf("\n--- Sort Menu ---\n");
    printf("1. ID ASC\n");
    printf("2. ID DESC\n");
    printf("3. Price ASC\n");
    printf("4. Price DESC\n");
    printf("5. Stock ASC\n");
    printf("6. Stock DESC\n");
    printf("7. Sold ASC\n");
    printf("8. Sold DESC\n");
    printf("Choose: ");

    scanf("%d", &choice);

    int swapped;

    Node* ptr1;

    Node* lptr = NULL;

    do {

        swapped = 0;

        ptr1 = head;

        while(ptr1->next != lptr) {

            int shouldSwap = 0;

            switch(choice) {

                case 1:
                    shouldSwap =
                        ptr1->data.id >
                        ptr1->next->data.id;
                    break;

                case 2:
                    shouldSwap =
                        ptr1->data.id <
                        ptr1->next->data.id;
                    break;

                case 3:
                    shouldSwap =
                        ptr1->data.price >
                        ptr1->next->data.price;
                    break;

                case 4:
                    shouldSwap =
                        ptr1->data.price <
                        ptr1->next->data.price;
                    break;

                case 5:
                    shouldSwap =
                        ptr1->data.stock >
                        ptr1->next->data.stock;
                    break;

                case 6:
                    shouldSwap =
                        ptr1->data.stock <
                        ptr1->next->data.stock;
                    break;

                case 7:
                    shouldSwap =
                        ptr1->data.soldCount >
                        ptr1->next->data.soldCount;
                    break;

                case 8:
                    shouldSwap =
                        ptr1->data.soldCount <
                        ptr1->next->data.soldCount;
                    break;

                default:
                    printf("Invalid choice!\n");
                    return;
            }

            if(shouldSwap) {

                Product temp = ptr1->data;

                ptr1->data = ptr1->next->data;

                ptr1->next->data = temp;

                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;

    } while(swapped);

    printf("Products sorted successfully!\n");

    showProducts();
}

void salesReport() {

    if(head == NULL) {

        printf("No products available.\n");

        return;
    }

    Node* temp = head;

    int totalProducts = 0;

    int totalSold = 0;

    float revenue = 0;

    Product bestSeller = head->data;

    while(temp != NULL) {

        totalProducts++;

        totalSold += temp->data.soldCount;

        revenue +=
            temp->data.price *
            temp->data.soldCount;

        if(temp->data.soldCount >
           bestSeller.soldCount) {

            bestSeller = temp->data;
        }

        temp = temp->next;
    }

    printf("\n===== SALES REPORT =====\n");

    printf("Total Products : %d\n",
           totalProducts);

    printf("Total Sold     : %d\n",
           totalSold);

    printf("Total Revenue  : %.2f\n",
           revenue);

    printf("\nBest Seller\n");

    printf("ID     : %d\n",
           bestSeller.id);

    printf("Name   : %s\n",
           bestSeller.name);

    printf("Sold   : %d\n",
           bestSeller.soldCount);
}

void recommendProducts() {

    if(head == NULL) {

        printf("No products.\n");

        return;
    }

    Node* temp = head;

    Product bestSeller;

    int found = 0;

    while(temp != NULL) {

        if(temp->data.stock > 0) {

            if(!found ||
               temp->data.soldCount >
               bestSeller.soldCount) {

                bestSeller =
                    temp->data;

                found = 1;
            }
        }

        temp = temp->next;
    }

    if(!found || bestSeller.soldCount == 0) {

        printf("No sales data for recommendation yet.\n");

        return;
    }

    printf("\n");
    printf("===================================\n");
    printf("        RECOMMENDED PRODUCT        \n");
    printf("===================================\n");

    printf("Best Seller Available Now\n\n");

    printf("ID: %d\n",
           bestSeller.id);

    printf("Name: %s\n",
           bestSeller.name);

    printf("Price: %.2f\n",
           bestSeller.price);

    printf("Stock: %d\n",
           bestSeller.stock);

    printf("Sold: %d\n",
           bestSeller.soldCount);

    printf("===================================\n");
}