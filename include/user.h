#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char password[50];
    int role; 
} User;

typedef struct UserNode {
    User data;
    struct UserNode* next;
} UserNode;

#define TABLE_SIZE 100

void registerUser(int role);
int loginUser(int role);

#endif