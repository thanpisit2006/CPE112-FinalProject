#include <stdio.h>
#include <string.h>
#include "product.h"

Product products[MAX];
int count = 0;

void addProduct() {
    printf("Enter ID: ");
    scanf("%d", &products[count].id);

    printf("Enter Name: ");
    scanf("%s", products[count].name);

    printf("Enter Price: ");
    scanf("%f", &products[count].price);

    printf("Enter Stock: ");
    scanf("%d", &products[count].stock);

    count++;
    printf("Product added successfully!\n");
}

void showProducts() {
    printf("\n--- Product List ---\n");
    for(int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n",
            products[i].id,
            products[i].name,
            products[i].price,
            products[i].stock);
    }
}

void updateProduct() {
    int id;
    printf("Enter product ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("New Price: ");
            scanf("%f", &products[i].price);

            printf("New Stock: ");
            scanf("%d", &products[i].stock);

            printf("Updated successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

void deleteProduct() {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            for(int j = i; j < count-1; j++) {
                products[j] = products[j+1];
            }
            count--;
            printf("Deleted successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

void searchProduct() {
    int id;
    printf("Enter product ID to search: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("Found: %s | Price: %.2f | Stock: %d\n",
                products[i].name,
                products[i].price,
                products[i].stock);
            return;
        }
    }
    printf("Product not found!\n");
}