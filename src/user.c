#include <stdio.h>
#include <string.h>
#include "user.h"

UserNode* hashTable[TABLE_SIZE];

char currentUser[50];

void registerUser(int role) {

    FILE *fp;

    User u;
    User temp;

    int adminExists = 0;

    fp = fopen("data/users.txt", "a+");

    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    rewind(fp);

    while(fscanf(fp,
                 "%49s %49s %d",
                 temp.username,
                 temp.password,
                 &temp.role) == 3) {

        if(temp.role == 1) {
            adminExists = 1;
        }
    }

    if(role == 1 && adminExists) {
        printf("Admin already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter username: ");
    scanf("%49s", u.username);

    rewind(fp);

    while(fscanf(fp,
                 "%49s %49s %d",
                 temp.username,
                 temp.password,
                 &temp.role) == 3) {

        if(strcmp(temp.username, u.username) == 0) {
            printf("Username already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter password: ");
    scanf("%49s", u.password);

    u.role = role;

    fprintf(fp,
            "%s %s %d\n",
            u.username,
            u.password,
            u.role);

    fclose(fp);

    printf("Register successful!\n");
}

int loginUser(int role) {

    FILE *fp;

    User u;

    char username[50];
    char password[50];

    fp = fopen("data/users.txt", "r");

    if(fp == NULL) {
        printf("No users found.\n");
        return 0;
    }

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    while(fscanf(fp,
                 "%49s %49s %d",
                 u.username,
                 u.password,
                 &u.role) == 3) {

        if(strcmp(username, u.username) == 0 &&
           strcmp(password, u.password) == 0 &&
           u.role == role) {

            fclose(fp);
            
            printf("Login successful!\n");

            strcpy(currentUser, username);
            
            return 1;
        }
    }

    fclose(fp);

    printf("Login failed!\n");

    return 0;
}

int hash(char* str) {

    int sum = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }

    return sum % TABLE_SIZE;
}