#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "file.h"

int cartIDs[100];
int cartQty[100];
int cartCount = 0;

typedef struct Order {
    char username[50];
    int ids[100];
    int qty[100];
    int count;
    struct Order* next;
} Order;

Order* front = NULL;
Order* rear = NULL;


void addToCart() {

    int id, qty;

    if(head == NULL) {
        printf("No products available.\n");
        return;
    }

    printf("Enter product ID: ");
    scanf("%d", &id);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.id == id) {

            printf("Enter quantity: ");
            scanf("%d", &qty);

            if(qty <= 0) {
                printf("Invalid quantity!\n");
                return;
            }

            if(qty > temp->data.stock) {
                printf("Not enough stock!\n");
                return;
            }

            for(int i = 0; i < cartCount; i++) {
                if(cartIDs[i] == id) {
                    cartQty[i] += qty;
                    printf("Updated quantity in cart!\n");
                    return;
                }
            }

            cartIDs[cartCount] = id;
            cartQty[cartCount] = qty;
            cartCount++;

            printf("Added to cart!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Product not found!\n");
}


void showCart() {

    float total = 0;

    if(cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }

    printf("\n--- Your Cart ---\n");

    for(int i = 0; i < cartCount; i++) {

        Node* temp = head;

        while(temp != NULL) {

            if(temp->data.id == cartIDs[i]) {

                float subtotal = temp->data.price * cartQty[i];
                total += subtotal;

                printf("ID: %d | %s x%d = %.2f\n",
                       temp->data.id,
                       temp->data.name,
                       cartQty[i],
                       subtotal);

                break;
            }

            temp = temp->next;
        }
    }

    printf("----------------------\n");
    printf("Total: %.2f\n", total);
}



void checkout(char* username) {

    if(cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }

    Order* newOrder = (Order*)malloc(sizeof(Order));

    strcpy(newOrder->username, username);
    newOrder->count = cartCount;

    for(int i = 0; i < cartCount; i++) {
        newOrder->ids[i] = cartIDs[i];
        newOrder->qty[i] = cartQty[i];
    }

    newOrder->next = NULL;

    if(front == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf("Order added to queue successfully!\n");

    cartCount = 0;  
}



void showOrders() {

    if(front == NULL) {
        printf("No pending orders.\n");
        return;
    }

    Order* temp = front;
    int num = 1;

    printf("\n===== ORDER QUEUE =====\n");

    while(temp != NULL) {

        printf("%d. Customer: %s\n", num++, temp->username);

        for(int i = 0; i < temp->count; i++) {
            printf("   - Product ID: %d | Qty: %d\n",
                   temp->ids[i],
                   temp->qty[i]);
        }

        temp = temp->next;
    }
}



void processOrder() {

    if(front == NULL) {
        printf("No orders to process.\n");
        return;
    }

    Order* temp = front;

    printf("Processing order of %s...\n", temp->username);

    for(int i = 0; i < temp->count; i++) {

        Node* p = head;

        while(p != NULL) {

            if(p->data.id == temp->ids[i]) {

                if(p->data.stock >= temp->qty[i]) {
                    p->data.stock -= temp->qty[i];
                    p->data.soldCount += temp->qty[i];
                } else {
                    printf("Stock not enough for product ID %d\n",
                           temp->ids[i]);
                }

                break;
            }

            p = p->next;
        }
    }

    front = front->next;

    if(front == NULL)
        rear = NULL;

    free(temp);

    saveToFile();

    printf("Order processed successfully!\n");
}