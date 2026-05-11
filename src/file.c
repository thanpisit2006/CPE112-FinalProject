#include <stdio.h>
#include <stdlib.h>
#include "product.h"

void saveToFile() {

    FILE *fp = fopen("data/products.txt", "w");

    if(fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    Node* temp = head;

    while(temp != NULL) {

        fprintf(fp,
                "%d|%s|%.2f|%d|%d\n",
                temp->data.id,
                temp->data.name,
                temp->data.price,
                temp->data.stock,
                temp->data.soldCount);

        temp = temp->next;
    }

    fclose(fp);
}

void loadFromFile() {

    FILE *fp = fopen("data/products.txt", "r");

    if(fp == NULL) {
        return;
    }

    Product p;

    while(fscanf(fp,
                "%d|%49[^|]|%f|%d|%d",
                &p.id,
                p.name,
                &p.price,
                &p.stock,
                &p.soldCount) == 5) {

        Node* newNode = createNode(p);

        if(head == NULL) {
            head = newNode;
        }
        else {

            Node* temp = head;

            while(temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }

    fclose(fp);
}