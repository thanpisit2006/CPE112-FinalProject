#ifndef USER_H
#define USER_H

#define TABLE_SIZE 100

typedef struct {
    char username[50];
    char password[50];
    int role;
} User;

typedef struct UserNode {
    User data;
    struct UserNode* next;
} UserNode;

extern char currentUser[50];
extern UserNode* hashTable[TABLE_SIZE];   

void registerUser(int role);
int loginUser(int role);

#endif