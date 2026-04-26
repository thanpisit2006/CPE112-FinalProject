#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char password[50];
    int role; 
} User;

void registerUser(int role);
int loginUser(int role);

#endif