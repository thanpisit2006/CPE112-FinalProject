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

typedef struct StackNode {
    Product data;
    struct StackNode* next;
} StackNode;

extern Node* head;
extern StackNode* undoStack;

Node* createNode(Product p);

void addProduct();
void showProducts();
void updateProduct();
void deleteProduct();
void searchProduct();

void sortProducts();
void undoDelete();
void salesReport();

void pushUndo(Product p);
Product popUndo();

#endif