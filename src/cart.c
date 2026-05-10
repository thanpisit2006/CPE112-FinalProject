#include <stdio.h>
#include <stdlib.h>

#include "product.h"
#include "file.h"

int cartIDs[100];
int cartQty[100];
int cartCount = 0;

typedef struct OrderNode {

    int productID;
    int quantity;

    struct OrderNode* next;

} OrderNode;

OrderNode* front = NULL;
OrderNode* rear = NULL;

void enqueueOrder(int id, int qty);

void addToCart() {

    int id;
    int qty;

    if(cartCount >= 100) {
        printf("Cart is full!\n");
        return;
    }

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

                float subtotal =
                    temp->data.price * cartQty[i];

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

void checkout() {

    if(cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }

    float total = 0;

    for(int i = 0; i < cartCount; i++) {

        Node* temp = head;

        while(temp != NULL) {

            if(temp->data.id == cartIDs[i]) {

                temp->data.stock -= cartQty[i];
                temp->data.soldCount += cartQty[i];

                enqueueOrder(
                    cartIDs[i],
                    cartQty[i]
                );

                total +=
                    temp->data.price * cartQty[i];

                break;
            }

            temp = temp->next;
        }
    }

    printf("Total Payment: %.2f\n", total);
    printf("Purchase successful!\n");

    saveToFile();

    cartCount = 0;
}

void enqueueOrder(int id, int qty) {

    OrderNode* newNode =
        malloc(sizeof(OrderNode));

    if(newNode == NULL) {
        printf("Queue allocation failed!\n");
        return;
    }

    newNode->productID = id;
    newNode->quantity = qty;
    newNode->next = NULL;

    if(rear == NULL) {

        front = rear = newNode;
    }
    else {

        rear->next = newNode;
        rear = newNode;
    }
}

void processOrders() {

    if(front == NULL) {
        printf("No pending orders.\n");
        return;
    }

    OrderNode* temp = front;

    printf("\nProcessing Order\n");

    printf("Product ID : %d\n",
           temp->productID);

    printf("Quantity   : %d\n",
           temp->quantity);

    front = front->next;

    if(front == NULL) {
        rear = NULL;
    }

    free(temp);

    printf("Order processed!\n");
}