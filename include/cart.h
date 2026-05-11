#ifndef CART_H
#define CART_H

typedef struct CartNode {

    int id;
    int qty;

    struct CartNode* next;

} CartNode;

extern CartNode* cartHead;

void addToCart();
void showCart();
void checkout(char* username);

void showOrders();
void processOrder();

void saveOrdersToFile();
void loadOrdersFromFile();

#endif