#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "file.h"
#include "cart.h"

CartNode* cartHead = NULL;

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

    int id;
    int qty;

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

            CartNode* cartTemp = cartHead;

            while(cartTemp != NULL) {

                if(cartTemp->id == id) {

                    if(cartTemp->qty + qty >
                    temp->data.stock) {

                        printf("Stock exceeded!\n");

                        return;
                    }

                    cartTemp->qty += qty;

                    printf("Updated cart quantity!\n");

                    return;
                }

                cartTemp = cartTemp->next;
            }

            CartNode* newNode =
                malloc(sizeof(CartNode));

            if(newNode == NULL) {

                printf("Memory allocation failed!\n");

                return;
            }

            newNode->id = id;
            newNode->qty = qty;
            newNode->next = cartHead;

            cartHead = newNode;

            printf("Added to cart!\n");

            return;
        }

        temp = temp->next;
    }

    printf("Product not found!\n");
}

void showCart() {

    if(cartHead == NULL) {

        printf("Cart is empty.\n");

        return;
    }

    float total = 0;

    CartNode* cartTemp = cartHead;

    printf("\n===== YOUR CART =====\n");

    while(cartTemp != NULL) {

        Node* temp = head;

        while(temp != NULL) {

            if(temp->data.id == cartTemp->id) {

                float subtotal =
                    temp->data.price *
                    cartTemp->qty;

                total += subtotal;

                printf("ID: %d | %s | Qty: %d | %.2f\n",
                       temp->data.id,
                       temp->data.name,
                       cartTemp->qty,
                       subtotal);

                break;
            }

            temp = temp->next;
        }

        cartTemp = cartTemp->next;
    }

    printf("----------------------\n");
    printf("Total: %.2f\n", total);
}

void checkout(char* username) {

    if(cartHead == NULL) {

        printf("Cart is empty.\n");

        return;
    }

    Order* newOrder =
        malloc(sizeof(Order));

    if(newOrder == NULL) {

        printf("Memory allocation failed!\n");

        return;
    }

    strcpy(newOrder->username, username);

    newOrder->count = 0;

    CartNode* cartTemp = cartHead;

    while(cartTemp != NULL) {

        newOrder->ids[newOrder->count] =
            cartTemp->id;

        newOrder->qty[newOrder->count] =
            cartTemp->qty;

        newOrder->count++;

        cartTemp = cartTemp->next;
    }

    newOrder->next = NULL;

    if(front == NULL) {

        front = rear = newOrder;
    }
    else {

        rear->next = newOrder;
        rear = newOrder;
    }

    saveOrdersToFile();

    while(cartHead != NULL) {

        CartNode* temp = cartHead;

        cartHead = cartHead->next;

        free(temp);
    }

    printf("Checkout successful!\n");
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

        printf("%d. %s\n",
               num++,
               temp->username);

        for(int i = 0; i < temp->count; i++) {

            printf("Product ID: %d | Qty: %d\n",
                   temp->ids[i],
                   temp->qty[i]);
        }

        temp = temp->next;
    }
}

void saveHistory(char* username,
                 int id,
                 int qty) {

    FILE* fp =
        fopen("data/history.txt", "a");

    if(fp == NULL)
        return;

    fprintf(fp,
            "%s %d %d\n",
            username,
            id,
            qty);

    fclose(fp);
}

void processOrder() {

    if(front == NULL) {

        printf("No orders.\n");

        return;
    }

    Order* temp = front;

    for(int i = 0; i < temp->count; i++) {

        Node* p = head;

        while(p != NULL) {

            if(p->data.id ==
               temp->ids[i]) {

                if(p->data.stock >= temp->qty[i]) {

                    p->data.stock -= temp->qty[i];

                    p->data.soldCount += temp->qty[i];

                    saveHistory(temp->username, temp->ids[i], temp->qty[i]);
                }
                else {

                    printf("Not enough stock for %s\n",
                        p->data.name);
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
    saveOrdersToFile();

    printf("Order processed!\n");
}

void saveOrdersToFile() {

    FILE* fp =
        fopen("data/orders.txt", "w");

    if(fp == NULL)
        return;

    Order* temp = front;

    while(temp != NULL) {

        fprintf(fp,
                "%s %d ",
                temp->username,
                temp->count);

        for(int i = 0; i < temp->count; i++) {

            fprintf(fp,
                    "%d %d ",
                    temp->ids[i],
                    temp->qty[i]);
        }

        fprintf(fp, "\n");

        temp = temp->next;
    }

    fclose(fp);
}

void loadOrdersFromFile() {

    FILE* fp =
        fopen("data/orders.txt", "r");

    if(fp == NULL)
        return;

    while(1) {

        Order* newOrder =
            malloc(sizeof(Order));

        if(fscanf(fp,
                  "%49s %d",
                  newOrder->username,
                  &newOrder->count) != 2) {

            free(newOrder);

            break;
        }

        for(int i = 0; i < newOrder->count; i++) {

            fscanf(fp,
                   "%d %d",
                   &newOrder->ids[i],
                   &newOrder->qty[i]);
        }

        newOrder->next = NULL;

        if(front == NULL) {

            front = rear = newOrder;
        }
        else {

            rear->next = newOrder;
            rear = newOrder;
        }
    }

    fclose(fp);
}