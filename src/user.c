#include <stdio.h>
#include <string.h>
#include "user.h"
#include <stdlib.h>

UserNode* hashTable[TABLE_SIZE];

char currentUser[50];

void insertUserToHash(User u) {

    int index = hash(u.username);

    UserNode* newNode =
        malloc(sizeof(UserNode));

    if(newNode == NULL) {
        return;
    }

    newNode->data = u;

    newNode->next = hashTable[index];

    hashTable[index] = newNode;
}

User* searchUser(char* username) {

    int index = hash(username);

    UserNode* temp =
        hashTable[index];

    while(temp != NULL) {

        if(strcmp(
            temp->data.username,
            username) == 0) {

            return &temp->data;
        }

        temp = temp->next;
    }

    return NULL;
}

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

    insertUserToHash(u);

    fprintf(fp,
            "%s %s %d\n",
            u.username,
            u.password,
            u.role);

    fclose(fp);

    printf("Register successful!\n");
}

int loginUser(int role) {

    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    User* user =
        searchUser(username);

    if(user != NULL &&
       strcmp(user->password,
              password) == 0 &&
       user->role == role) {

        strcpy(currentUser,
               username);

        printf("Login successful!\n");

        return 1;
    }

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

void loadUsersToHash() {

    FILE* fp =
        fopen("data/users.txt", "r");

    if(fp == NULL) {
        return;
    }

    User u;

    while(fscanf(fp,
                 "%49s %49s %d",
                 u.username,
                 u.password,
                 &u.role) == 3) {

        insertUserToHash(u);
    }

    fclose(fp);
}