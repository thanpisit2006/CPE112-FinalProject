#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
} Product;

extern Product products[MAX];
extern int count;

void addProduct();
void showProducts();
void updateProduct();
void deleteProduct();
void searchProduct();

#endif