#include <stdio.h>
#include "product.h"

void saveToFile() {
    FILE *fp = fopen("products.txt", "w");

    for(int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %f %d\n",
            products[i].id,
            products[i].name,
            products[i].price,
            products[i].stock);
    }

    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("products.txt", "r");

    if(fp == NULL) return;

    while(fscanf(fp, "%d %s %f %d",
        &products[count].id,
        products[count].name,
        &products[count].price,
        &products[count].stock) != EOF) {

        count++;
    }

    fclose(fp);
}