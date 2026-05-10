#include <stdio.h>
#include <string.h>
#include "user.h"

void registerUser(int role) {
    FILE *fp;
    User u;
    User temp;
    int adminExists = 0;

    fp = fopen("users.txt", "a+");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // เช็คว่า admin มีแล้วไหม
    rewind(fp);
    while(fscanf(fp, "%s %s %d", temp.username, temp.password, &temp.role) != EOF) {
        if(temp.role == 1) {
            adminExists = 1;
        }
    }

    if(role == 1 && adminExists) {
        printf("Admin already exists! Only 1 admin allowed.\n");
        fclose(fp);
        return;
    }

    printf("Enter username: ");
    scanf("%s", u.username);

    printf("Enter password: ");
    scanf("%s", u.password);

    u.role = role;

    fprintf(fp, "%s %s %d\n", u.username, u.password, u.role);

    printf("Register successful!\n");

    fclose(fp);
}

int loginUser(int role) {
    FILE *fp;
    User u;
    char username[50], password[50];

    fp = fopen("users.txt", "r");
    if(fp == NULL) {
        printf("No users found.\n");
        return 0;
    }

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    while(fscanf(fp, "%s %s %d", u.username, u.password, &u.role) != EOF) {
        if(strcmp(username, u.username) == 0 &&
           strcmp(password, u.password) == 0 &&
           u.role == role) {

            fclose(fp);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Login failed!\n");
    return 0;
}