#include <stdio.h>
#include "product.h"
#include "cart.h"

int cartIDs[100];
int cartQty[100];
int cartCount = 0;

void addToCart() {
    int id, qty;
    printf("Enter product ID: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {

            printf("Enter quantity: ");
            scanf("%d", &qty);

            if(qty > products[i].stock) {
                printf("Not enough stock!\n");
                return;
            }

            cartIDs[cartCount] = id;
            cartQty[cartCount] = qty;
            cartCount++;

            printf("Added to cart!\n");
            return;
        }
    }

    printf("Product not found!\n");
}

void showCart() {
    float total = 0;
    printf("\n--- Your Cart ---\n");

    for(int i = 0; i < cartCount; i++) {
        for(int j = 0; j < count; j++) {
            if(products[j].id == cartIDs[i]) {
                float subtotal = products[j].price * cartQty[i];
                total += subtotal;

                printf("%s x%d = %.2f\n",
                    products[j].name,
                    cartQty[i],
                    subtotal);
            }
        }
    }

    printf("Total: %.2f\n", total);
}

void checkout() {
    for(int i = 0; i < cartCount; i++) {
        for(int j = 0; j < count; j++) {
            if(products[j].id == cartIDs[i]) {
                products[j].stock -= cartQty[i];
            }
        }
    }

    cartCount = 0;
    printf("Purchase successful!\n");
}