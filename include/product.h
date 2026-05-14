#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
    int soldCount;
} Product;

typedef struct Node {
    Product data;
    struct Node* next;
} Node;

extern Node* head;

Node* createNode(Product p);

void addProduct();
void showProducts();
void updateProduct();
void deleteProduct();

void searchProduct();
void searchProductByName();

void recommendProducts();

void sortProducts();

void undoDelete();

void salesReport();

void saveDeletedProduct(Product p);
void showDeletedProducts();

#endif