#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

Node* head = NULL;

Node* createNode(Product p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

void addProduct() {
    Product p;

    printf("Enter ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Price: ");
    scanf("%f", &p.price);

    printf("Enter Stock: ");
    scanf("%d", &p.stock);

    p.soldCount = 0;

    Node* newNode = createNode(p);

    if(head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Product added!\n");
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

            if(prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Deleted!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Product not found.\n");
}