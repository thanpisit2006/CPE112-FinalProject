#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "file.h"

Node* head = NULL;
StackNode* undoStack = NULL;

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

void pushUndo(Product p) {

    StackNode* newNode = malloc(sizeof(StackNode));

    if(newNode == NULL) {
        printf("Stack allocation failed!\n");
        return;
    }

    newNode->data = p;
    newNode->next = undoStack;

    undoStack = newNode;
}

Product popUndo() {

    Product empty = {0};

    if(undoStack == NULL) {
        return empty;
    }

    StackNode* temp = undoStack;

    Product p = temp->data;

    undoStack = undoStack->next;

    free(temp);

    return p;
}

void undoDelete() {

    if(undoStack == NULL) {
        printf("Nothing to undo!\n");
        return;
    }

    Product p = popUndo();

    Node* newNode = createNode(p);

    newNode->next = head;
    head = newNode;

    saveToFile();

    printf("Undo successful!\n");
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
    scanf("%49s", p.name);

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

    printf("\n--- Product List ---\n");

    while(temp != NULL) {

        printf("ID: %d | %s | %.2f | Stock: %d | Sold: %d\n",
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

void updateProduct() {

    int id;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.id == id) {

            printf("New Price: ");
            scanf("%f", &temp->data.price);

            printf("New Stock: ");
            scanf("%d", &temp->data.stock);

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

            pushUndo(temp->data);

            if(prev == NULL) {
                head = temp->next;
            }
            else {
                prev->next = temp->next;
            }

            free(temp);

            saveToFile();

            printf("Deleted!\n");

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
    printf("1. Price ASC\n");
    printf("2. Price DESC\n");
    printf("3. Stock ASC\n");
    printf("4. Stock DESC\n");
    printf("5. Sold ASC\n");
    printf("6. Sold DESC\n");
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
                        ptr1->data.price >
                        ptr1->next->data.price;
                    break;

                case 2:
                    shouldSwap =
                        ptr1->data.price <
                        ptr1->next->data.price;
                    break;

                case 3:
                    shouldSwap =
                        ptr1->data.stock >
                        ptr1->next->data.stock;
                    break;

                case 4:
                    shouldSwap =
                        ptr1->data.stock <
                        ptr1->next->data.stock;
                    break;

                case 5:
                    shouldSwap =
                        ptr1->data.soldCount >
                        ptr1->next->data.soldCount;
                    break;

                case 6:
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