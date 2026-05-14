# cpe112

Smart Convenience Management System - CPE112 Final Project

---

## overview

This project is a console based inventory management system written in C.

The system supports:

- product management
- customer and admin login
- shopping cart system
- order queue system
- sales report
- recommendation system
- undo delete feature
- file persistence
- hash table for user management

---

## features

### admin features

- add product
- update product
- delete product
- undo deleted product
- sort products
- process customer orders
- view sales report
- manage stock

### customer features

- register and login
- browse products
- search product by id
- search product by name
- add product to cart
- checkout
- view recommended products

---

## data structures used

| data structure | usage |
|---|---|
| linked list | product storage |
| queue | customer orders |
| hash table | user management |

---

## project structure

.
├── data/
│   ├── deletedproducts.txt
│   ├── products.txt
│   ├── users.txt
│   ├── orders.txt
│   └── history.txt
│
├── include/
│   ├── cart.h
│   ├── file.h
│   ├── product.h
│   └── user.h
│
├── src/
│   ├── cart.c
│   ├── file.c
│   ├── main.c
│   ├── product.c
│   └── user.c
│
├── .gitignore
└── README.md

## run instruction

step 1: run this command on terminal
    gcc src/*.c -Iinclude -Wall -Wextra -o app

step 2: after previous command finished, then run this command
    ./app

step 3: program running